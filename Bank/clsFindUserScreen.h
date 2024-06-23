#pragma once

class clsFindUserScreen : protected clsScreen
{
public:
	static void FindUser()
	{
		system("cls");
		clsScreen::PrintHead("Find User");

		std::string user_name = ReadUserName("User not found - Invalid Username!\n", true);

		clsUser user = clsUser::Find(user_name);

		if (!user.IsEmpty())
			std::cout << "\nUser Found :)\n";
		else
			std::cout << "\nUser Not Found!\n";

		PrintUserCard(user);
	}
};
