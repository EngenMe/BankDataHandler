#pragma once

#include <iomanip>      // Include header for setw() and left manipulators
#include "clsClient.h"  // Include header file for clsClient class
#include "clsScreen.h"  // Include header file for clsScreen class

class clsClientsListScreen : protected clsScreen
{
public:
    // Static method to display the list of clients
    static void ShowClientsList()
    {
        // Check if current user has permission to list clients
        if (current_user.CheckAccessPermission(clsUser::enPermissions::list_clients) ==
            clsUser::enAccessPermission::denied)
        {
            AccessDeniedScreen();  // Display access denied screen and return
            return;
        }

        system("cls");  // Clear the console screen

        // Retrieve the list of clients from the clsClient class
        std::vector<clsClient> v_clients = clsClient::GetClientsList();

        // Print the header of the clients list table
        PrintHead("Clients List", enTableMode::long_table, v_clients.size(), "Client");

        // Print column headers with formatting using setw() and left manipulators
        std::cout << "| " << std::left << std::setw(15) << "Account Number";
        std::cout << "| " << std::left << std::setw(20) << "First Name";
        std::cout << "| " << std::left << std::setw(15) << "Last Name";
        std::cout << "| " << std::left << std::setw(25) << "Full Name";
        std::cout << "| " << std::left << std::setw(25) << "Email";
        std::cout << "| " << std::left << std::setw(15) << "Phone Number";
        std::cout << "| " << std::left << std::setw(15) << "Account Balance";

        // Print separator line
        std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------\n";

        // Iterate through each client and print their information
        for (int i = 0; i < v_clients.size(); i++)
        {
            clsClient client = v_clients[i];  // Get current client object

            // Print client information with appropriate formatting
            std::cout << "| " << std::left << std::setw(15) << client.GetAccountNumber();
            std::cout << "| " << std::left << std::setw(20) << client.first_name;
            std::cout << "| " << std::left << std::setw(15) << client.last_name;
            std::cout << "| " << std::left << std::setw(25) << client.GetFullName();
            std::cout << "| " << std::left << std::setw(25) << client.email;
            std::cout << "| " << std::left << std::setw(15) << client.phone;
            std::cout << "| " << std::left << std::setw(15) << client.balance;

            std::cout << std::endl;  // Move to the next line after printing client information
        }

        // Print footer line
        std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
};
