#pragma once
#include <Utils/SmsDB.hpp>
#include <IUeGui.hpp>

namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void viewSmsList() = 0;
    virtual void showSmsList() = 0;
    virtual void showSms(int index) = 0;
    virtual SmsDB& getSmsDB() = 0;
    virtual int getCurrentMenuIndex() = 0;
    virtual void setAcceptCallback(IUeGui::Callback acceptCallback) = 0;
    virtual void setRejectCallback(IUeGui::Callback rejectCallback) = 0;
    virtual IUeGui::ISmsComposeMode& showComposeSms() = 0;
    virtual IUeGui::IDialMode& showDialMode() = 0;
    virtual IUeGui::ICallMode& showCallMode() = 0;
    virtual IUeGui::ITextMode& showAlertMode() = 0;

};

}
