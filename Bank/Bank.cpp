#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "ReadNumber.h";
#include "ReadString.h";
#include "GetIsYesNo.h";

const std::string delimiter = ", ";
const std::string clients_file_name = "ClientsData.txt";
const std::string users_file_name = "UsersData.txt";

enum enAction
{
	show_client_list = 1,
	add_new_client = 2,
	delete_client = 3,
	update_client_info = 4,
	find_client = 5,
	transactions = 6,
	manage_users = 7,
	logout = 8,
	end_programme,
	denied = 10
};

enum enTransaction
{
	deposit = 1,
	withdraw = 2,
	total_balances = 3,
	main_menue = 4
};

enum enUserAction
{
	list_users = 1,
	add_new_user = 2,
	delete_user = 3,
	update_user = 4,
	find_user = 5,
	user_main_menue = 6
};

enum enPermission
{
	per_all = -1,
	per_list_clients = 1,
	per_add_new_client = 2,
	per_delete_client = 4,
	per_update_client = 8,
	per_find_client = 16,
	per_transactions = 32,
	per_manage_users = 64,
	per_exit = 128
};

struct stClientInfo
{
	std::string account_number;
	std::string pin_code;
	std::string name;
	std::string phone_number;
	double account_balance;
	bool is_delete = false;
	bool is_update = false;
};

struct stUser
{
	std::string user_name;
	std::string password;
	int permission;
	bool is_user_delete = false;
	bool is_user_update = false;
};

short FindClientIndex(std::string account_number, std::vector <stClientInfo>& v_client_data);
void DisplayClient(short index_of_client, std::vector <stClientInfo>& v_client_data);
std::vector <stUser> FillUserDataVectorFromTxtFile();
bool BackToMainMenue(bool pause);

void DisplayHeadMessage()
{
	std::cout << "========================================================================\n";
	std::cout << "\t\t\t *** Main Menue Screen ***\n";
	std::cout << "========================================================================\n";
	std::cout << "\t\t [1] Show Client List\n";
	std::cout << "\t\t [2] Add New Client\n";
	std::cout << "\t\t [3] Delete Client\n";
	std::cout << "\t\t [4] Update Client Info\n";
	std::cout << "\t\t [5] Find Client\n";
	std::cout << "\t\t [6] Transactions\n";
	std::cout << "\t\t [7] Manage Users\n";
	std::cout << "\t\t [8] Logout\n";
	std::cout << "\t\t [9] End Programme\n";
	std::cout << "========================================================================\n";
}

enAction ReadAction(stUser user)
{
	enAction action = (enAction)ReadNumber::ReadIntNumberBetweenFromAndTo(1, 9,
		"Chose which action you want to take");

	short modified_action = (int)pow(2, (int)action - 1);

	if ((user.permission == enPermission::per_all || action == enAction::logout ||
		action == enAction::end_programme) || ((user.permission & modified_action) == modified_action))
	{
		return action;
	}
	
	return enAction::denied;
}

void ShowAccessDeniedMenue()
{
	system("cls");

	std::cout << "-----------------------------------------------\n";
	std::cout << "Access Denied!\n";
	std::cout << "You don't have permission to do that!\n";
	std::cout << "Please contact your admin\n";
	std::cout << "-----------------------------------------------\n";
}

void SplitString(std::string my_string, std::vector <std::string>& v_words, std::string delim = ", ")
{
	short pos = 0;
	std::string word;

	while ((pos = my_string.find(delim)) != std::string::npos)
	{
		word = my_string.substr(0, pos);

		if (!word.empty())
			v_words.push_back(word);

		my_string.erase(0, pos + delim.length());
	}

	if (!my_string.empty())
		v_words.push_back(my_string);
}

stClientInfo StrToClientData(std::string str)
{
	std::vector <std::string> v_client_data;
	SplitString(str, v_client_data, delimiter);

	stClientInfo st_client_data;
	st_client_data.account_number = v_client_data[0];
	st_client_data.pin_code = v_client_data[1];
	st_client_data.name = v_client_data[2];
	st_client_data.phone_number = v_client_data[3];
	st_client_data.account_balance = stod(v_client_data[4]);

	return st_client_data;
}

