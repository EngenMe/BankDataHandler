#pragma once

#include "Global.h"  // Include header file for global declarations

class clsLogoutScreen
{
public:
	static void ShowLogoutScreen()
	{
		current_user = clsUser::Find("", "");  // Set current_user to empty user (logout)
	}
};
