#pragma once

#include <iostream>

namespace ReadString
{
	void DisplayMessage(std::string message)
	{
		if (!message.empty())
			std::cout << message << " : " << std::endl;
	}

	std::string ReadString(std::string message = "")
	{
		DisplayMessage(message);
		
		std::string str;

		std::getline(std::cin >> std::ws, str);

		return str;
	}
}