std::vector <stClientInfo> FillClientDataVectorFromTxtFile()
{
	std::vector <stClientInfo> v_client_data;

	std::fstream file;
	file.open(clients_file_name, std::ios::in);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			v_client_data.push_back(StrToClientData(line));
		}

		file.close();
	}

	return v_client_data;
}

bool AccountNumberAlreadyExist(std::string account_number, std::vector <stClientInfo>& v_client_data)
{
	for (stClientInfo st : v_client_data)
	{
		if (st.account_number == account_number)
		{
			std::cout << "Client with account number [" << account_number << "] already exist!\n";
			return true;
		}
	}

	return false;
}

bool AccountNumberNotExist(std::string account_number, std::vector <stClientInfo>& v_client_data)
{
	for (stClientInfo st : v_client_data)
	{
		if (st.account_number == account_number)
		{
			return false;
		}
	}

	std::cout << "Client with account number [" << account_number << "] not exist!\n";
	return true;
}

std::string ReadAccountNumber(std::vector <stClientInfo>& v_client_data, enAction en_action)
{
	std::string account_number;

	switch (en_action)
	{
	case enAction::add_new_client:
		while (true)
		{
			account_number = ReadString::ReadString("Enter account number of client");
			if (!AccountNumberAlreadyExist(account_number, v_client_data))
				break;
		}
		break;
	case enAction::delete_client:
		while (true)
		{
			account_number = ReadString::ReadString("Enter account number of client you want to delete");
			if (!AccountNumberNotExist(account_number, v_client_data))
				break;
		}
		break;
	case enAction::update_client_info:
		while (true)
		{
			account_number = ReadString::ReadString("Enter account number of client you want to update");
			if (!AccountNumberNotExist(account_number, v_client_data))
				break;
		}
		break;
	default:
		while (true)
		{
			account_number = ReadString::ReadString("Enter account number of client you searching for");
			if (!AccountNumberNotExist(account_number, v_client_data))
				break;
		}
	}
	

	return account_number;
}

// Show Client List

void ShowClientList(std::vector <stClientInfo>& v_client_data)
{
	std::cout << "\n\t\t\t\t\t" << "Client List [" << v_client_data.size() << "] client(s)";

	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	std::cout << "| " << std::left << std::setw(15) << "Account Number";
	std::cout << "| " << std::left << std::setw(15) << "PIN Code";
	std::cout << "| " << std::left << std::setw(25) << "Name";
	std::cout << "| " << std::left << std::setw(20) << "Phone Number";
	std::cout << "| " << std::left << std::setw(15) << "Account Balance";

	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	stClientInfo st_client_data;

	for (int i = 0; i < v_client_data.size(); i++)
	{
		st_client_data = v_client_data[i];

		std::cout << "| " << std::left << std::setw(15) << st_client_data.account_number;
		std::cout << "| " << std::left << std::setw(15) << st_client_data.pin_code;
		std::cout << "| " << std::left << std::setw(25) << st_client_data.name;
		std::cout << "| " << std::left << std::setw(20) << st_client_data.phone_number;
		std::cout << "| " << std::left << std::setw(15) << st_client_data.account_balance;

		std::cout << std::endl;
	}

	std::cout << "----------------------------------------------------------------------------------------------------------\n";
}

// Add New Client

std::string ClientDataToString(stClientInfo st_client_data)
{
	return st_client_data.account_number + delimiter
		+ st_client_data.pin_code + delimiter
		+ st_client_data.name + delimiter
		+ st_client_data.phone_number + delimiter
		+ std::to_string(st_client_data.account_balance);
}

stClientInfo ReadClientData(std::vector <stClientInfo>& v_client_data)
{
	stClientInfo st_client_data;
	
	st_client_data.account_number = ReadAccountNumber(v_client_data, enAction::add_new_client);
	st_client_data.pin_code = ReadString::ReadString("Enter pin code");
	st_client_data.name = ReadString::ReadString("Enter name");
	st_client_data.phone_number = ReadString::ReadString("Enter phone number");
	st_client_data.account_balance = ReadNumber::ReadDoublePositiveNumber("Enter account balance");

	return st_client_data;
}

void AddStrToFile(std::string str, std::string file_name)
{
	std::fstream file;
	file.open(file_name, std::ios::out | std::ios::app);
	if (file.is_open())
	{
		file << str << std::endl;
		file.close();
	}
}

bool MoreAction(std::string message = "")
{
	if (!message.empty())
		std::cout << message << " (Y/N)?\n";

	return GetIsYesNo::GetIsYesNo();
}

