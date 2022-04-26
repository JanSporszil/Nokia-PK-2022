#pragma once

#include "ConnectedState.hpp"
#include "UeGui/ISmsComposeMode.hpp"
namespace ue
{

class SendingSmsState : public ConnectedState
{
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
public:
    SendingSmsState(Context& context);
private:
    IUeGui::ISmsComposeMode& composeMode;
};

}
