#include "ConnectedState.hpp"
#include "SendingSmsState.hpp"
#include "IUeGui.hpp"

namespace ue
{
SendingSmsState::SendingSmsState(Context &context)
    : ConnectedState(context), composeMode(context.user.showComposeSms() )
{
    composeMode.clearSmsText();
}

void SendingSmsState::onAcceptClicked()
{
    std::string content = composeMode.getSmsText();
    common::PhoneNumber numberTo = composeMode.getPhoneNumber();

    context.user.getSmsDB().addSmsToDB(content, context.bts.getMyPhoneNumber(), numberTo, true);
    context.bts.sendSms(numberTo, content, 0);
    context.setState<ConnectedState>();

}

void SendingSmsState::onDeclineClicked()
{
    context.setState<ConnectedState>();
}

}
