#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
    friend class ApplicationTestSuite;
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer);
    ~Application();

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleSMSReceive(const std::string &, common::PhoneNumber, common::PhoneNumber) override;
    void handleFailedSms() override;
    void handleCallDrop() override;
    void handleUnknownCallNumber() override;
    void handleCallAccepted() override;
    void handleCallRequest(common::PhoneNumber) override;
    void handleUnknownCallAccept() override;
    void handleCallTalkReceive(const std::string&, common::PhoneNumber) override;

private:
    Context context;
    common::PrefixedLogger logger;


};

}
