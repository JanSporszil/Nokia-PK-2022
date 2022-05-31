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
    bool isViewed() const;
    bool isFailed() const;
    void markAsFailed();
    const std::string getTitle() const;
    const std::string &getContent() const;

};
