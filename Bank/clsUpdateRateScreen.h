#pragma once

#include "clsScreen.h" // Include necessary header file for clsScreen functionality
#include "clsCurrency.h" // Include clsCurrency class for currency operations

class clsUpdateRateScreen : protected clsScreen
{
public:
	// Method to display the update rate screen
	static void ShowUpdateRate()
	{
		system("cls"); // Clear console screen
		PrintHead("Update Rate"); // Display header for update rate screen

		clsCurrency currency = clsCurrency::EmptyCurrency(); // Initialize currency object

		// Prompt user to choose whether to find currency by country name or currency code
		if ((clsCurrency::enFindBy)clsNumber::ReadShortNumberBetween(1, 2,
			"Find by [1] Country Name or [2] Currency Code: ") == clsCurrency::enFindBy::country)
		{
			std::string country_name = ReadCountryName("Currency not found - Invalid country name!\n", true); // Read country name
			currency = clsCurrency::FindByCountryName(country_name); // Find currency by country name
		}
		else
		{
			std::string currency_code = ReadCurrencyCode("Currency not found - Invalid currency code!\n", true); // Read currency code
			currency = clsCurrency::FindByCurrencyCode(currency_code); // Find currency by currency code
		}

		PrintCurrencyCard(currency); // Print details of the found currency

		// Ask user if they want to update the currency rate
		if (!clsBool::GetYesNo("Do you want to update this rate (Y/N)? "))
		{
			std::cout << "Cancelled! - "; // If user declines update, display message and return
			return;
		}

		float new_rate = clsNumber::ReadFloatNumber("Enter new USD rate: "); // Prompt user for new USD rate

		currency.UpdateUSDRate(new_rate); // Update the USD rate of the currency

		std::cout << "\nRate Updated Successfully :)\n"; // Display success message

		PrintCurrencyCard(currency); // Print updated currency details
	}
};

