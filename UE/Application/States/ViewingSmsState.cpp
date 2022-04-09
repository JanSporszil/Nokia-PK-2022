#include "ViewSmsListState.hpp"
#include "ConnectedState.hpp"
#include "ViewingSmsState.hpp"

namespace ue
{
ViewingSmsState::ViewingSmsState(Context &context, int smsIndex)
    : ConnectedState(context)
{
    context.user.showSms(smsIndex);
}

void ViewingSmsState::onAcceptClicked()
{

}

void ViewingSmsState::onDeclineClicked()
{
    context.setState<ViewSmsListState>();
}

}
