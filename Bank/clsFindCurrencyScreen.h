#pragma once
#include "clsScreen.h" // Include necessary header file for clsScreen functionality
#include "clsCurrency.h" // Include clsCurrency class for currency operations

class clsFindCurrencyScreen : protected clsScreen
{
public:
	// Method to display the find currency screen
	static void ShowFindCurrency()
	{
		system("cls"); // Clear console screen
		clsScreen::PrintHead("Find Currency"); // Print header for find currency screen

		clsCurrency currency = clsCurrency::EmptyCurrency(); // Initialize an empty currency object

		// Prompt user to choose search criteria (by country name or currency code)
		if ((clsCurrency::enFindBy)clsNumber::ReadShortNumberBetween(1, 2,
			"Find by [1] Country Name or [2] Currency Code: ") == clsCurrency::enFindBy::country)
		{
			// If searching by country name
			std::string country_name = ReadCountryName("Currency not found - Invalid country name!\n", true);
			currency = clsCurrency::FindByCountryName(country_name); // Find currency by country name
		}
		else
		{
			// If searching by currency code
			std::string currency_code = ReadCurrencyCode("Currency not found - Invalid currency code!\n", true);
			currency = clsCurrency::FindByCurrencyCode(currency_code); // Find currency by currency code
		}

		// Display search result
		if (!currency.IsEmpty()) // If currency object is not empty (i.e., currency found)
			std::cout << "\nCurrency Found :)\n"; // Display success message
		else
			std::cout << "\nCurrency Not Found!\n"; // Display failure message

		PrintCurrencyCard(currency); // Print details of the found currency (if found)
	}
};

