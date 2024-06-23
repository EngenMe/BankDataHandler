#pragma once

#include <iostream>
#include <vector>
#include <string>

class clsNumber
{
private:
	// Private method to check if a number is within a specified range
	static bool _IsBetween(double number, double from, double to)
	{
		return number >= from && number <= to;
	}

public:
	// Method to read a short integer from input, ensuring it falls within a specified range
	static short ReadShortNumberBetween(short from, short to, std::string message = "",
		std::string error_message = "Invalid Number Range Exceeded! Enter Again: ")
	{
		std::cout << message;

		short number;
		std::cin >> number;
		while (!_IsBetween(number, from, to))
		{
			std::cout << error_message;
			std::cin >> number;
		}

		return number;
	}

	// Method to read a floating-point number from input
	static float ReadFloatNumber(std::string message = "")
	{
		std::cout << message;

		float number;
		std::cin >> number;

		return number;
	}

	// Method to calculate the sum of a vector of floating-point numbers
	static float Sum(std::vector<float> v_numbers)
	{
		float sum = 0;

		for (float f : v_numbers)
		{
			sum += f;
		}

		return sum;
	}

	// Method to convert a number (up to billions) to its English text representation
	static std::string NumberToText(int number)
	{
		if (number == 0)
		{
			return "Zero";
		}
		else if (number < 0)
		{
			return "Minus " + NumberToText(-number);
		}
		else if (number >= 1 && number <= 19)
		{
			std::string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
				"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
				"Eighteen", "Nineteen" };
			return arr[number] + " ";
		}
		else if (number >= 20 && number <= 99)
		{
			std::string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty",
				"Ninety" };
			return arr[number / 10] + " " + NumberToText(number % 10);
		}
		else if (number >= 100 && number <= 999)
		{
			return NumberToText(number / 100) + " Hundred " + NumberToText(number % 100);
		}
		else if (number >= 1000 && number <= 999999)
		{
			return NumberToText(number / 1000) + " Thousand " + NumberToText(number % 1000);
		}
		else if (number >= 1000000 && number <= 999999999)
		{
			return NumberToText(number / 1000000) + " Million " + NumberToText(number % 1000000);
		}
		else if (number >= 1000000000 && number <= 999999999999)
		{
			return NumberToText(number / 1000000000) + " Billion " + NumberToText(number % 1000000000);
		}
		else
		{
			return "Number out of range";
		}
	}
};
