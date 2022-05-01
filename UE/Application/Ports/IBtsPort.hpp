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

};

class IBtsPort
{
public:

    virtual ~IBtsPort() = default;
    virtual common::PhoneNumber getMyPhoneNumber() = 0;
    virtual void sendSms(common::PhoneNumber, std::string, int) = 0;
    virtual void sendAttachRequest(common::BtsId) = 0;
};

}
