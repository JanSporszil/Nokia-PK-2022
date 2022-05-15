#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleDisconnected, (), (final));
    MOCK_METHOD(void, handleFailedSms, (), (final));
    MOCK_METHOD(void, handleCallDrop, (), (final));
    MOCK_METHOD(void, handleUnknownCallNumber, (), (final));
    MOCK_METHOD(void, handleCallAccepted, (), (final));
    MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleUnknownCallAccept, (), (final));
    MOCK_METHOD(void, handleSMSReceive, (uint8_t, std::string, common::PhoneNumber, common::PhoneNumber), (final));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(common::PhoneNumber, getMyPhoneNumber, (), (final));
    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendSms, (common::PhoneNumber, std::string, int), (final));
    MOCK_METHOD(void, sendCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendDropCall, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendCallAccepted, (common::PhoneNumber), (final));

};

}
