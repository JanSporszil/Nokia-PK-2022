#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include <Utils/SmsDB.hpp>

namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback) override;
    void showSmsList(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback) override;
    virtual SmsDB &getSmsDB() override;
    int getCurrentMenuIndex();

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    IUeGui::Callback acceptStateCallback;

    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    SmsDB smsDB;

    int currentMenuIndex = -1;

    void onAcceptClickedWhenMenuActivated(IUeGui::IListViewMode& menu);
    void showSms(IUeGui::IListViewMode& menu);
    void viewSms(Sms sms);
    void viewSmsList(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback) override;
};

}
