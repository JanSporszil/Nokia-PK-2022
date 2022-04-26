#pragma once
#include <string>
#include "Messages/PhoneNumber.hpp"

struct Sms
{
private:
    std::string content;
    common::PhoneNumber from;
    common::PhoneNumber to;
    bool viewed;
    bool failed;

public:
    Sms(std::string , common::PhoneNumber , common::PhoneNumber , bool = false, bool = false);
    void markAsViewed();
    bool isViewed();
    void markAsFailed();
    const std::string &getContent() const;

};
