#pragma once
#include <string>

namespace ue
{

class SmsDB
{
public:
    SmsDB();
    void addReceivedSms(std::string);
};

}
