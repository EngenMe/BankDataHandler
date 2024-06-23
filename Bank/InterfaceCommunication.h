#pragma once

#include <string>

// Abstract class InterfaceCommunication
class InterfaceCommunication
{
public:
    // Pure virtual method to send an email
    virtual void SendEmail(std::string destination_email, std::string title, std::string body) = 0;

    // Pure virtual method to send an SMS
    virtual void SendSMS(std::string destination_phone, std::string body) = 0;
};

