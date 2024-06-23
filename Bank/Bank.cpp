#include <iostream>       // Include standard input-output stream header
#include "clsLoginScreen.h"  // Include the header file for the clsLoginScreen class

int main()
{
    while (true)  // Infinite loop to keep showing the login screen
    {
        clsLoginScreen::ShowLoginScreen();  // Call the static method ShowLoginScreen() of clsLoginScreen class
    }

    return 0;  // Return 0 to indicate successful execution
}
