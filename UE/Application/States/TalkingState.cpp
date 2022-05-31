#include "AbstractCallingState.hpp"
#include "TalkingState.hpp"
#include "ClosingState.hpp"

namespace ue
{
TalkingState::TalkingState(Context &context, common::PhoneNumber phoneNumber)
    : AbstractCallingState(context), callMode(context.user.showCallMode()), phoneNumber(phoneNumber)
{
    callMode.clearIncomingText();
    callMode.clearOutgoingText();

    callMode.appendIncomingText("Connected with " + common::to_string(phoneNumber));

    resetTimer();

    context.user.setCloseGuard([&](){
        context.bts.sendDropCall(this->phoneNumber);
        context.setState<ClosingState>();
        return false;
    });
}

void TalkingState::resetTimer()
{
    context.timer.stopTimer();
    using namespace std::chrono_literals;
    context.timer.startTimer(2min);
}

void TalkingState::onAcceptClicked()
{
    resetTimer();
    callMode.appendIncomingText("[" + common::to_string(context.bts.getMyPhoneNumber()) + "]: " + callMode.getOutgoingText());
    context.bts.sendCallTalk(callMode.getOutgoingText(), phoneNumber);
    callMode.clearOutgoingText();
}

void TalkingState::onDeclineClicked()
{
    context.timer.stopTimer();
    context.bts.sendDropCall(phoneNumber);
    context.setState<ConnectedState>();
}

void TalkingState::handleCallTalkReceive(const std::string& content, common::PhoneNumber from)
{
    resetTimer();
    callMode.appendIncomingText("[" + common::to_string(from) + "]: " + content);
}

void TalkingState::handleTimeout()
{
    context.bts.sendDropCall(phoneNumber);
    context.setState<ConnectedState>();
}

void TalkingState::handleCallRequest(common::PhoneNumber from)
{
    if (from != phoneNumber) {
        context.bts.sendDropCall(from);
    }
}

}
