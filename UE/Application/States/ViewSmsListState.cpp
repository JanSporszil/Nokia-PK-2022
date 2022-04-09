#include "ViewSmsListState.hpp"
#include "ConnectedState.hpp"
#include "ViewingSmsState.hpp"

namespace ue
{
ViewSmsListState::ViewSmsListState(Context &context)
    : ConnectedState(context)
{
    context.user.showSmsList();
}

void ViewSmsListState::onAcceptClicked()
{
    int currentMenuIndex = context.user.getCurrentMenuIndex();
    context.setState<ViewingSmsState>(currentMenuIndex);
}

void ViewSmsListState::onDeclineClicked()
{
    context.setState<ConnectedState>();
}


}