void AddNewClient(std::vector <stClientInfo>& v_client_data)
{
	do
	{
		stClientInfo st_client_data = ReadClientData(v_client_data);
		std::string line = ClientDataToString(st_client_data);
		AddStrToFile(line, clients_file_name);
	} while (MoreAction("Do you want to add more clients"));
}

// Delete Client

void MarkIsDelete(std::string account_number, std::vector <stClientInfo>& v_client_data)
{
	for (stClientInfo& st : v_client_data)
	{
		if (st.account_number == account_number)
		{
			st.is_delete = true;
			break;
		}
	}
}

void EraseFile(std::string file_name = clients_file_name)
{
	std::fstream file;
	file.open(file_name, std::ios::out);
	file.close();
}

void ClientDataToFile(std::vector <stClientInfo>& v_client_data)
{
	for (stClientInfo st : v_client_data)
	{
		if (!st.is_delete)
			AddStrToFile(ClientDataToString(st), clients_file_name);
	}
}

bool ConfirmAction()
{
	std::cout << "Do you want to confirm this action (Y/N)?\n";
	return GetIsYesNo::GetIsYesNo();
}

void DeleteClient(std::vector <stClientInfo>& v_client_data)
{
	std::string account_number = ReadAccountNumber(v_client_data, enAction::delete_client);
	MarkIsDelete(account_number, v_client_data);
	short index_of_client = FindClientIndex(account_number, v_client_data);
	DisplayClient(index_of_client, v_client_data);
	if (ConfirmAction())
	{
		EraseFile();
		ClientDataToFile(v_client_data);
		std::cout << "Client Deleted Successfully!\n";
	}
	else
	{
		std::cout << "Cancelled!\n";
	}
}

// Update Client Info

void MarkIsUpdate(std::string account_number, std::vector <stClientInfo>& v_client_data)
{
	for (stClientInfo& st : v_client_data)
	{
		if (st.account_number == account_number)
		{
			st.is_update = true;
			break;
		}
	}
}

void UpdateClientLine(stClientInfo& st_client_data)
{
	st_client_data.pin_code = ReadString::ReadString("Enter new pin code");
	st_client_data.name = ReadString::ReadString("Enter new name");
	st_client_data.phone_number = ReadString::ReadString("Enter new phone number");
	st_client_data.account_balance = ReadNumber::ReadDoublePositiveNumber("Enter new account balance");
	st_client_data.is_update = false;
}

void UpdateVectClientData(std::vector <stClientInfo>& v_client_data)
{
	for (stClientInfo& st : v_client_data)
	{
		if (st.is_update)
		{
			UpdateClientLine(st);
			break;
		}
	}
}

void UpdateClientInfo(std::vector <stClientInfo>& v_client_data)
{
	std::string account_number = ReadAccountNumber(v_client_data, enAction::update_client_info);
	MarkIsUpdate(account_number, v_client_data);
	UpdateVectClientData(v_client_data);
	EraseFile();
	ClientDataToFile(v_client_data);
}

// Find Client

short FindClientIndex(std::string account_number, std::vector <stClientInfo>& v_client_data)
{
	short counter = 0;
	for (stClientInfo st : v_client_data)
	{
		if (st.account_number == account_number)
			return counter;

		counter++;
	}
}

void DisplayClient(short index_of_client, std::vector <stClientInfo>& v_client_data)
{
	std::cout << "\n===============================   Client Found Successfully   ============================\n\n";
	std::cout << std::setw(20) << "Account Number : " << std::setw(40) << v_client_data[index_of_client].account_number << std::endl;
	std::cout << std::setw(20) << "PIN Code : " << std::setw(40) << v_client_data[index_of_client].pin_code << std::endl;
	std::cout << std::setw(20) << "Name : " << std::setw(40) << v_client_data[index_of_client].name << std::endl;
	std::cout << std::setw(20) << "Phone Number : " << std::setw(40) << v_client_data[index_of_client].phone_number << std::endl;
	std::cout << std::setw(20) << "Account balance : " << std::setw(40) << v_client_data[index_of_client].account_balance << std::endl;
	std::cout << "\n==============================================================================================\n";
}

