#include "AbstractCallingState.hpp"
#include "MakingCallState.hpp"
#include "TalkingState.hpp"

namespace ue
{
MakingCallState::MakingCallState(Context &context, common::PhoneNumber phoneNumber)
    : AbstractCallingState(context), alertMode(context.user.showAlertMode()), phoneNumber(phoneNumber)
{
    alertMode.setText("Calling " + common::to_string(phoneNumber) + "...");
    context.bts.sendCallRequest(phoneNumber);
    using namespace std::chrono_literals;
    context.timer.startTimer(60s);
}

void MakingCallState::onAcceptClicked()
{

}

void MakingCallState::onDeclineClicked()
{
    context.bts.sendDropCall(phoneNumber);
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void MakingCallState::handleUnknownCallNumber()
{
    context.timer.stopTimer();
    alertMode.setText("This number does not exist");
}

void MakingCallState::handleTimeout()
{
    context.setState<ConnectedState>();
}

void MakingCallState::handleCallAccepted()
{
    context.setState<TalkingState>(phoneNumber);
}

}
