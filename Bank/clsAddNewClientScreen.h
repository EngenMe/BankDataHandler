#pragma once

class clsAddNewClientScreen : protected clsScreen
{
public:
    // Static method to handle adding a new client
    static void AddNewClient()
    {
        // Check if current user has permission to add a new client
        if (current_user.CheckAccessPermission(clsUser::enPermissions::add_new_client) ==
            clsUser::enAccessPermission::denied)
        {
            AccessDeniedScreen();  // Display access denied screen and return if permission is denied
            return;
        }

        system("cls");  // Clear screen for better display
        PrintHead("Add New Client");  // Print header for the add new client screen

        // Read account number from user input, handle case where account number already exists
        std::string account_number = ReadAccountNumber("Account Number Already Exist!\n", false);

        // Create a new client object with the given account number
        clsClient new_client = clsClient::NewClientObj(account_number);

        // Read additional client information from user input
        ReadClientInfo(new_client);

        // Attempt to save the new client information
        clsClient::enSave save = new_client.Save();

        // Handle different outcomes of the save operation
        switch (save)
        {
        case clsClient::enSave::success:
            std::cout << "\nAccount Added Successfully :)\n";
            PrintClientCard(new_client);  // Print client card details upon successful addition
            break;
        case clsClient::enSave::failed_empty_obj:
            std::cout << "\nError - Empty Account!\n";  // Error message for empty client object
            break;
        case clsClient::enSave::failed_already_exist:
            std::cout << "\nError - Account Already Exist!\n";  // Error message for existing account
            break;
        }
    }
};
