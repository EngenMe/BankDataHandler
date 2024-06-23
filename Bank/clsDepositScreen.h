#pragma once

class clsDepositScreen : protected clsScreen  // Class definition inheriting clsScreen protectedly
{
public:
	static void Deposit()  // Static method to handle deposit operation
	{
		system("cls");  // Clear screen
		PrintHead("Deposit");  // Print heading

		std::string account_number = ReadAccountNumber("Client not found - Invalid account number!\n", true);  // Read account number

		clsClient client = clsClient::Find(account_number);  // Find client
		PrintClientCard(client);  // Print client card

		float amount = clsNumber::ReadFloatNumber("Enter Amount: ");  // Read deposit amount

		if (clsBool::GetYesNo("Do you want to confirm this action (Y/N): "))  // Confirm action
		{
			client.Deposit(amount);  // Deposit amount to client's account
			std::cout << "\nAmount Deposited Successfully.\n";  // Success message
			std::cout << "\nNew Balance Is: " << client.balance << std::endl;  // Display new balance
		}
		else
			std::cout << "\nOperation cancelled.\n";  // Cancelled message
	}
};
