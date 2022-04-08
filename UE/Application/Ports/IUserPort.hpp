#pragma once
#include <Utils/SmsDB.hpp>

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
    virtual SmsDB& getSmsDB() = 0;

private:
    virtual void showSmsList() = 0;
};

}
