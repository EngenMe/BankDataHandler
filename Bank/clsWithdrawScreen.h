#pragma once

class clsWithdrawScreen : protected clsScreen
{
public:
	// Method to handle withdrawal process
	static void Withdraw()
	{
		// Clear the screen
		system("cls");

		// Print header for withdrawal screen
		PrintHead("Withdraw");

		// Read the account number from user input, handling cases where account is not found
		std::string account_number = ReadAccountNumber("Client not found - Invalid account number!\n", true);

		// Find the client based on the account number and print their details
		clsClient client = clsClient::Find(account_number);
		PrintClientCard(client);

		// Read the withdrawal amount from user input
		float amount = clsNumber::ReadFloatNumber("Enter Amount: ");

		// Prompt user to confirm the withdrawal action
		if (clsBool::GetYesNo("Do you want to confirm this action (Y/N): "))
		{
			// Attempt to withdraw the specified amount from the client's account
			if (client.Withdraw(amount))
			{
				// Display success message and new balance if withdrawal is successful
				std::cout << "\nAmount Withdrawal Successfully.\n";
				std::cout << "\nNew Balance Is: " << client.balance << std::endl;
			}
			else
			{
				// Display message if withdrawal fails due to insufficient balance
				std::cout << "Cannot Withdraw - Insufficient Balance!\n";
			}
		}
		else
		{
			// Display message if user cancels the operation
			std::cout << "\nOperation cancelled.\n";
		}
	}
};
