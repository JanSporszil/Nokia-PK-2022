#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{}

void BtsPort::start(IBtsEventsHandler &handler)
{
    this->handler = &handler;
    transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
    transport.registerDisconnectedCallback([this]() {this->handler->handleDisconnected();});
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    transport.registerDisconnectedCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
        case common::MessageId::Sib:
        {
            auto btsId = reader.readBtsId();
            handler->handleSib(btsId);
            break;
        }
        case common::MessageId::AttachResponse:
        {
            bool accept = reader.readNumber<std::uint8_t>() != 0u;
            if (accept)
                handler->handleAttachAccept();
            else
                handler->handleAttachReject();
            break;
        }
        case common::MessageId::Sms:
        {
            uint8_t mode = reader.readNumber<std::uint8_t>();

            if (mode == 0)
            {
                std::string content = reader.readRemainingText();
                handler->handleSMSReceive(mode, content, from, to);
            }

            else
            {
                /* TODO */
                logger.logError("Received unknown SMS mode", mode);
            }
            break;
        }
        case common::MessageId::UnknownRecipient:
        {
            common::MessageId failedMessageId = reader.readMessageId();
            if(failedMessageId == common::MessageId::Sms)
            {
                handler->handleFailedSms();

            }
            break;
        }
        default:
            logger.logError("unknow message: ", msgId, ", from: ", from);

        }
    }
    catch (std::exception const& ex)
    {
        logger.logError("handleMessage error: ", ex.what());
    }
}


void BtsPort::sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());


}

void BtsPort::sendSms(common::PhoneNumber to, std::string message, int mode)
{
    logger.logDebug("sending sms: ", to, message, mode);
    common::OutgoingMessage msg{common::MessageId::Sms,
                                phoneNumber,
                                to};
    msg.writeNumber( static_cast<uint8_t>(mode));
    switch (mode) {
    case 0:
        {
            msg.writeText(message);
        }
        break;
    default:
        {
        logger.logError("Sending sms: unknown mode");
        }
        break;
    }
    transport.sendMessage(msg.getMessage());

}

common::PhoneNumber BtsPort::getMyPhoneNumber()
{
    return phoneNumber;
}


}
