#pragma once

#include "clsLogs.h"  // Include header file for clsLogs class

class clsLoginRegisterScreen : protected clsScreen  // Class definition inheriting clsScreen protectedly
{
public:
	static void ShowLoginRegister()  // Static method to show login register information
	{
		if (current_user.CheckAccessPermission(clsUser::enPermissions::login_register) ==  // Check permission for login/register
			clsUser::enAccessPermission::denied)
		{
			AccessDeniedScreen();  // Display access denied screen if permission is denied
			return;
		}

		system("cls");  // Clear screen

		std::vector<clsLogs> v_login_register = clsLogs::GetLoginRegister();  // Retrieve login/register records

		PrintHead("Login Register", enTableMode::short_table, v_login_register.size(), "Record");  // Print header for login register table

		// Print table headers
		std::cout << "| " << std::left << std::setw(25) << "Date / Time";
		std::cout << "| " << std::left << std::setw(20) << "Username";
		std::cout << "| " << std::left << std::setw(15) << "Password";
		std::cout << "| " << std::left << std::setw(25) << "Permissions";

		std::cout << "\n--------------------------------------------------------------------------------------------\n";

		// Print each record from the vector
		for (int i = 0; i < v_login_register.size(); i++)
		{
			clsLogs login_register = v_login_register[i];  // Get each login/register record

			// Print record details
			std::cout << "| " << std::left << std::setw(25) << login_register.date_time;
			std::cout << "| " << std::left << std::setw(20) << login_register.user.user_name;
			std::cout << "| " << std::left << std::setw(15) << login_register.user.password;
			std::cout << "| " << std::left << std::setw(25) << login_register.user.permissions;

			std::cout << std::endl;  // Move to the next line
		}

		std::cout << "\n--------------------------------------------------------------------------------------------\n";
	}
};
