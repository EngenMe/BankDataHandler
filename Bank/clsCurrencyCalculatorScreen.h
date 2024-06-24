#pragma once
#include "clsScreen.h" // Include necessary header file for clsScreen functionality

class clsCurrencyCalculatorScreen : protected clsScreen
{
public:
	// Static method to display the currency calculator screen
	static void ShowCurrencyCalculator()
	{
		system("cls"); // Clear console screen
		PrintHead("Currency Calculator"); // Print header for currency calculator

		// Initialize source and destination currencies as empty
		clsCurrency source_currency = clsCurrency::EmptyCurrency();
		clsCurrency destination_currency = clsCurrency::EmptyCurrency();

		// Prompt user to choose search criteria for currencies
		if ((clsCurrency::enFindBy)clsNumber::ReadShortNumberBetween(1, 2,
			"Find by [1] Country Name or [2] Currency Code: ") == clsCurrency::enFindBy::country)
		{
			// If user chooses to find by country name
			std::cout << "Source Currency:\n";
			std::string source_country_name =
				ReadCountryName("Currency not found - Invalid country name!\n", true); // Read source country name

			std::cout << "Destination Currency:\n";
			std::string destination_country_name =
				ReadCountryName("Currency not found - Invalid country name!\n", true); // Read destination country name

			// Find corresponding currencies based on country names
			source_currency = clsCurrency::FindByCountryName(source_country_name);
			destination_currency = clsCurrency::FindByCountryName(destination_country_name);
		}
		else
		{
			// If user chooses to find by currency code
			std::cout << "Source Currency:\n";
			std::string source_currency_code =
				ReadCurrencyCode("Currency not found - Invalid currency code!\n", true); // Read source currency code

			std::cout << "Destination Currency:\n";
			std::string destination_currency_code =
				ReadCurrencyCode("Currency not found - Invalid currency code!\n", true); // Read destination currency code

			// Find corresponding currencies based on currency codes
			source_currency = clsCurrency::FindByCurrencyCode(source_currency_code);
			destination_currency = clsCurrency::FindByCurrencyCode(destination_currency_code);
		}

		// Read amount to exchange from user
		float amount_to_exchange = clsNumber::ReadFloatNumber("Enter Amount to Exchange: ");

		// If destination currency is USD, perform direct conversion to USD
		if (destination_currency.GetCurrencyCode() == "USD")
		{
			std::cout << "\nConvert From:\n";
			PrintCurrencyCard(source_currency); // Print source currency details

			std::cout << "\nConvert To:\n";
			PrintCurrencyCard(destination_currency); // Print destination currency details

			// Convert and display amount in USD
			std::cout << "\n" << amount_to_exchange << " " << source_currency.GetCurrencyCode() << " = " <<
				source_currency.ConvertToUSD(amount_to_exchange) << " USD\n";

			return; // Exit method after displaying result
		}
		else
		{
			std::cout << "\nConvert From:\n";
			PrintCurrencyCard(source_currency); // Print source currency details
			std::cout << "\n" << amount_to_exchange << " " << source_currency.GetCurrencyCode() << " = " <<
				source_currency.ConvertToUSD(amount_to_exchange) << " USD\n";

			std::cout << "\nConvert To:\n";
			PrintCurrencyCard(destination_currency); // Print destination currency details

			// Convert and display amount from USD to destination currency
			std::cout << "\n" << source_currency.ConvertToUSD(amount_to_exchange) << " " << " USD = " <<
				destination_currency.ConvertToAnotherCurrency(amount_to_exchange, source_currency) <<
				destination_currency.GetCurrencyCode() << std::endl;
		}
	}
};

