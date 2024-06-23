#pragma once

class clsUpdateClientScreen : protected clsScreen
{
public:
    // Public function to update client information
    static void UpdateClient()
    {
        // Check if current user has permission to update client information
        if (current_user.CheckAccessPermission(clsUser::enPermissions::update_client) ==
            clsUser::enAccessPermission::denied)
        {
            AccessDeniedScreen(); // Display access denied screen if permission is denied
            return;
        }

        system("cls"); // Clear console screen
        PrintHead("Update Client"); // Print screen header

        // Prompt user to enter account number to update client
        std::string account_number = ReadAccountNumber("Client not found, Invalid account number!\n", true);

        // Find client object based on entered account number
        clsClient client = clsClient::Find(account_number);

        // Display client information card
        PrintClientCard(client);

        // Confirmation prompt to update client
        if (!clsBool::GetYesNo("Do you want to update this client (Y/N)? "))
        {
            std::cout << "Cancelled! - "; // Display cancellation message if user declines
            return;
        }

        ReadClientInfo(client); // Read updated client information from user input

        // Save updated client information and handle save status
        clsClient::enSave save = client.Save();

        switch (save)
        {
        case clsClient::enSave::success:
            std::cout << "\nAccount Updated Successfully :)\n"; // Display success message on successful update
            PrintClientCard(client); // Print updated client card
            break;
        case clsClient::enSave::failed_empty_obj:
            std::cout << "\nError - Empty Account!\n"; // Display error message if client object is empty
        }
    }
};

