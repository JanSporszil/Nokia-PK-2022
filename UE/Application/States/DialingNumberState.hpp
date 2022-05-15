#pragma once

#include "ConnectedState.hpp"
#include "UeGui/IDialMode.hpp"

namespace ue
{

class DialingNumberState : public ConnectedState
{
private:
    IUeGui::IDialMode& dialMode;
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
public:
    DialingNumberState(Context& context);
};

}
