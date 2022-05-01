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

void ViewSmsListState::handleSMSReceive(uint8_t mode, std::string content, common::PhoneNumber from, common::PhoneNumber to)
{
    ConnectedState::handleSMSReceive(mode, content, from, to);
    context.setState<ViewSmsListState>();
}



}
