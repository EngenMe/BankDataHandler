#pragma once

#include "clsScreen.h" // Include necessary header file for clsScreen functionality
#include "clsListCurrenciesScreen.h" // Include screens related to currency operations
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeOptions
	{
		list_currencies = 1,
		find_currency,
		update_rate,
		currency_calculator,
		main
	};

	// Method to return to currency exchange menu after an operation
	static void _BackToCurrencyExchange()
	{
		std::cout << "\nPress Any Key to Return to Currency Exchange Menu . . . ";
		system("pause>0"); // Pause to wait for user input
		ShowCurrencyExchange(); // Redisplay currency exchange menu
	}

	// Method to display list currencies screen
	static void _ListCurrencies()
	{
		clsListCurrenciesScreen::ShowListCurrencies(); // Show list of currencies
		_BackToCurrencyExchange(); // Return to currency exchange menu
	}

	// Method to display find currency screen
	static void _FindCurrency()
	{
		clsFindCurrencyScreen::ShowFindCurrency(); // Show find currency screen
		_BackToCurrencyExchange(); // Return to currency exchange menu
	}

	// Method to display update rate screen
	static void _UpdateRate()
	{
		clsUpdateRateScreen::ShowUpdateRate(); // Show update rate screen
		_BackToCurrencyExchange(); // Return to currency exchange menu
	}

	// Method to perform selected currency exchange option based on user input
	static void _PerformCurrencyExchangeOption(enCurrencyExchangeOptions option)
	{
		switch (option)
		{
		case enCurrencyExchangeOptions::list_currencies:
			_ListCurrencies(); // Execute list currencies option
			_BackToCurrencyExchange(); // Return to currency exchange menu
			break;
		case enCurrencyExchangeOptions::find_currency:
			_FindCurrency(); // Execute find currency option
			_BackToCurrencyExchange(); // Return to currency exchange menu
			break;
		case enCurrencyExchangeOptions::update_rate:
			_UpdateRate(); // Execute update rate option
			_BackToCurrencyExchange(); // Return to currency exchange menu
			break;
		case enCurrencyExchangeOptions::currency_calculator:
			clsCurrencyCalculatorScreen::ShowCurrencyCalculator(); // Show currency calculator screen
			_BackToCurrencyExchange(); // Return to currency exchange menu
			break;
		default:
			return; // Exit method if invalid option
		}
	}

public:
	// Method to display the currency exchange screen
	static void ShowCurrencyExchange()
	{
		// Check if current user has permission for currency exchange
		if (current_user.CheckAccessPermission(clsUser::enPermissions::currency_exchange) ==
			clsUser::enAccessPermission::denied)
		{
			AccessDeniedScreen(); // Display access denied screen if permission is denied
			return; // Exit method
		}

		system("cls"); // Clear console screen
		PrintHead("Currency Exchange"); // Print header for currency exchange

		// Define options for currency exchange menu
		std::vector<std::string> v_options =
		{
			"List Currencies",
			"Find Currency",
			"Update Rate",
			"Currency Calculator",
			"Main Menu"
		};
		PrintOptions(v_options); // Print options for currency exchange menu

		// Read user input and perform corresponding action
		_PerformCurrencyExchangeOption(static_cast<enCurrencyExchangeOptions>(
			clsNumber::ReadShortNumberBetween(1, v_options.size(), "Choose Action: "))); // Read and validate user input
	}
};

