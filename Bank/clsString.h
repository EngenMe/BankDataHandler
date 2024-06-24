#pragma once

#include <string>
#include <vector>
#include <iostream>

class clsString
{
private:
    std::string _value;

public:
    // Constructor to initialize with a value
    clsString(std::string value)
    {
        _value = value;
    }

    // Setter for the value
    void SetValue(std::string value)
    {
        _value = value;
    }

    // Getter for the value
    std::string GetValue()
    {
        return _value;
    }

    // Property declaration for easy access to value
    __declspec(property(get = GetValue, put = SetValue)) std::string value;

    // Static function to split a string by a separator
    static std::vector<std::string> Split(std::string str, std::string separator)
    {
        std::vector<std::string> v_string;

        short pos = 0;
        std::string word;

        // Iterate through the string to split by separator
        while ((pos = str.find(separator)) != std::string::npos)
        {
            word = str.substr(0, pos);
            if (!word.empty())
                v_string.push_back(word);

            str.erase(0, pos + separator.length());
        }

        // Push back the remaining string
        if (!str.empty())
        {
            v_string.push_back(str);
        }

        return v_string;
    }

    // Static function to read a string from user input
    static std::string ReadString(std::string message = "")
    {
        if (!message.empty())
            std::cout << message; // Display message if provided

        std::string str;
        std::getline(std::cin >> std::ws, str); // Read input with whitespace trimming

        return str;
    }

    // Static function to return an upper case of a given string
    static std::string UpperAll(std::string str)
    {
        std::string upper_str = "";

        for (char c : str)
        {
            upper_str += std::toupper(c);
        }

        return upper_str;
    }
};

