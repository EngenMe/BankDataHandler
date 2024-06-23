#pragma once

class clsUpdateUserScreen : protected clsScreen
{
public:
    // Function: UpdateUser
    // Description: Updates user information if user has permission,
    // prompts for username, reads user info and permissions, and saves changes.
    static void UpdateUser()
    {
        system("cls"); // Clear console screen
        PrintHead("Update User"); // Print screen header

        // Prompt user to enter username to update user
        std::string user_name = ReadUserName("User not found, Invalid Username!\n", true);

        // Find user object based on entered username
        clsUser user = clsUser::Find(user_name);

        // Display user information card
        PrintUserCard(user);

        // Confirmation prompt to update user
        if (!clsBool::GetYesNo("Do you want to update this user (Y/N)? "))
        {
            std::cout << "Cancelled! - "; // Display cancellation message if user declines
            return;
        }

        ReadUserInfo(user); // Read updated user information from user input
        ReadUserPermissions(user); // Read updated user permissions from user input

        // Save updated user information and handle save status
        clsUser::enSave save = user.Save();

        switch (save)
        {
        case clsUser::enSave::success:
            std::cout << "\nUser Updated Successfully :)\n"; // Display success message on successful update
            PrintUserCard(user); // Print updated user card
            break;
        case clsUser::enSave::failed_empty_obj:
            std::cout << "\nError - Empty User!\n"; // Display error message if user object is empty
        }
    }
};

