#pragma once

#include <iomanip>

#include "clsScreen.h"
#include "clsUser.h"

class clsUsersListScreen : protected clsScreen
{
public:
    // Method to display users list
    static void ShowUsersList()
    {
        // Clear screen
        system("cls");

        // Retrieve list of users
        std::vector<clsUser> v_users = clsUser::GetUsersList();

        // Print header with table mode and count of users
        PrintHead("Users List", enTableMode::long_table, v_users.size(), "User");

        // Print table headers
        std::cout << "| " << std::left << std::setw(15) << "User Name";
        std::cout << "| " << std::left << std::setw(20) << "First Name";
        std::cout << "| " << std::left << std::setw(15) << "Last Name";
        std::cout << "| " << std::left << std::setw(25) << "Full Name";
        std::cout << "| " << std::left << std::setw(25) << "Email";
        std::cout << "| " << std::left << std::setw(15) << "Phone Number";
        std::cout << "| " << std::left << std::setw(15) << "Permissions";

        std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------\n";

        // Iterate over each user and print their details
        for (int i = 0; i < v_users.size(); i++)
        {
            clsUser user = v_users[i];

            std::cout << "| " << std::left << std::setw(15) << user.user_name;
            std::cout << "| " << std::left << std::setw(20) << user.first_name;
            std::cout << "| " << std::left << std::setw(15) << user.last_name;
            std::cout << "| " << std::left << std::setw(25) << user.GetFullName();
            std::cout << "| " << std::left << std::setw(25) << user.email;
            std::cout << "| " << std::left << std::setw(15) << user.phone;
            std::cout << "| " << std::left << std::setw(15) << user.permissions;

            std::cout << std::endl;
        }

        // Print bottom separator line for the table
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
};
