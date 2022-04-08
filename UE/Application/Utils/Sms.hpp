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

public:
    Sms();
    void markAsViewed();
    bool isViewed();
    const std::string &getContent() const;
};
