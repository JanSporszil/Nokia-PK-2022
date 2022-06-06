#pragma once

#include "IBtsPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "ITransport.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class BtsPort : public IBtsPort
{
public:
    BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber);
    void start(IBtsEventsHandler& handler);
    void stop();


    void sendAttachRequest(common::BtsId) override;
    void sendSms(common::PhoneNumber, const std::string &) override;
    void sendCallRequest(common::PhoneNumber) override;
    common::PhoneNumber getMyPhoneNumber() override;
    void sendDropCall(common::PhoneNumber) override;
    void sendCallAccepted(common::PhoneNumber) override;
    void sendCallTalk(const std::string&, common::PhoneNumber) override;

private:
    void handleMessage(BinaryMessage msg);
    void xorMessage(std::string& message, uint8_t key);
    void cesarEncryptMessage(std::string& message, uint8_t key);
    void cesarDecryptMessage(std::string& message, uint8_t key);
    uint8_t getRandomNumber();
    enum EncryptionMode
    {
        NONE = 0,
        XOR,
        CESAR,
        UNKNOWN
    };
    common::PrefixedLogger logger;
    common::ITransport& transport;
    common::PhoneNumber phoneNumber;
    const uint8_t PROPOSED_ENCRYPTION_MODE = NONE;
    IBtsEventsHandler* handler = nullptr;
    uint8_t callEncryptionMode = 0;
    uint8_t callEncryptionKey = 0;

};

}
