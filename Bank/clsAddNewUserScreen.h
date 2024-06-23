#pragma once

class clsAddNewUserScreen : protected clsScreen
{
public:
    // Static method to handle adding a new user
    static void AddNewUser()
    {
        system("cls");  // Clear screen for better display
        PrintHead("Add New User");  // Print header for the add new user screen

        // Read user name from user input, handle case where user name already exists
        std::string user_name = ReadUserName("Account Number Already Exist!\n", false);

        // Create a new user object with the given user name
        clsUser new_user = clsUser::NewUserObj(user_name);

        // Read additional user information from user input
        ReadUserInfo(new_user);

        // Read and assign user permissions from user input
        ReadUserPermissions(new_user);

        // Attempt to save the new user information
        clsUser::enSave save = new_user.Save();

        // Handle different outcomes of the save operation
        switch (save)
        {
        case clsUser::enSave::success:
            std::cout << "\nUser Added Successfully :)\n";
            PrintUserCard(new_user);  // Print user card details upon successful addition
            break;
        case clsUser::enSave::failed_empty_obj:
            std::cout << "\nError - Empty User!\n";  // Error message for empty user object
            break;
        case clsUser::enSave::failed_already_exist:
            std::cout << "\nError - User Already Exist!\n";  // Error message for existing user
            break;
        }
    }
};
