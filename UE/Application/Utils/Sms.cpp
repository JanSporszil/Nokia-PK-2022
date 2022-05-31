#include "Sms.hpp"

Sms::Sms(std::string content, common::PhoneNumber phoneNumberFrom, common::PhoneNumber phoneNumberTo, bool viewed, bool failed ):
    content(content), from(phoneNumberFrom), to(phoneNumberTo), viewed(viewed), failed(failed)
{
}

void Sms::markAsViewed()
{
    viewed = true;
}

bool Sms::isFailed() const
{
    return failed;
}

bool Sms::isViewed() const
{
    return viewed;
}

void Sms::markAsFailed()
{
    failed = true;
}

const std::string &Sms::getContent() const
{
    return content;
}

const std::string Sms::getTitle() const
{
    return common::to_string(from) + " -> " + common::to_string(to);
}