void FindClient(std::vector <stClientInfo>& v_client_data)
{
	std::string account_number = ReadAccountNumber(v_client_data, enAction::find_client);
	short index_of_client = FindClientIndex(account_number, v_client_data);
	DisplayClient(index_of_client, v_client_data);
}

// Transcations

void ShowTransactionMenue()
{
	std::cout << "========================================================================\n";
	std::cout << "\t\t\t *** Transactions Menue Screen ***\n";
	std::cout << "========================================================================\n";
	std::cout << "\t\t [1] Deposit\n";
	std::cout << "\t\t [2] Withdraw\n";
	std::cout << "\t\t [3] Total Balances\n";
	std::cout << "\t\t [4] Main Menue\n";
	std::cout << "========================================================================\n";
}

enTransaction GetTransaction()
{
	return (enTransaction)ReadNumber::ReadIntNumberBetweenFromAndTo(1, 4, "Enter Transaction Type");
}

std::string ReadAccountNumber(std::vector <stClientInfo>& v_client_data, enTransaction en_transaction)
{
	std::string account_number;

	while (true)
	{
		account_number = ReadString::ReadString("Enter account number of client");
		if (!AccountNumberNotExist(account_number, v_client_data))
			break;
	}

	return account_number;
}

// Deposit

void ShowDepositScreen()
{
	system("cls");
	std::cout << "========================================================================\n";
	std::cout << "\t\t\t *** Deposit Screen ***\n";
	std::cout << "========================================================================\n";
}

void MakeDeposit(enTransaction en_transaction, std::vector <stClientInfo>& v_client_data)
{
	ShowDepositScreen();
	std::string account_number = ReadAccountNumber(v_client_data, en_transaction);
	short index = FindClientIndex(account_number, v_client_data);
	DisplayClient(index, v_client_data);
	double deposit_amount = ReadNumber::ReadDoublePositiveNumber("Enter the deposit amount");
	if (ConfirmAction())
	{
		v_client_data[index].account_balance += deposit_amount;
		EraseFile();
		ClientDataToFile(v_client_data);
		std::cout << "Deposit Added Successfully!\n";
		std::cout << "New Balance is : " << v_client_data[index].account_balance << std::endl;
	}
}

// Withdraw

void ShowWithdrawScreen()
{
	system("cls");
	std::cout << "========================================================================\n";
	std::cout << "\t\t\t *** Withdraw Screen ***\n";
	std::cout << "========================================================================\n";
}

void MakeWithdraw(enTransaction en_transaction, std::vector <stClientInfo>& v_client_data)
{
	ShowWithdrawScreen();
	std::string account_number = ReadAccountNumber(v_client_data, en_transaction);
	short index = FindClientIndex(account_number, v_client_data);
	DisplayClient(index, v_client_data);
	double withdraw_amount = ReadNumber::ReadDoubleNumberBetweenFromAndTo(0,
		v_client_data[index].account_balance, "Enter the withdraw amount");
	if (ConfirmAction())
	{
		v_client_data[index].account_balance -= withdraw_amount;
		EraseFile();
		ClientDataToFile(v_client_data);
		std::cout << "Withdraw Added Successfully!\n";
		std::cout << "New Balance is : " << v_client_data[index].account_balance << std::endl;
	}
}

// Total_balances

double GetTotalBalances(std::vector <stClientInfo>& v_client_data)
{
	double total_balances = 0;
	for (stClientInfo st : v_client_data)
	{
		total_balances += st.account_balance;
	}

	return total_balances;
}

void ShowTotalBalances(std::vector <stClientInfo>& v_client_data)
{
	system("cls");
	
	std::cout << "\n\t\t\t\t\t" << "Balances List [" << v_client_data.size() << "] client(s)";

	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	std::cout << "| " << std::left << std::setw(15) << "Account Number";
	std::cout << "| " << std::left << std::setw(25) << "Client Name";
	std::cout << "| " << std::left << std::setw(15) << "Balance";

	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	stClientInfo st_client_data;

	for (int i = 0; i < v_client_data.size(); i++)
	{
		st_client_data = v_client_data[i];

		std::cout << "| " << std::left << std::setw(15) << st_client_data.account_number;
		std::cout << "| " << std::left << std::setw(25) << st_client_data.name;
		std::cout << "| " << std::left << std::setw(15) << st_client_data.account_balance;

		std::cout << std::endl;
	}

	std::cout << "----------------------------------------------------------------------------------------------------------\n";


	std::cout << std::endl << "\t\tTotal Blances = " << GetTotalBalances(v_client_data) << "\n\n";
}

