#include "ConnectedState.hpp"
#include "SendingSmsState.hpp"
#include "NotConnectedState.hpp"
#include "ViewSmsListState.hpp"
#include "IUeGui.hpp"
#include "DialingNumberState.hpp"

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

    if (currentMenuIndex == 0)
    {
        context.setState<SendingSmsState>();
    }
    else if (currentMenuIndex == 1)
    {
        context.setState<ViewSmsListState>();
    }
    else if (currentMenuIndex == 2)
    {
        context.setState<DialingNumberState>();
    }
}

void ConnectedState::onDeclineClicked()
{
    context.logger.logInfo("Decline has been clicked");
}

void ConnectedState::handleFailedSms()
{
    context.user.getSmsDB().markLastAsFailed();
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleSMSReceive(uint8_t mode, std::string content, common::PhoneNumber from, common::PhoneNumber to)
{
    context.user.getSmsDB().addSmsToDB(content, from, to);
}


}
