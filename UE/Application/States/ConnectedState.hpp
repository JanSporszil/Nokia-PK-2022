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
public:
    void handleDisconnected() override;
    void handleSMSReceive(uint8_t mode, std::string content) override;
};

}