void TakeTransaction(enTransaction en_transaction, std::vector <stClientInfo>& v_client_data)
{
	switch (en_transaction)
	{
	case enTransaction::deposit:
		MakeDeposit(en_transaction, v_client_data);
		break;
	case enTransaction::withdraw:
		MakeWithdraw(en_transaction, v_client_data);
		break;
	case enTransaction::total_balances:
		ShowTotalBalances(v_client_data);
		break;
	default:
		break;
	}
}

bool BackToTransactionMenue()
{
	std::cout << "Press Any Key To Back To Transaction Menue...";
	system("pause>0");
	system("cls");

	return true;
}

void Transaction(std::vector <stClientInfo>& v_client_data)
{
	do
	{
		ShowTransactionMenue();

		enTransaction en_transaction = GetTransaction();

		TakeTransaction(en_transaction, v_client_data);

		if (en_transaction == enTransaction::main_menue)
			break;
	} while (BackToTransactionMenue());
}

// Manage Users

void DisplayManageUsersScreen()
{
	system("cls");

	std::cout << "========================================================================\n";
	std::cout << "\t\t\t *** Manage Users Menue Screen ***\n";
	std::cout << "========================================================================\n";
	std::cout << "\t\t [1] List Users\n";
	std::cout << "\t\t [2] Add New User\n";
	std::cout << "\t\t [3] Delete User\n";
	std::cout << "\t\t [4] Update User\n";
	std::cout << "\t\t [5] Find User\n";
	std::cout << "\t\t [6] Main Menue\n";
	std::cout << "========================================================================\n";
}

enUserAction ReadUserAction()
{
	std::string to_be_displayed = "Choose which user action you want to take";
	return (enUserAction)ReadNumber::ReadIntNumberBetweenFromAndTo(1, 6, to_be_displayed);
}

// List Users

void ListUsers(std::vector <stUser>& v_user_data)
{
	system("cls");

	std::cout << "\n\t\t\t\t\t" << "User List [" << v_user_data.size() << "] user(s)";

	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	std::cout << "| " << std::left << std::setw(15) << "User Name";
	std::cout << "| " << std::left << std::setw(15) << "Password";
	std::cout << "| " << std::left << std::setw(25) << "Permissions";

	std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

	stUser user;

	for (int i = 0; i < v_user_data.size(); i++)
	{
		user = v_user_data[i];

		std::cout << "| " << std::left << std::setw(15) << user.user_name;
		std::cout << "| " << std::left << std::setw(15) << user.password;
		std::cout << "| " << std::left << std::setw(25) << user.permission;

		std::cout << std::endl;
	}

	std::cout << "----------------------------------------------------------------------------------------------------------\n";
}

// Add New User

int GetUserPermissions()
{
	int permission = 0;
	std::cout << "\nDo you want to give access to:\n";

	std::vector <std::string> v_permissions = {
		"Show Client List",
		"Add New Client",
		"Delete Client",
		"Update Client Info",
		"Find Client",
		"Transactions",
		"Manage Users"
	};

	for (short i = 0; i < v_permissions.size(); i++)
	{
		std::cout << v_permissions[i] << " (Y/N):\n";
		if (GetIsYesNo::GetIsYesNo())
		{
			permission += (int)pow(2, i);
		}
	}

	return permission;
}

bool UserNameIsExist(std::vector <stUser>& v_user_data, std::string user_name,
	std::string message = "Sorry, username you entered does not exist!\n")
{
	for (stUser& st : v_user_data)
	{
		if (st.user_name == user_name)
		{
			st.is_user_delete = true;
			return true;
		}
	}

	if (!message.empty())
		std::cout << message;

	return false;
}

stUser ReadUserData(std::vector <stUser>& v_user_data)
{
	stUser user;

	bool user_name_is_exist = false;
	do
	{
		user.user_name = ReadString::ReadString("Enter username");
		
		user_name_is_exist = UserNameIsExist(v_user_data, user.user_name, "");
		if (user_name_is_exist)
		{
			std::cout << "User with [" << user.user_name << "] already exists!\n";
			std::cout << "Enter another username:\n";
		}

	} while (user_name_is_exist);

	user.password = ReadString::ReadString("Enter Password");
	std::cout << "Do you want to give this user a full permission! (Y/N) ";

	bool full_permission = GetIsYesNo::GetIsYesNo();
	
	if (full_permission)
		user.permission = -1;
	else
		user.permission = GetUserPermissions();

	return user;
}

