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
    virtual void showConnected(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback) = 0;
    virtual void viewSmsList() = 0;
    virtual void showSmsList(IUeGui::Callback acceptCallback, IUeGui::Callback declineCallback) = 0;
    virtual SmsDB& getSmsDB() = 0;
    virtual int getCurrentMenuIndex() = 0;
};

}
