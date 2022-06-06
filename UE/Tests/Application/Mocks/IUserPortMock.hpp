#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"
#include "IUeGui.hpp"

namespace ue
{

class IUserEventsHandlerMock : public IUserEventsHandler
{
public:
    IUserEventsHandlerMock();
    ~IUserEventsHandlerMock() override;

};

class IUserPortMock : public IUserPort
{
public:
    IUserPortMock();
    ~IUserPortMock() override;

    MOCK_METHOD(void, showNotConnected, (), (final));
    MOCK_METHOD(void, showConnecting, (), (final));
    MOCK_METHOD(void, showConnected, (), (final));
    MOCK_METHOD(void, viewSmsList, (), (final));
    MOCK_METHOD(void, showSmsList, (), (final));
    MOCK_METHOD(void, showSms, (int), (final));
    MOCK_METHOD(void, clearCallMode, (), (final));
    MOCK_METHOD(SmsDB&, getSmsDB, (), (final));
    MOCK_METHOD(int, getCurrentMenuIndex, (), (final));
    MOCK_METHOD(void, setAcceptCallback, (IUeGui::Callback), (final));
    MOCK_METHOD(void, setRejectCallback, (IUeGui::Callback), (final));
    MOCK_METHOD(IUeGui::ISmsComposeMode&, showComposeSms, (), (final));
    MOCK_METHOD(IUeGui::IDialMode&, showDialMode, (), (final));
    MOCK_METHOD(IUeGui::ICallMode&, showCallMode, (), (final));
    MOCK_METHOD(IUeGui::ITextMode&, showAlertMode, (), (final));
};

}
