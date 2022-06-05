#pragma once

#include <gmock/gmock.h>
#include "Utils/SmsDB.hpp"

namespace ue
{
class SmsDBMock : public SmsDB
{
public:
    SmsDBMock();
    ~SmsDBMock();

    MOCK_METHOD(const std::vector<Sms> &, getSmsList, (), ());
};
}
