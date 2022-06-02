#include "ConnectedState.hpp"
#include "SendingSmsState.hpp"
#include "NotConnectedState.hpp"
#include "ViewSmsListState.hpp"
#include "IUeGui.hpp"
#include "DialingNumberState.hpp"
#include "ReceivingCallState.hpp"
#include "Ports/UserPort.hpp"
namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.setAcceptCallback([this](){this->onAcceptClicked();});
    context.user.setRejectCallback([this](){this->onDeclineClicked();});
    context.user.showConnected();
}

void ConnectedState::onAcceptClicked()
{
    int currentMenuIndex = context.user.getCurrentMenuIndex();

    if (currentMenuIndex == UserPort::MenuList::COMPOSE_SMS)
    {
        context.setState<SendingSmsState>();
    }
    else if (currentMenuIndex == UserPort::MenuList::VIEW_SMS)
    {
        context.setState<ViewSmsListState>();
    }
    else if (currentMenuIndex == UserPort::MenuList::CALL)
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

void ConnectedState::handleCallRequest(common::PhoneNumber number)
{
    context.setState<ReceivingCallState>(number);
}

void ConnectedState::handleDisconnected()
{
    context.setState<NotConnectedState>();
}

void ConnectedState::handleSMSReceive(const std::string &content, common::PhoneNumber from, common::PhoneNumber to)
{
    context.user.getSmsDB().addSmsToDB(content, from, to, false);
}


}
