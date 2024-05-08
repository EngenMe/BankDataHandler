#pragma once

#include <iostream>

namespace ReadChar
{
	void DisplayMessage(std::string message)
	{
		if (!message.empty())
			std::cout << message << " :\n";
	}

	char ReadChar(std::string message = "")
	{
		char c;

		DisplayMessage(message);

		std::cin >> c;

		return c;
	}
}