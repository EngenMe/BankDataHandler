#pragma once

#include "clsScreen.h" // Include necessary header file for clsScreen functionality
#include "clsEndScreen.h" // Include screens for various menu options
#include "clsLogoutScreen.h"
#include "clsFindClientScreen.h"
#include "clsClientsListScreen.h"
#include "clsManageUsersScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"

class clsMainScreen : protected clsScreen
{
private:
	// Enum defining the main menu options
	enum enMainMenueOptions
	{
		show_clients_list = 1,
		add_new_client,
		delete_client,
		update_client,
		find_client,
		transactions,
		manage_users,
		login_register,
		currency_exchange,
		logout,
		end
	};

	// Method to go back to the main menu after completing an action
	static void _BackToMain()
	{
		std::cout << "Press Any Key to Return to Main Menu . . . ";
		system("pause>0");
		DisplayMainMenueScreen(); // Redisplay the main menu
	}

	// Methods to invoke screens for various menu options
	static void _ShowClientsListScreen()
	{
		clsClientsListScreen::ShowClientsList(); // Display the clients list screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::AddNewClient(); // Display the add new client screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::DeleteClient(); // Display the delete client screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::UpdateClient(); // Display the update client screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::FindClient(); // Display the find client screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowTransactionsScreen()
	{
		clsTransactionsScreen::DisplayTransactionsMenuScreen(); // Display the transactions screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowManageUsersScreen()
	{
		clsManageUsersScreen::DisplayManageUsersScreen(); // Display the manage users screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegister(); // Display the login/register screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowCurrencyExchange(); // Display the currency exchange screen
		_BackToMain(); // Return to main menu
	}

	static void _ShowLogoutScreen()
	{
		clsLogoutScreen::ShowLogoutScreen(); // Display the logout screen
	}

	static void _ShowEndScreen()
	{
		clsEndScreen::ShowEndScreen(); // Display the end screen
	}

	// Method to perform the selected main menu option
	static void _PerformMainMenueOption(enMainMenueOptions option)
	{
		switch (option)
		{
		case enMainMenueOptions::show_clients_list:
			_ShowClientsListScreen(); // Invoke method to show clients list screen
			break;
		case enMainMenueOptions::add_new_client:
			_ShowAddNewClientScreen(); // Invoke method to show add new client screen
			break;
		case enMainMenueOptions::delete_client:
			_ShowDeleteClientScreen(); // Invoke method to show delete client screen
			break;
		case enMainMenueOptions::update_client:
			_ShowUpdateClientScreen(); // Invoke method to show update client screen
			break;
		case enMainMenueOptions::find_client:
			_ShowFindClientScreen(); // Invoke method to show find client screen
			break;
		case enMainMenueOptions::transactions:
			_ShowTransactionsScreen(); // Invoke method to show transactions screen
			break;
		case enMainMenueOptions::manage_users:
			_ShowManageUsersScreen(); // Invoke method to show manage users screen
			break;
		case enMainMenueOptions::login_register:
			_ShowLoginRegisterScreen(); // Invoke method to show login/register screen
			break;
		case enMainMenueOptions::currency_exchange:
			_ShowCurrencyExchangeScreen(); // Invoke method to show currency exchange screen
			break;
		case enMainMenueOptions::logout:
			_ShowLogoutScreen(); // Invoke method to show logout screen
			break;
		case enMainMenueOptions::end:
			_ShowEndScreen(); // Invoke method to show end screen
			break;
		}
	}

public:
	// Method to display the main menu screen
	static void DisplayMainMenueScreen()
	{
		system("cls"); // Clear console screen
		PrintHead("Main Menu"); // Display header for main menu

		// Vector containing options for the main menu
		std::vector<std::string> v_options =
		{
			"Show Clients List",
			"Add New Client",
			"Delete Client",
			"Update Client",
			"Find Client",
			"Transactions",
			"Manage Users",
			"Login Register",
			"Currency Exchange",
			"Logout",
			"End Programme"
		};

		PrintOptions(v_options); // Print options for the main menu

		// Perform the selected main menu option based on user input
		_PerformMainMenueOption(static_cast<enMainMenueOptions>(
			clsNumber::ReadShortNumberBetween(1, v_options.size(), "Choose Action: ")));
	}
};

