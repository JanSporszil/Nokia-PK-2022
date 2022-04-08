#pragma once
#include <string>
#include <vector>
#include <optional>
#include <Utils/Sms.hpp>

namespace ue
{

class SmsDB
{
private:
    std::vector<Sms> smsList;
public:
    SmsDB();
    void addReceivedSms(std::string);
    const std::vector<Sms> &getSmsList();
    std::optional<Sms> retrieveSms(int index);
};

}
