#pragma once

#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include "clsTotalBalancesScreen.h"

class clsTransactionsScreen : protected clsScreen
{
private:
	// Enum to represent transaction options
	enum enTransactionsOptions
	{
		deposit = 1,
		withdraw,
		total_balance,
		transfer,
		transfer_log,
		main
	};

	// Function to go back to the transactions menu after completing an action
	static void _BackToTransactions()
	{
		std::cout << "Press Any Key to Return to Transactions Menu . . . ";
		system("pause>0");
		DisplayTransactionsMenuScreen(); // Calls the main menu display function
	}

	// Function to display the deposit screen
	static void _ShowDepositScreen()
	{
		clsDepositScreen::Deposit(); // Invokes the deposit function from clsDepositScreen
		_BackToTransactions(); // Returns to transactions menu after deposit
	}

	// Function to display the withdraw screen
	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::Withdraw(); // Invokes the withdraw function from clsWithdrawScreen
		_BackToTransactions(); // Returns to transactions menu after withdrawal
	}

	// Function to display the total balances screen
	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalancesList(); // Shows total balances using clsTotalBalancesScreen
		_BackToTransactions(); // Returns to transactions menu after viewing total balances
	}

	// Function to display the transfer screen
	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen(); // Invokes the transfer screen from clsTransferScreen
		_BackToTransactions(); // Returns to transactions menu after initiating a transfer
	}

	// Function to display the transfer log screen
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLog(); // Shows transfer log using clsTransferLogScreen
		_BackToTransactions(); // Returns to transactions menu after viewing transfer log
	}

	// Function to perform the selected transaction option based on the enum
	static void _PerformTransactionOption(enTransactionsOptions option)
	{
		switch (option)
		{
		case enTransactionsOptions::deposit:
			_ShowDepositScreen();
			break;
		case enTransactionsOptions::withdraw:
			_ShowWithdrawScreen();
			break;
		case enTransactionsOptions::total_balance:
			_ShowTotalBalancesScreen();
			break;
		case enTransactionsOptions::transfer:
			_ShowTransferScreen();
			break;
		case enTransactionsOptions::transfer_log:
			_ShowTransferLogScreen();
			break;
		default:
			return; // Returns if an invalid option is selected
		}
	}

public:
	// Function to display the transactions menu screen
	static void DisplayTransactionsMenuScreen()
	{
		// Check if user has permission to access transactions
		if (current_user.CheckAccessPermission(clsUser::enPermissions::transactions) ==
			clsUser::enAccessPermission::denied)
		{
			AccessDeniedScreen(); // Display access denied screen if permission is denied
			return;
		}

		system("cls"); // Clears screen
		PrintHead("Transactions Menu"); // Prints header for transactions menu

		// Options for transactions menu
		std::vector<std::string> v_options =
		{
			"Deposit",
			"Withdraw",
			"Total Balances",
			"Transfer",
			"Transfer Log",
			"Back To Main Menu"
		};
		PrintOptions(v_options); // Print options to console

		// Reads and performs the selected transaction option
		_PerformTransactionOption(static_cast<enTransactionsOptions>(
			clsNumber::ReadShortNumberBetween(1, v_options.size(), "Choose Action: ")));
	}
};

