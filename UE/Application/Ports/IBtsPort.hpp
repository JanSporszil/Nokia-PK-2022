#pragma once
#include <string>
#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleDisconnected() = 0;
    virtual void handleSMSReceive(uint8_t, std::string, common::PhoneNumber, common::PhoneNumber) = 0;
    virtual void handleFailedSms() = 0;
    virtual void handleCallDrop() = 0;
    virtual void handleUnknownCallNumber() = 0;
    virtual void handleCallAccepted() = 0;
    virtual void handleCallRequest(common::PhoneNumber) = 0;
    virtual void handleUnknownCallAccept() = 0;
    virtual void handleCallTalkReceive(const std::string&, common::PhoneNumber) = 0;

};

class IBtsPort
{
public:

    virtual ~IBtsPort() = default;
    virtual common::PhoneNumber getMyPhoneNumber() = 0;
    virtual void sendSms(common::PhoneNumber, std::string, int) = 0;
    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendCallRequest(common::PhoneNumber) = 0;
    virtual void sendDropCall(common::PhoneNumber) = 0;
    virtual void sendCallAccepted(common::PhoneNumber) = 0;
    virtual void sendCallTalk(const std::string&, common::PhoneNumber) = 0;
};

}
