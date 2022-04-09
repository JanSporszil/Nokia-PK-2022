#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "ViewSmsListState.hpp"
#include "IUeGui.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.setAcceptCallback(std::bind(&ConnectedState::onAcceptClicked, this));
    context.user.setRejectCallback(std::bind(&ConnectedState::onDeclineClicked, this));
    context.user.showConnected();
}

void ConnectedState::onAcceptClicked()
{
    int currentMenuIndex = context.user.getCurrentMenuIndex();

    if (currentMenuIndex == 1)
    {
        context.setState<ViewSmsListState>();
    }
}

void ConnectedState::onDeclineClicked()
{
    context.logger.logInfo("Decline has been clicked");
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleSMSReceive(uint8_t mode, std::string content)
{
    context.user.getSmsDB().addReceivedSms(content);
}

}
