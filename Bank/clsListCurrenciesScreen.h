#pragma once

#include "clsScreen.h" // Include necessary header file for clsScreen functionality
#include "clsCurrency.h" // Include clsCurrency class for currency operations

class clsListCurrenciesScreen : protected clsScreen
{
public:
	// Method to display the list of currencies
	static void ShowListCurrencies()
	{
		system("cls"); // Clear console screen

		// Retrieve list of currencies from clsCurrency class
		std::vector<clsCurrency> v_currencies = clsCurrency::GetCurrenciesList();

		// Print header for currency list with table formatting
		PrintHead("Currency", enTableMode::long_table, v_currencies.size(), "Currencies");

		// Print table header for currency details
		std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "| " << std::left << std::setw(30) << "Country";
		std::cout << "| " << std::left << std::setw(15) << "Code";
		std::cout << "| " << std::left << std::setw(40) << "Name";
		std::cout << "| " << std::left << std::setw(15) << "USD Rate";
		std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------\n";

		// Iterate through the list of currencies and print each currency's details
		for (int i = 0; i < v_currencies.size(); i++)
		{
			clsCurrency currency = v_currencies[i]; // Retrieve currency object at index i

			// Print each currency's details in table format
			std::cout << "| " << std::left << std::setw(30) << currency.GetCountryName();
			std::cout << "| " << std::left << std::setw(15) << currency.GetCurrencyCode();
			std::cout << "| " << std::left << std::setw(40) << currency.GetCurrencyName();
			std::cout << "| " << std::left << std::setw(15) << currency.GetUSDRate();
			std::cout << std::endl; // Move to next line after printing currency details
		}

		// Print bottom border of the table
		std::cout << "\n------------------------------------------------------------------------------------------------------------------------------------------------\n";
	}
};

