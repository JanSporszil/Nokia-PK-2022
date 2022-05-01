#include "SmsDB.hpp"
ue::SmsDB::SmsDB()
{
}

void ue::SmsDB::addSmsToDB(
        std::string content,
        common::PhoneNumber phoneNumberFrom,
        common::PhoneNumber phoneNumberTo,
        bool viewed)
{
    smsList.push_back(Sms{content, phoneNumberFrom, phoneNumberTo, viewed});
}

const std::vector<Sms> &ue::SmsDB::getSmsList()
{
    return smsList;
}

std::optional<Sms> ue::SmsDB::retrieveSms(int index)
{
    if (index < 0 || index >= smsList.size())
    {
        return {};
    }

    smsList[index].markAsViewed();
    return smsList[index];
}

void ue::SmsDB::markLastAsFailed()
{
    if( smsList.empty() )
    {
        return;
    }

    smsList.back().markAsFailed();

}
