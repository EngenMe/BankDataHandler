#pragma once

#include <string>

class clsPerson
{
private:
    // Private member variables to store personal information
    std::string _first_name; // First name of the person
    std::string _last_name;  // Last name of the person
    std::string _email;      // Email address of the person
    std::string _phone;      // Phone number of the person

public:
    // Constructor to initialize the person object with provided details
    clsPerson(std::string first_name, std::string last_name, std::string email, std::string phone)
        : _first_name(first_name), _last_name(last_name), _email(email), _phone(phone)
    {
    }

    // Setter methods for each member variable
    void SetFirstName(std::string first_name)
    {
        _first_name = first_name; // Set the first name of the person
    }
    void SetLastName(std::string last_name)
    {
        _last_name = last_name;   // Set the last name of the person
    }
    void SetEmail(std::string email)
    {
        _email = email;           // Set the email address of the person
    }
    void SetPhone(std::string phone)
    {
        _phone = phone;           // Set the phone number of the person
    }

    // Getter methods for each member variable
    std::string GetFirstName()
    {
        return _first_name;       // Retrieve the first name of the person
    }
    std::string GetLastName()
    {
        return _last_name;        // Retrieve the last name of the person
    }
    std::string GetEmail()
    {
        return _email;            // Retrieve the email address of the person
    }
    std::string GetPhone()
    {
        return _phone;            // Retrieve the phone number of the person
    }

    // Properties using __declspec(property)
    // These properties provide convenient access to member variables using getter and setter methods
    __declspec(property(get = GetFirstName, put = SetFirstName)) std::string first_name;
    __declspec(property(get = GetLastName, put = SetLastName)) std::string last_name;
    __declspec(property(get = GetEmail, put = SetEmail)) std::string email;
    __declspec(property(get = GetPhone, put = SetPhone)) std::string phone;

    // Method to retrieve full name of the person by concatenating first and last names
    std::string GetFullName()
    {
        return _first_name + " " + _last_name; // Concatenate first and last names with a space
    }
};
