#include "Sms.hpp"

Sms::Sms(std::string content, common::PhoneNumber phoneNumberFrom, common::PhoneNumber phoneNumberTo, bool viewed, bool failed ):
    content(content), from(phoneNumberFrom), to(phoneNumberTo), viewed(viewed), failed(failed)
{
}

void Sms::markAsViewed()
{
    viewed = true;
}

void Sms::markAsFailed()
{
    failed = true;
}

const std::string &Sms::getContent() const
{
    return content;
}
