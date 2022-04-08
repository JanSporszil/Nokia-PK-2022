#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"

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

void UserPort::showConnected(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback)
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    this->acceptStateCallback = acceptCallback;
    gui.setAcceptCallback(std::bind(&UserPort::onAcceptClickedWhenMenuActivated, this, std::ref(menu)));
    gui.setRejectCallback(declineCallback);
}

void UserPort::viewSmsList(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback)
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for (auto& sms : smsDB.getSmsList())
    {
        menu.addSelectionListItem(sms.getContent(), "");
    }

    gui.setAcceptCallback(std::bind(&UserPort::onAcceptClickedWhenMenuActivated, this, std::ref(menu)));
    gui.setRejectCallback(declineCallback);
}

SmsDB &UserPort::getSmsDB()
{
    return smsDB;
}

int UserPort::getCurrentMenuIndex()
{
    return currentMenuIndex;
}

void UserPort::showSmsList(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback)
{
    viewSmsList(acceptCallback, declineCallback);
}

void UserPort::viewSms(Sms sms)
{
    IUeGui::ITextMode& text = gui.setViewTextMode();
    text.setText(sms.getContent());
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

void UserPort::showSms(IUeGui::IListViewMode &menu)
{
    auto selection = menu.getCurrentItemIndex();

    if (!selection.first)
    {
        return;
    }

    std::optional<Sms> sms = smsDB.retrieveSms(selection.second);

    if (!sms.has_value())
    {
        return;
    }

    viewSms(sms.value());
}

}
