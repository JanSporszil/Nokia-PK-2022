#include "SmsDB.hpp"
ue::SmsDB::SmsDB()
{
    smsList.push_back(Sms());
}

void ue::SmsDB::addReceivedSms(std::string content)
{

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
