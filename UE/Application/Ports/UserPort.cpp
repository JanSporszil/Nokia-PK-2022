#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ICallMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for(int i = 0; i < UNKNOWN; i++)
    {
        if(i == COMPOSE_SMS)
        {
            menu.addSelectionListItem("Compose SMS", "");
        }
        else if(i == VIEW_SMS)
        {
            menu.addSelectionListItem("View SMS", "");
        }
        else if(i == CALL)
        {
            menu.addSelectionListItem("Call", "");
        }
    }
    gui.setAcceptCallback([&menu, this](){this->onAcceptClickedWhenMenuActivated(menu);});
}

void UserPort::viewSmsList()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for (auto& sms : smsDB.getSmsList())
    {
        std::string prefix = "";
        if( sms.isFailed() )
        {
            prefix = "[!] ";
        }
        else if( !sms.isViewed() )
        {
            prefix = "[*] ";
        }

        menu.addSelectionListItem(prefix + sms.getTitle(), sms.getContent());
    }
    gui.setAcceptCallback([&menu, this](){this->onAcceptClickedWhenMenuActivated(menu);});
}

SmsDB &UserPort::getSmsDB()
{
    return smsDB;
}

int UserPort::getCurrentMenuIndex()
{
    return currentMenuIndex;
}

void UserPort::clearCallMode()
{
    IUeGui::ICallMode& callMode = gui.setCallMode();
    callMode.clearIncomingText();
    callMode.clearOutgoingText();
}

void UserPort::setAcceptCallback(IUeGui::Callback acceptCallback)
{
    this->acceptStateCallback = acceptCallback;
    gui.setAcceptCallback(acceptCallback);
}

void UserPort::setRejectCallback(IUeGui::Callback rejectCallback)
{
    gui.setRejectCallback(rejectCallback);
}

void UserPort::setCloseGuard(IUeGui::CloseGuard closeGuard)
{
    gui.setCloseGuard(closeGuard);
}

void UserPort::showSmsList()
{
    viewSmsList();
}

void UserPort::showSms(int index)
{
    viewSms(index);
}

void UserPort::viewSms(int index)
{
    auto sms = smsDB.retrieveSms(index);
    IUeGui::ITextMode& text = gui.setViewTextMode();

    if (sms.has_value())
    {
        text.setText(sms.value().getContent());
    }
}

void UserPort::onAcceptClickedWhenMenuActivated(IUeGui::IListViewMode& menu)
{
    auto selection = menu.getCurrentItemIndex();
    if (!selection.first)
    {
        currentMenuIndex = -1;
    }

    else
    {
        currentMenuIndex = selection.second;
    }

    acceptStateCallback();
}

IUeGui::ISmsComposeMode &UserPort::showComposeSms(){
    return gui.setSmsComposeMode();
}

IUeGui::IDialMode &UserPort::showDialMode()
{
    clearCallMode();
    return gui.setDialMode();
}

IUeGui::ICallMode &UserPort::showCallMode()
{
    return gui.setCallMode();
}

IUeGui::ITextMode &UserPort::showAlertMode()
{
    return gui.setAlertMode();
}


}