std::string UserDataToString(stUser user)
{
	return user.user_name + delimiter + user.password + delimiter + std::to_string(user.permission);
}

void AddNewUser(std::vector <stUser>& v_user_data)
{
	stUser user = ReadUserData(v_user_data);
	std::string line = UserDataToString(user);
	AddStrToFile(line, users_file_name);
	v_user_data = FillUserDataVectorFromTxtFile();
}

// Delete User

short FindUserIndex(std::string user_name, std::vector <stUser>& v_user_data)
{
	short counter = 0;
	for (stUser st : v_user_data)
	{
		if (st.user_name == user_name)
			return counter;

		counter++;
	}
}

void DisplayUser(short index_of_user, std::vector <stUser>& v_user_data)
{
	std::vector <std::string> permissions = { "Half Permission", "Full Permission" };

	std::cout << "\n===============================   User Found Successfully   ============================\n\n";
	std::cout << std::setw(20) << "Username : " << std::setw(40) << v_user_data[index_of_user].user_name << std::endl;
	std::cout << std::setw(20) << "Password : " << std::setw(40) << v_user_data[index_of_user].password << std::endl;
	std::cout << std::setw(20) << "Permission : " << std::setw(40) << permissions[v_user_data[index_of_user].permission] << std::endl;
	std::cout << "\n========================================================================================\n";
}

void UserDataToFile(std::vector <stUser>& v_user_data)
{
	for (stUser st : v_user_data)
	{
		if (!st.is_user_delete)
			AddStrToFile(UserDataToString(st), users_file_name);
	}
}

void DeleteUser(std::vector <stUser>& v_user_data)
{
	std::string user_name;
	do
	{
		user_name = ReadString::ReadString("Enter username of the user you want to delete");

		if (user_name == "Admin")
		{
			std::cout << "You cannot delete Admin!\n";
			return;
		}

	} while (!UserNameIsExist(v_user_data, user_name));

	short index_of_user = FindUserIndex(user_name, v_user_data);
	DisplayUser(index_of_user, v_user_data);

	if (ConfirmAction())
	{
		EraseFile(users_file_name);
		UserDataToFile(v_user_data);
		std::cout << "User Deleted Successfully!\n";
	}
	else
	{
		std::cout << "Cancelled!\n";
	}

	v_user_data = FillUserDataVectorFromTxtFile();
}

// Update User

void MarkIsUpdate(std::string user_name, std::vector <stUser>& v_user_data)
{
	for (stUser& st : v_user_data)
	{
		if (st.user_name == user_name)
		{
			st.is_user_update = true;
			break;
		}
	}
}

void UpdateVectUserData(std::vector <stUser>& v_user_data)
{
	for (stUser& st : v_user_data)
	{
		if (st.is_user_update)
		{
			st = ReadUserData(v_user_data);
			break;
		}
	}
}

void UpdateUser(std::vector <stUser>& v_user_data)
{
	std::string user_name;
	do
	{
		user_name = ReadString::ReadString("Enter the username you want to update");
		MarkIsUpdate(user_name, v_user_data);

	} while (!UserNameIsExist(v_user_data, user_name));

	short index_of_user = FindUserIndex(user_name, v_user_data);
	DisplayUser(index_of_user, v_user_data);

	UpdateVectUserData(v_user_data);

	if (ConfirmAction())
	{
		EraseFile(users_file_name);
		UserDataToFile(v_user_data);
		v_user_data = FillUserDataVectorFromTxtFile();
	}
	else
	{
		v_user_data = FillUserDataVectorFromTxtFile();
		std::cout << "Cancelled!\n";
	}
}

// Find User

void FindUser(std::vector <stUser>& v_user_data)
{
	std::string user_name;
	do
	{
		user_name = ReadString::ReadString("Enter username you want to lookup at");

	} while (!UserNameIsExist(v_user_data, user_name));

	short index_of_user = FindUserIndex(user_name, v_user_data);
	DisplayUser(index_of_user, v_user_data);
}

