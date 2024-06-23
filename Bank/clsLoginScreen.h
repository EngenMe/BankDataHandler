#pragma once

#include <fstream>  // File stream operations
#include <string>   // String operations

#include "clsScreen.h"      // Include header file for clsScreen class
#include "clsMainScreen.h"  // Include header file for clsMainScreen class
#include "Global.h"         // Include header file for global declarations

class clsLoginScreen : protected clsScreen  // Class definition inheriting clsScreen protectedly
{
private:
	static void _Login()  // Private static method for handling login process
	{
		bool login_failed = false;  // Flag to track if login failed
		std::string user_name;      // Variable to store username
		std::string password;       // Variable to store password

		short remain_trials = 3;    // Number of login attempts allowed
		do
		{
			if (login_failed)
			{
				if (remain_trials == 0)
				{
					std::cout << "\nYou are locked!\n\n";  // Display message if locked out
					exit(0);  // Exit the program
				}
				std::cout << "\nInvalid Username/Password!\n";  // Display message for invalid credentials
				std::cout << "You have " << remain_trials << " trials to login\n\n";  // Display remaining login attempts
			}

			user_name = clsString::ReadString("Enter Username: ");  // Read username from user
			password = clsString::ReadString("Enter Password: ");  // Read password from user

			current_user = clsUser::Find(user_name, password);  // Attempt to find user with provided credentials
			login_failed = current_user.IsEmpty();  // Check if user was found (login failed if true)
			remain_trials--;  // Decrement remaining login attempts
		} while (login_failed);

		clsLogs::RegisterLogin();  // Register login in system logs
		clsMainScreen::DisplayMainMenueScreen();  // Display main menu screen after successful login
	}

public:
	static void ShowLoginScreen()  // Static method to display login screen
	{
		system("cls");  // Clear the screen
		PrintHead("Login");  // Print header for login screen
		_Login();  // Execute the login process
	}
};
