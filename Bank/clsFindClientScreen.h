#pragma once

class clsFindClientScreen : protected clsScreen  // Class definition inheriting clsScreen protectedly
{
public:
	static void FindClient()  // Static method to find a client
	{
		if (current_user.CheckAccessPermission(clsUser::enPermissions::find_client) ==
			clsUser::enAccessPermission::denied)  // Check if user has permission to find client
		{
			AccessDeniedScreen();  // Show access denied screen
			return;  // Exit method
		}

		system("cls");  // Clear screen
		clsScreen::PrintHead("Find Client");  // Print heading for finding client

		std::string account_number = ReadAccountNumber("Client not found - Invalid account number!\n", true);  // Read account number from user input

		clsClient client = clsClient::Find(account_number);  // Find client based on account number

		if (!client.IsEmpty())  // If client is found
			std::cout << "\nClient Found :)\n";  // Print message indicating client is found
		else
			std::cout << "\nClient Not Found!\n";  // Print message indicating client is not found

		PrintClientCard(client);  // Print client information
	}
};

