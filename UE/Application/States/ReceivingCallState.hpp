#pragma once

#include "AbstractCallingState.hpp"
#include "UeGui/ITextMode.hpp"

namespace ue
{

class ReceivingCallState : public AbstractCallingState
{
private:
    IUeGui::ITextMode& alertMode;
    common::PhoneNumber phoneNumber;
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
    void handleTimeout() override;
    void handleUnknownCallAccept() override;
    void handleCallRequest(common::PhoneNumber) override;

public:
    ReceivingCallState(Context& context, common::PhoneNumber phoneNumber);
};

}
