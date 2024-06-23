#pragma once

#include "clsScreen.h"  // Include header file for clsScreen

class clsEndScreen : protected clsScreen  // Class definition inheriting clsScreen protectedly
{
public:
	static void ShowEndScreen()  // Static method to show end screen and terminate program
	{
		system("cls");  // Clear screen
		PrintHead("Programme End");  // Print heading for program end
		exit(0);  // Terminate program
	}
};