void TakeUserAction(std::vector <stUser>& v_user_data, enUserAction user_action)
{
	switch (user_action)
	{
	case enUserAction::list_users:
		ListUsers(v_user_data);
		break;
	case enUserAction::add_new_user:
		AddNewUser(v_user_data);
		break;
	case enUserAction::delete_user:
		DeleteUser(v_user_data);
		break;
	case enUserAction::update_user:
		UpdateUser(v_user_data);
		break;
	case enUserAction::find_user:
		FindUser(v_user_data);
		break;
	case enUserAction::user_main_menue:
		break;
	}
}

void ManageUsers(std::vector <stUser>& v_user_data)
{
	do
	{
		DisplayManageUsersScreen();

		enUserAction user_action = ReadUserAction();

		TakeUserAction(v_user_data, user_action);

		if (user_action == enUserAction::user_main_menue)
			break;

	} while (MoreAction("Do you want to take more user actions"));
}

void TakeAction(enAction en_action, std::vector <stClientInfo>& v_client_data, std::vector <stUser>& v_user_data)
{
	system("cls");
	switch (en_action)
	{
	case enAction::show_client_list:
		ShowClientList(v_client_data);
		break;
	case enAction::add_new_client:
		AddNewClient(v_client_data);
		std::cout << "Client Added Successfully!\n";
		break;
	case enAction::delete_client:
		DeleteClient(v_client_data);
		break;
	case enAction::update_client_info:
		UpdateClientInfo(v_client_data);
		std::cout << "Client Updated Successfully!\n";
		break;
	case enAction::find_client:
		FindClient(v_client_data);
		break;
	case enAction::transactions:
		Transaction(v_client_data);
		break;
	case enAction::manage_users:
		ManageUsers(v_user_data);
		break;
	default:
		break;
	}
}

bool BackToMainMenue(bool pause)
{
	if (pause)
	{
		std::cout << "Press Any Key To Back To Main Menue...";
		system("pause>0");
	}

	system("cls");

	return true;
}

void ShowEndScreen()
{
	std::cout << "\n------------------------------------\n";
	std::cout << "\t Programme Ends :)";
	std::cout << "\n------------------------------------\n";
}

stUser ReadUser()
{
	stUser user;
	
	std::cout << "Enter Username: ";
	std::cin >> user.user_name;

	std::cout << "Enter Password: ";
	std::cin >> user.password;

	return user;
}

stUser StrToUserData(std::string str)
{
	std::vector <std::string> v_user_data;
	SplitString(str, v_user_data, delimiter);

	stUser st_user_data;
	
	st_user_data.user_name = v_user_data[0];
	st_user_data.password = v_user_data[1];
	st_user_data.permission = stoi(v_user_data[2]);

	return st_user_data;
}

std::vector <stUser> FillUserDataVectorFromTxtFile()
{
	std::vector <stUser> v_user_data;

	std::fstream file;
	file.open(users_file_name, std::ios::in);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			v_user_data.push_back(StrToUserData(line));
		}

		file.close();
	}

	return v_user_data;
}

bool IsValidUser(stUser& user, std::vector <stUser> v_users)
{
	for (stUser st : v_users)
	{
		if (st.user_name == user.user_name && st.password == user.password)
		{
			user.permission = st.permission;

			return true;
		}
	}

	std::cout << "\nInvalid Username/Password!\n";

	return false;
}

int main()
{
	std::vector <stUser> v_user_data = FillUserDataVectorFromTxtFile();

	stUser user;
	do
	{
		user = ReadUser();
	} while (!IsValidUser(user, v_user_data));

	std::cout << std::endl;

	bool pause = true;
	do
	{
		DisplayHeadMessage();

		enAction en_action = ReadAction(user);

		if (en_action == enAction::logout)
		{
			system("cls");

			do
			{
				user = ReadUser();
			} while (!IsValidUser(user, v_user_data));

			continue;
		}

		if (en_action == enAction::denied)
			ShowAccessDeniedMenue();
		else
		{
			std::vector <stClientInfo> v_client_data = FillClientDataVectorFromTxtFile();

			TakeAction(en_action, v_client_data, v_user_data);

			if (en_action == enAction::transactions)
				pause = false;
			else
				pause = true;

			if (en_action == enAction::end_programme)
				break;
		}

		BackToMainMenue(pause);

	} while (true);

	ShowEndScreen();

	return 0;
}