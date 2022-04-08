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
    void showConnected() override;
    void viewSmsList() override;
    virtual SmsDB &getSmsDB() override;

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    SmsDB smsDB;

    void onAcceptClicked(IUeGui::IListViewMode& menu);
    void showSms(IUeGui::IListViewMode& menu);
    void showSmsList() override;
    void viewSms(Sms sms);
};

}
