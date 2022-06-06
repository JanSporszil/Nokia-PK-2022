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

            else if (mode == 1)
            {
                uint8_t key = reader.readNumber<std::uint8_t>();
                std::string content = reader.readRemainingText();
                xorMessage(content, key);
                handler->handleSMSReceive(mode, content, from, to);
            }

            else if (mode == 2)
            {
                uint8_t key = reader.readNumber<std::uint8_t>();
                std::string content = reader.readRemainingText();
                cesarDecryptMessage(content, key);
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

            if(failedMessageId == common::MessageId::CallRequest)
            {
                handler->handleUnknownCallNumber();
            }

            if(failedMessageId == common::MessageId::CallAccepted)
            {
                handler->handleUnknownCallAccept();
            }

            if(failedMessageId == common::MessageId::CallDropped)
            {
                //UE should ignore this message
                logger.logInfo("Received CallDropped with unknown number");
            }
            break;
        }
        case common::MessageId::CallDropped:
        {
            handler->handleCallDrop();
            break;
        }
        case common::MessageId::CallAccepted:
        {
            handler->handleCallAccepted();
            break;
        }
        case common::MessageId::CallRequest:
        {
            uint8_t mode = reader.readNumber<std::uint8_t>();

            if (mode == 0)
            {
                handler->handleCallRequest(from);
            }

            else
            {
                /* TODO */
                logger.logError("Received unknown CALL mode", mode);
            }

            break;
        }

        case common::MessageId::CallTalk:
        {
            std::string content = reader.readRemainingText();
            handler->handleCallTalkReceive(content, from);
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

void BtsPort::xorMessage(std::string &message, uint8_t key)
{
    for (auto& ch : message) {
        ch ^= key;
    }
}

void BtsPort::cesarEncryptMessage(std::string &message, uint8_t key)
{
    for (auto& ch : message) {
        ch += key;
    }
}

void BtsPort::cesarDecryptMessage(std::string &message, uint8_t key)
{
    for (auto& ch : message) {
        ch -= key;
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
    case 1:
    {
        msg.writeNumber(static_cast<uint8_t>(55));
        xorMessage(message, 55);
        msg.writeText(message);
        break;
    }
    case 2:
    {
        msg.writeNumber(static_cast<uint8_t>(155));
        cesarEncryptMessage(message, 155);
        msg.writeText(message);
        break;
    }
    default:
        {
        logger.logError("Sending sms: unknown mode");
        }
        break;
    }
    transport.sendMessage(msg.getMessage());

}

void BtsPort::sendCallRequest(common::PhoneNumber to)
{
    logger.logDebug("sending call request: ", to);
    common::OutgoingMessage msg{common::MessageId::CallRequest,
                                phoneNumber,
                                to};
    msg.writeNumber( static_cast<uint8_t>(0));
    transport.sendMessage(msg.getMessage());
}

common::PhoneNumber BtsPort::getMyPhoneNumber()
{
    return phoneNumber;
}

void BtsPort::sendDropCall(common::PhoneNumber to)
{
    logger.logDebug("Sending drop call: ", to);
    common::OutgoingMessage msg{common::MessageId::CallDropped,
                                phoneNumber,
                                to};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallAccepted(common::PhoneNumber to)
{
    logger.logDebug("Sending call accepted: ", to);
    common::OutgoingMessage msg{common::MessageId::CallAccepted,
                                phoneNumber,
                                to};

    msg.writeNumber( static_cast<uint8_t>(0));
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallTalk(const std::string & content, common::PhoneNumber to)
{
    logger.logDebug("Sending call talk: ", to);
    common::OutgoingMessage msg{common::MessageId::CallTalk,
                                phoneNumber,
                                to};

    msg.writeText(content);
    transport.sendMessage(msg.getMessage());
}


}
