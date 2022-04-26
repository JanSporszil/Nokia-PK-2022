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
    void addSmsToDB(std::string, common::PhoneNumber, common::PhoneNumber, bool = false);
    const std::vector<Sms> &getSmsList();
    std::optional<Sms> retrieveSms(int);
    void markLastAsFailed();
};

}
