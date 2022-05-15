#pragma once
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"

namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleDisconnected() override;
    void handleSMSReceive(uint8_t mode, std::string content, common::PhoneNumber from, common::PhoneNumber to) override;
    void handleFailedSms() override;
    void handleCallDrop() override;
    void handleUnknownCallNumber() override;
    void handleCallAccepted() override;

protected:
    Context& context;
    common::PrefixedLogger logger;


};

}
