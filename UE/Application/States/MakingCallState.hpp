#pragma once

#include "AbstractCallingState.hpp"
#include "UeGui/ITextMode.hpp"

namespace ue
{

class MakingCallState : public AbstractCallingState
{
private:
    IUeGui::ITextMode& alertMode;
    common::PhoneNumber phoneNumber;
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
    void handleUnknownCallNumber() override;
    void handleTimeout() override;
    void handleCallAccepted() override;

public:
    MakingCallState(Context& context, common::PhoneNumber phoneNumber);
};

}
