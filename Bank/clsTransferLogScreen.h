#pragma once

#include "clsScreen.h"

class clsTransferLogScreen : protected clsScreen
{
public:
	// Function to show transfer log details
	static void ShowTransferLog()
	{
		system("cls"); // Clear screen
		std::vector<clsLogs> v_transfer_log = clsLogs::GetTransferRegister(); // Retrieve transfer logs

		// Print header with title and table mode
		PrintHead("Transfer Log.", enTableMode::long_table, v_transfer_log.size(), "Record");

		// Print table headers
		std::cout << "| " << std::left << std::setw(22) << "Date / Time";
		std::cout << "| " << std::left << std::setw(15) << "Source Acc.";
		std::cout << "| " << std::left << std::setw(18) << "Destination Acc.";
		std::cout << "| " << std::left << std::setw(18) << "Transfer Amount";
		std::cout << "| " << std::left << std::setw(22) << "Source Acc. Balance";
		std::cout << "| " << std::left << std::setw(25) << "Destination Acc. Balance";
		std::cout << "| " << std::left << std::setw(15) << "Username";

		// Print separator line
		std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------\n";

		// Print each transfer log entry
		for (int i = 0; i < v_transfer_log.size(); i++)
		{
			clsLogs transfer_register = v_transfer_log[i]; // Get current transfer log entry

			// Print log details
			std::cout << "| " << std::left << std::setw(22) << transfer_register.date_time;
			std::cout << "| " << std::left << std::setw(15) <<
				transfer_register.source_client.GetAccountNumber();
			std::cout << "| " << std::left << std::setw(18) <<
				transfer_register.destination_client.GetAccountNumber();
			std::cout << "| " << std::left << std::setw(18) << transfer_register.trasfer_amount;
			std::cout << "| " << std::left << std::setw(22) << transfer_register.source_client.balance;
			std::cout << "| " << std::left << std::setw(25) << transfer_register.destination_client.balance;
			std::cout << "| " << std::left << std::setw(15) << transfer_register.user.user_name;

			std::cout << std::endl; // Move to the next line
		}

		// Print footer and end of table
		std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------\n";
	}
};

