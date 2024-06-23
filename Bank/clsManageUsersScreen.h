#pragma once

#include "clsFindUserScreen.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersOptions
	{
		list_users = 1,
		add_new_user,
		delete_user,
		update_user,
		find_user,
		main
	};

	static void _BackToManage()
	{
		std::cout << "Press Any Key to Back to Manage Menu . . . ";
		system("pause>0");
		DisplayManageUsersScreen();
	}

	static void _ShowListUsersScreen()
	{
		clsUsersListScreen::ShowUsersList();
		_BackToManage();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::AddNewUser();
		_BackToManage();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::DeleteUser();
		_BackToManage();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::UpdateUser();
		_BackToManage();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::FindUser();
		_BackToManage();
	}

	static void _PerformManageUsersOption(enManageUsersOptions option)
	{
		switch (option)
		{
		case enManageUsersOptions::list_users:
			_ShowListUsersScreen();
			break;
		case enManageUsersOptions::add_new_user:
			_ShowAddNewUserScreen();
			break;
		case enManageUsersOptions::delete_user:
			_ShowDeleteUserScreen();
			break;
		case enManageUsersOptions::update_user:
			_ShowUpdateUserScreen();
			break;
		case enManageUsersOptions::find_user:
			_ShowFindUserScreen();
			break;
		default:
			return;
		}
	}

public:
	static void DisplayManageUsersScreen()
	{
		if (current_user.CheckAccessPermission(clsUser::enPermissions::manage_users) ==
			clsUser::enAccessPermission::denied)
		{
			AccessDeniedScreen();
			return;
		}

		system("cls");
		PrintHead("Manage Users Menu");

		std::vector<std::string> v_options =
		{
			"List Users",
			"Add New User",
			"Delete User",
			"Update User",
			"Find User",
			"Main Menu"
		};
		PrintOptions(v_options);

		_PerformManageUsersOption(static_cast<enManageUsersOptions>(
			clsNumber::ReadShortNumberBetween(1, v_options.size(), "Choose Action: ")));
	}
};
