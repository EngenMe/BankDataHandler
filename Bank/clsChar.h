#pragma once

#include <iostream>  // Include standard input-output stream header for cin and cout

class clsChar
{
private:
    char _char;  // Private member variable to store a single character

public:
    // Static method to read a single character from standard input (cin)
    static char ReadChar(std::string message = "")
    {
        clsChar cls_char;  // Create an instance of clsChar to access _char

        std::cout << message;  // Print optional message provided by the caller

        std::cin >> cls_char._char;  // Read a single character from standard input (keyboard)

        return cls_char._char;  // Return the read character
    }
};
