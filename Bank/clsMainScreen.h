#pragma once

#include "clsScreen.h"
#include "clsEndScreen.h"
#include "clsLogoutScreen.h"
#include "clsFindClientScreen.h"
#include "clsClientsListScreen.h"
#include "clsManageUsersScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsLoginRegisterScreen.h"

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenueOptions
	{
		show_clients_list = 1,
		add_new_client,
		delete_client,
		update_client,
		find_client,
		transactions,
		manage_users,
		login_register,
		logout,
		end
	};

	static void _BackToMain()
	{
		std::cout << "Press Any Key to Back to Main . . . ";
		system("pause>0");
		DisplayMainMenueScreen();
	}

	static void _ShowClientsListScreen()
	{
		clsClientsListScreen::ShowClientsList();
		_BackToMain();
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::AddNewClient();
		_BackToMain();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::DeleteClient();
		_BackToMain();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::UpdateClient();
		_BackToMain();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::FindClient();
		_BackToMain();
	}

	static void _ShowTransactionsScreen()
	{
		clsTransactionsScreen::DisplayTransactionsMenuScreen();
		_BackToMain();
	}

	static void _ShowManageUsersScreen()
	{
		clsManageUsersScreen::DisplayManageUsersScreen();
		_BackToMain();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegister();
		_BackToMain();
	}

	static void _ShowLogoutScreen()
	{
		clsLogoutScreen::ShowLogoutScreen();
	}

	static void _ShowEndScreen()
	{
		clsEndScreen::ShowEndScreen();
	}

	static void _PerformMainMenueOption(enMainMenueOptions option)
	{
		switch (option)
		{
		case enMainMenueOptions::show_clients_list:
			_ShowClientsListScreen();
			break;
		case enMainMenueOptions::add_new_client:
			_ShowAddNewClientScreen();
			break;
		case enMainMenueOptions::delete_client:
			_ShowDeleteClientScreen();
			break;
		case enMainMenueOptions::update_client:
			_ShowUpdateClientScreen();
			break;
		case enMainMenueOptions::find_client:
			_ShowFindClientScreen();
			break;
		case enMainMenueOptions::transactions:
			_ShowTransactionsScreen();
			break;
		case enMainMenueOptions::manage_users:
			_ShowManageUsersScreen();
			break;
		case enMainMenueOptions::login_register:
			_ShowLoginRegisterScreen();
			break;
		case enMainMenueOptions::logout:
			_ShowLogoutScreen();
			break;
		case enMainMenueOptions::end:
			_ShowEndScreen();
			break;
		}
	}

public:
	static void DisplayMainMenueScreen()
	{
		system("cls");
		PrintHead("Main Menu");

		std::vector<std::string> v_options =
		{
			"Show Clients List",
			"Add New Client",
			"Delete Client",
			"Update Client",
			"Find Client",
			"Transactions",
			"Manage Users",
			"Login Register",
			"Logout",
			"End Programme"
		};
		PrintOptions(v_options);

		_PerformMainMenueOption(static_cast<enMainMenueOptions>(
			clsNumber::ReadShortNumberBetween(1, v_options.size(), "Choose Action: ")));
	}
};
