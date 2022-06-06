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
    void showSmsList() override;
    void viewSmsList() override;
    void showSms(int index) override;
    SmsDB &getSmsDB() override;
    int getCurrentMenuIndex() override;
    void clearCallMode() override;
    void setAcceptCallback(IUeGui::Callback acceptCallback) override;
    void setRejectCallback(IUeGui::Callback rejectCallback) override;
    void setCloseGuard(IUeGui::CloseGuard closeGuard) override;
    IUeGui::ISmsComposeMode& showComposeSms() override;
    IUeGui::IDialMode& showDialMode() override;
    IUeGui::ICallMode& showCallMode() override;
    IUeGui::ITextMode& showAlertMode() override;

private:
    common::PrefixedLogger logger;
    IUeGui& gui;
    IUeGui::Callback acceptStateCallback;

    common::PhoneNumber phoneNumber;
    IUserEventsHandler* handler = nullptr;
    SmsDB smsDB;

    int currentMenuIndex = -1;

    void onAcceptClickedWhenMenuActivated(IUeGui::IListViewMode& menu);
    void viewSms(int index);
};

}
