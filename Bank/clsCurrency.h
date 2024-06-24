#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "clsString.h" // Include necessary header file for string manipulation

class clsCurrency
{
private:
	std::string _country_name;
	std::string _currency_code;
	std::string _currency_name;
	float _usd_rate;

	enum enMode
	{
		empty,
		update
	};
	enMode _mode;

	// Private method to convert string data to clsCurrency object
	static clsCurrency _ConvertStrToCurrency(std::string str)
	{
		std::vector<std::string> v_currencies = clsString::Split(str, ", "); // Split string into components

		// Create and return clsCurrency object from parsed data
		return clsCurrency(enMode::update, v_currencies[0], v_currencies[1], v_currencies[2],
			stof(v_currencies[3]));
	}

	// Private method to convert clsCurrency object to string data
	std::string _ConvertCurrencyToStr(clsCurrency currency, std::string delimiter = ", ")
	{
		// Convert clsCurrency data to a formatted string
		return currency.GetCountryName() + delimiter +
			currency.GetCurrencyCode() + delimiter +
			currency.GetCurrencyName() + delimiter +
			std::to_string(currency.GetUSDRate());
	}

	// Private method to save vector of clsCurrency objects to a text file
	void _SaveCurrenciesToTxt(std::vector<clsCurrency> v_currencies)
	{
		std::fstream file;
		file.open("Currencies.txt", std::ios::out); // Open file for writing

		if (file.is_open())
		{
			for (clsCurrency c : v_currencies)
			{
				file << _ConvertCurrencyToStr(c) << std::endl; // Write each clsCurrency object to file
			}

			file.close(); // Close file after writing
		}
	}

	// Private method to load clsCurrency objects from a text file
	static std::vector<clsCurrency> _LoadCurrenciesFromTxt()
	{
		std::vector<clsCurrency> v_currencies; // Vector to store clsCurrency objects

		std::fstream file;
		file.open("Currencies.txt", std::ios::in); // Open file for reading
		if (file.is_open())
		{
			std::string line;
			while (getline(file, line))
			{
				v_currencies.push_back(_ConvertStrToCurrency(line)); // Read and parse each line into clsCurrency objects
			}

			file.close(); // Close file after reading
		}

		return v_currencies; // Return vector of clsCurrency objects
	}

	// Private method to update existing clsCurrency object in file
	void _Update()
	{
		std::vector<clsCurrency> v_currencies = _LoadCurrenciesFromTxt(); // Load currencies from file

		for (clsCurrency& c : v_currencies)
		{
			if (c._currency_code == GetCurrencyCode()) // Find matching currency code
			{
				c = *this; // Update matching currency with current object data
				break;
			}
		}

		_SaveCurrenciesToTxt(v_currencies); // Save updated currencies back to file
	}

public:
	// Constructor to initialize clsCurrency object
	clsCurrency(enMode mode, std::string country_name, std::string currency_code, std::string currency_name,
		float usd_rate)
	{
		_mode = mode;
		_country_name = country_name;
		_currency_code = currency_code;
		_currency_name = currency_name;
		_usd_rate = usd_rate;
	}

	// Getter methods for clsCurrency data members
	std::string GetCountryName()
	{
		return _country_name;
	}
	std::string GetCurrencyCode()
	{
		return _currency_code;
	}
	std::string GetCurrencyName()
	{
		return _currency_name;
	}
	float GetUSDRate()
	{
		return _usd_rate;
	}

	// Method to check if clsCurrency object is empty
	bool IsEmpty()
	{
		return _mode == enMode::empty;
	}

	// Enumeration to define search criteria for finding clsCurrency objects
	enum enFindBy
	{
		country = 1,
		currency
	};

	// Static method to find clsCurrency object by country name
	static clsCurrency FindByCountryName(std::string country_name)
	{
		std::fstream file;
		file.open("Currencies.txt", std::ios::in); // Open file for reading

		while (file.is_open())
		{
			std::string line;
			while (getline(file, line))
			{
				clsCurrency currency = _ConvertStrToCurrency(line); // Convert line to clsCurrency object
				if (clsString::UpperAll(currency._country_name) == clsString::UpperAll(country_name)) // Case-insensitive comparison
				{
					file.close();
					return currency; // Return matching currency object
				}
			}

			file.close(); // Close file after reading
		}

		return EmptyCurrency(); // Return empty currency if not found
	}

	// Static method to find clsCurrency object by currency code
	static clsCurrency FindByCurrencyCode(std::string currency_code)
	{
		std::fstream file;
		file.open("Currencies.txt", std::ios::in); // Open file for reading

		while (file.is_open())
		{
			std::string line;
			while (getline(file, line))
			{
				clsCurrency currency = _ConvertStrToCurrency(line); // Convert line to clsCurrency object
				if (clsString::UpperAll(currency._currency_code) == clsString::UpperAll(currency_code)) // Case-insensitive comparison
				{
					file.close();
					return currency; // Return matching currency object
				}
			}

			file.close(); // Close file after reading
		}

		return EmptyCurrency(); // Return empty currency if not found
	}

	// Static method to check if clsCurrency object exists by country name
	static bool IsCurrencyExistByCountryName(std::string country_name)
	{
		return !clsCurrency::FindByCountryName(country_name).IsEmpty(); // Check if currency exists by country name
	}

	// Static method to check if clsCurrency object exists by currency code
	static bool IsCurrencyExistByCurrencyCode(std::string currency_code)
	{
		return !clsCurrency::FindByCurrencyCode(currency_code).IsEmpty(); // Check if currency exists by currency code
	}

	// Static method to get vector of all clsCurrency objects from file
	static std::vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesFromTxt(); // Return vector of currencies loaded from file
	}

	// Method to update USD exchange rate and save changes to file
	void UpdateUSDRate(float new_rate)
	{
		_usd_rate = new_rate; // Update USD exchange rate
		_Update(); // Call private method to save changes to file
	}

	// Static method to create an empty clsCurrency object
	static clsCurrency EmptyCurrency()
	{
		return clsCurrency(enMode::empty, "", "", "", 0.0); // Return empty currency object
	}

	// Method to convert amount to USD using current exchange rate
	float ConvertToUSD(float amount)
	{
		return amount / this->GetUSDRate(); // Convert amount to USD
	}

	// Method to convert amount to another currency using current exchange rates
	float ConvertToAnotherCurrency(float amount, clsCurrency destination_currency)
	{
		float amount_in_usd = destination_currency.ConvertToUSD(amount); // Convert amount to USD

		if (destination_currency.GetCurrencyCode() == "USD")
			return amount_in_usd; // Return amount if destination currency is USD
		else
			return amount_in_usd * this->GetUSDRate(); // Convert amount to destination currency
	}
};

