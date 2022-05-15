#pragma once

#include "AbstractCallingState.hpp"
#include "UeGui/ICallMode.hpp"

namespace ue
{

class TalkingState : public AbstractCallingState
{
private:
    IUeGui::ICallMode& callMode;
    common::PhoneNumber phoneNumber;
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;

public:
    TalkingState(Context& context, common::PhoneNumber phoneNumber);
};

}
