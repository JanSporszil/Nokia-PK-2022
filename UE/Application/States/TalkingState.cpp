#include "AbstractCallingState.hpp"
#include "TalkingState.hpp"

namespace ue
{
TalkingState::TalkingState(Context &context, common::PhoneNumber phoneNumber)
    : AbstractCallingState(context), callMode(context.user.showCallMode()), phoneNumber(phoneNumber)
{
    callMode.clearIncomingText();
    callMode.clearOutgoingText();

    callMode.appendIncomingText("Connected with " + common::to_string(phoneNumber));
}

void TalkingState::onAcceptClicked()
{

}

void TalkingState::onDeclineClicked()
{
    context.bts.sendDropCall(phoneNumber);
    context.setState<ConnectedState>();
}

}
