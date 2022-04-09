#include "Sms.hpp"

Sms::Sms()
{
    content = "Test";
}

void Sms::markAsViewed()
{
    viewed = true;
}

const std::string &Sms::getContent() const
{
    return content;
}
