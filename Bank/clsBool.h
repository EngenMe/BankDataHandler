#pragma once

#include "clsChar.h"  // Include the header file for clsChar class

class clsBool
{
private:
    std::vector<char> _arr_yes = { 'Y', 'y' };  // Private member variable to store characters considered as 'yes'

public:
    // Static method to check if a character is in a vector of characters
    static bool IsIn(char char_to_be_verified, std::vector<char> arr_of_chars)
    {
        for (char c : arr_of_chars)
        {
            if (c == char_to_be_verified)
                return true;  // Return true if the character is found in the vector
        }

        return false;  // Return false if the character is not found in the vector
    }

    // Static method to get user input for yes/no and return true/false based on user input
    static bool GetYesNo(std::string message = "")
    {
        std::cout << message;  // Print optional message provided by the caller

        clsBool cls_bool;  // Create an instance of clsBool to access _arr_yes

        // Read a character input from the user and check if it is in _arr_yes
        return clsBool::IsIn(clsChar::ReadChar(), cls_bool._arr_yes);
    }
};
