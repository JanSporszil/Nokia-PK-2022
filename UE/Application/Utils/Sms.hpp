#pragma once
#include <string>
#include "Messages/PhoneNumber.hpp"

struct Sms
{
    std::string content;
    common::PhoneNumber from;
    common::PhoneNumber to;
    bool isViewed;
};
