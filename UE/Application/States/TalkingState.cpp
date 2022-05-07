#include "AbstractCallingState.hpp"
#include "TalkingState.hpp"

namespace ue
{
TalkingState::TalkingState(Context &context, common::PhoneNumber phoneNumber)
    : AbstractCallingState(context), callMode(context.user.showCallMode()), phoneNumber(phoneNumber)
{

}

void TalkingState::onAcceptClicked()
{

}

void TalkingState::onDeclineClicked()
{

}

}
