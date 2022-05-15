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
    void resetTimer();
protected:
    void onAcceptClicked() override;
    void onDeclineClicked() override;
    void handleCallTalkReceive(const std::string&, common::PhoneNumber) override;
    void handleTimeout() override;

public:
    TalkingState(Context& context, common::PhoneNumber phoneNumber);
};

}
