#include "ConnectedState.hpp"
#include "DialingNumberState.hpp"
#include "MakingCallState.hpp"
#include "IUeGui.hpp"

namespace ue
{
DialingNumberState::DialingNumberState(Context &context)
    : ConnectedState(context), dialMode(context.user.showDialMode())
{

}

void DialingNumberState::onAcceptClicked()
{
    context.setState<MakingCallState>(dialMode.getPhoneNumber());
}

void DialingNumberState::onDeclineClicked()
{
    context.setState<ConnectedState>();
}

}
