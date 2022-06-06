#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
protected:
    virtual void onAcceptClicked();
    virtual void onDeclineClicked();
    void handleDisconnected() override;
    void handleSMSReceive(const std::string &content, common::PhoneNumber from, common::PhoneNumber to) override;
    void handleFailedSms() override;
    void handleCallRequest(common::PhoneNumber) override;
};

}
