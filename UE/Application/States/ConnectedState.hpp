#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleDisconnected() override;
    void handleSMSReceive(uint8_t mode, std::string content, common::PhoneNumber from, common::PhoneNumber to) override;
    void handleFailedSms() override;
protected:
    virtual void onAcceptClicked();
    virtual void onDeclineClicked();

};

}
