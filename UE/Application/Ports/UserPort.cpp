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

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    gui.setAcceptCallback(std::bind(&UserPort::onAcceptClicked, this, std::ref(menu)));
}

void UserPort::viewSmsList()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for (auto& sms : smsDB.getSmsList())
    {
        menu.addSelectionListItem(sms.getContent(), "");
    }

    gui.setAcceptCallback(std::bind(&UserPort::showSms, this, std::ref(menu)));
}

SmsDB &UserPort::getSmsDB()
{
    return smsDB;
}

void UserPort::showSmsList()
{
    viewSmsList();
}

void UserPort::viewSms(Sms sms)
{
    IUeGui::ITextMode& text = gui.setViewTextMode();
    text.setText(sms.getContent());
}

void UserPort::onAcceptClicked(IUeGui::IListViewMode& menu)
{
    auto selection = menu.getCurrentItemIndex();

    if (!selection.first)
    {
        return;
    }

    if (selection.second == 1)
    {
        showSmsList();
    }
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
