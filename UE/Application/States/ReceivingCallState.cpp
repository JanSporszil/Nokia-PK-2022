#include "AbstractCallingState.hpp"
#include "ReceivingCallState.hpp"
#include "TalkingState.hpp"
#include "ClosingState.hpp"

namespace ue
{
ReceivingCallState::ReceivingCallState(Context &context, common::PhoneNumber phoneNumber)
    : AbstractCallingState(context), alertMode(context.user.showAlertMode()), phoneNumber(phoneNumber)
{
    alertMode.setText("Incoming call from " + common::to_string(phoneNumber) + "...");
    using namespace std::chrono_literals;
    context.timer.startTimer(60s);

    context.user.setCloseGuard([&](){
        context.bts.sendDropCall(this->phoneNumber);
        context.setState<ClosingState>();
        return false;
    });
}


void ReceivingCallState::onAcceptClicked()
{
    context.bts.sendCallAccepted(phoneNumber);
    context.timer.stopTimer();
    context.setState<TalkingState>(phoneNumber);
}

void ReceivingCallState::onDeclineClicked()
{
    context.bts.sendDropCall(phoneNumber);
    context.timer.stopTimer();
    context.setState<ConnectedState>();
}

void ReceivingCallState::handleTimeout()
{
    context.bts.sendDropCall(phoneNumber);
    context.setState<ConnectedState>();
}

void ReceivingCallState::handleUnknownCallAccept()
{
    alertMode.setText("This number is no longer conntected to BTS");
    context.timer.stopTimer();
}

void ReceivingCallState::handleCallRequest(common::PhoneNumber from)
{
    if (from != phoneNumber) {
        context.bts.sendDropCall(from);
    }
}

}
