#pragma once

#include "clsLogs.h"
#include "clsScreen.h"

class clsTransferScreen : protected clsScreen
{
private:
    // Private function to read transfer amount with validation against maximum balance
    static float _ReadAmount(float balance_max)
    {
        float amount;
        std::string message = "\nEnter transfer amount: ";

        // Loop until valid amount is entered
        while (true)
        {
            amount = clsNumber::ReadFloatNumber(message); // Read amount from user input

            if (amount > balance_max)
            {
                std::cout << "\nAmount Exceed!\n"; // Display error message if amount exceeds maximum balance
                message = "\nEnter another amount: "; // Prompt user to enter another amount
            }
            else
            {
                break; // Break the loop if valid amount is entered
            }
        }

        return amount;
    }

    // Private function to read client information and validate account number
    static clsClient _ReadClient()
    {
        std::string account_number = ReadAccountNumber("Client not found - Invalid account number!\n",
            true, "\nEnter account number to transfer from: "); // Prompt user to enter account number

        clsClient client = clsClient::Find(account_number); // Find client based on account number
        PrintClientCard(client, enClientCardMode::short_card); // Display client card

        return client; // Return the found client object
    }

public:
    // Public function to display transfer screen
    static void ShowTransferScreen()
    {
        system("cls"); // Clear screen
        PrintHead("Transfer Screen"); // Print screen header

        clsClient source_client = _ReadClient(); // Read source client information
        clsClient destination_client = _ReadClient(); // Read destination client information

        float amount = _ReadAmount(source_client.balance); // Read transfer amount from source client

        // Confirmation prompt
        if (!clsBool::GetYesNo("\nDo you want to confirm (Y/N)? "))
        {
            std::cout << "Cancelled!\n"; // Display cancellation message if user declines confirmation
            return;
        }

        clsClient::Transfer(source_client, destination_client, amount); // Perform transfer between clients

        clsLogs::RegisterTransferLog(source_client, destination_client, amount); // Register transfer log
        std::cout << "\nTransfer Done Successfully :)\n"; // Display success message

        PrintClientCard(source_client, enClientCardMode::short_card); // Display updated source client card
        PrintClientCard(destination_client, enClientCardMode::short_card); // Display updated destination client card
        std::cout << std::endl; // Empty line for formatting
    }
};

