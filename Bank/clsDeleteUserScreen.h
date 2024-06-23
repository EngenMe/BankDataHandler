#pragma once

class clsDeleteUserScreen : protected clsScreen  // Class definition inheriting clsScreen protectedly
{
public:
	static void DeleteUser()  // Static method to delete a user
	{
		system("cls");  // Clear screen
		PrintHead("Delete User");  // Print heading

		std::string user_name = ReadUserName("User not found - Invalid username!\n", true);  // Read username

		clsUser user = clsUser::Find(user_name);  // Find user
		PrintUserCard(user);  // Print user card

		if (!clsBool::GetYesNo("Do you want to delete this user (Y/N)? "))  // Confirm deletion
		{
			std::cout << "Cancelled! - ";  // Cancelled message
			return;  // Exit function
		}

		if (user.Delete())  // Delete user
		{
			std::cout << "\nUser Deleted Successfully :)\n";  // Success message
			PrintUserCard(user);  // Print updated user card
		}
		else
			std::cout << "\nError - User Not Deleted!\n";  // Error message
	}
};
