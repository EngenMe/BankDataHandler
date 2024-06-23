#pragma once

#include "clsBool.h"  // Include header file for clsBool class

class clsDeleteClientScreen : protected clsScreen  // Class definition inheriting clsScreen protectedly
{
public:
    static void DeleteClient()  // Static method to delete a client
    {
        if (current_user.CheckAccessPermission(clsUser::enPermissions::delete_client) == clsUser::enAccessPermission::denied)  // Check delete permission
        {
            AccessDeniedScreen();  // Access denied screen
            return;  // Exit function
        }

        system("cls");  // Clear screen
        PrintHead("Delete Client");  // Print heading

        std::string account_number = ReadAccountNumber("Client not found - Invalid account number!\n", true);  // Read account number

        clsClient client = clsClient::Find(account_number);  // Find client
        PrintClientCard(client);  // Print client card

        if (!clsBool::GetYesNo("Do you want to delete this client (Y/N)? "))  // Confirm deletion
        {
            std::cout << "Cancelled! - ";  // Cancelled message
            return;  // Exit function
        }

        if (client.Delete())  // Delete client
        {
            std::cout << "\nClient Deleted Successfully :)\n";  // Success message
            PrintClientCard(client);  // Print updated client card
        }
        else
            std::cout << "\nError - Client Not Deleted!\n";  // Error message
    }
};
