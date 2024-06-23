#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "clsString.h"  // Include header file for string manipulation
#include "clsDate.h"    // Include header file for date operations
#include "clsUser.h"    // Include header file for user operations
#include "clsClient.h"  // Include header file for client operations

class clsLogs
{
private:
	std::string _date_time;
	clsUser _user = clsUser::GetEmptyUser();
	clsClient _source_client = clsClient::GetEmptyClient();
	clsClient _destination_client = clsClient::GetEmptyClient();
	float _transfer_amount;

	static clsLogs _ConvertStrToLoginRegister(std::string str)
	{
		// Convert string to login register entry
		std::vector<std::string> v_login_register = clsString::Split(str, ", ");
		clsUser user = clsUser::Find(v_login_register[1], clsUser::DecryptPassword(v_login_register[2]));

		return clsLogs(v_login_register[0], user, clsClient::GetEmptyClient(), clsClient::GetEmptyClient(),
			0.0);
	}

	static clsLogs _ConvertStrTransferRegister(std::string str)
	{
		// Convert string to transfer register entry
		std::vector<std::string> v_transfer_register = clsString::Split(str, ", ");

		return clsLogs(v_transfer_register[0], clsUser::Find(v_transfer_register[6]),
			clsClient::Find(v_transfer_register[1]), clsClient::Find(v_transfer_register[2]),
			stof(v_transfer_register[3]));
	}

	static std::vector<clsLogs> _LoadLoginRegisterFromTxt()
	{
		// Load login register data from file
		std::vector<clsLogs> v_login_register;

		std::fstream file;
		file.open("Login.txt", std::ios::in);
		if (file.is_open())
		{
			std::string line;
			while (getline(file, line))
			{
				v_login_register.push_back(_ConvertStrToLoginRegister(line));
			}

			file.close();
		}

		return v_login_register;
	}

	static std::vector<clsLogs> _LoadTransferRegisterFromTxt()
	{
		// Load transfer register data from file
		std::vector<clsLogs> v_transfer_register;

		std::fstream file;
		file.open("TransferLog.txt", std::ios::in);
		if (file.is_open())
		{
			std::string line;
			while (getline(file, line))
			{
				v_transfer_register.push_back(_ConvertStrTransferRegister(line));
			}

			file.close();
		}

		return v_transfer_register;
	}

	static std::string _GetLoginRecord(std::string delimiter = ", ")
	{
		// Create login record string
		std::string login_record = "";

		login_record += clsDate::GetSystemDateTimeStr() + delimiter +
			current_user.user_name + delimiter +
			clsUser::EncryptPassword(current_user.password) + delimiter +
			std::to_string(current_user.permissions);

		return login_record;
	}

	static std::string _GetTransferRecord(clsClient source_client, clsClient destination_client,
		float transfer_amount, std::string delimiter = ", ")
	{
		// Create transfer record string
		std::string transaction_record = "";

		transaction_record += clsDate::GetSystemDateTimeStr() + delimiter +
			source_client.GetAccountNumber() + delimiter +
			destination_client.GetAccountNumber() + delimiter +
			std::to_string(transfer_amount) + delimiter +
			std::to_string(source_client.balance) + delimiter +
			std::to_string(destination_client.balance) + delimiter +
			current_user.user_name;

		return transaction_record;
	}

public:
	// Constructors and property declarations

	clsLogs(std::string date_time, clsUser user, clsClient source_client, clsClient destination_client,
		float transfer_amount)
	{
		_date_time = date_time;
		_user = user;
		_source_client = source_client;
		_destination_client = destination_client;
		_transfer_amount = transfer_amount;
	}

	void SetDateTime(std::string date_time)
	{
		_date_time = date_time;
	}
	void SetUser(clsUser user)
	{
		_user = user;
	}
	void SetSourceClient(clsClient source_client)
	{
		_source_client = source_client;
	}
	void SetDestinationClient(clsClient destination_client)
	{
		_destination_client = destination_client;
	}
	void SetTransferAmount(float transfer_amount)
	{
		_transfer_amount = transfer_amount;
	}

	std::string GetDateTime()
	{
		return _date_time;
	}
	clsUser GetUser()
	{
		return _user;
	}
	clsClient GetSourceClient()
	{
		return _source_client;
	}
	clsClient GetDestinationClient()
	{
		return _destination_client;
	}
	float GetTransferAmount()
	{
		return _transfer_amount;
	}

	// Property declaration for easy access to value

	__declspec(property(get = GetDateTime, put = SetDateTime)) std::string date_time;
	__declspec(property(get = GetUser, put = SetUser)) clsUser user;
	__declspec(property(get = GetSourceClient, put = SetSourceClient)) clsClient source_client;
	__declspec(property(get = GetDestinationClient, put = SetDestinationClient)) clsClient destination_client;
	__declspec(property(get = GetTransferAmount, put = SetTransferAmount)) float trasfer_amount;

	// Static methods for accessing log data

	static std::vector<clsLogs> GetLoginRegister()
	{
		return _LoadLoginRegisterFromTxt();
	}

	static std::vector<clsLogs> GetTransferRegister()
	{
		return _LoadTransferRegisterFromTxt();
	}

	// Static methods for logging actions

	static void RegisterLogin()
	{
		std::string login_record = _GetLoginRecord();

		std::fstream file;
		file.open("Login.txt", std::ios::out | std::ios::app);
		if (file.is_open())
		{
			file << login_record << "\n";
			file.close();
		}
	}

	static void RegisterTransferLog(clsClient source_client, clsClient destination_client,
		float transfer_amount)
	{
		std::string transfer_record = _GetTransferRecord(source_client, destination_client,
			transfer_amount);

		std::fstream file;
		file.open("TransferLog.txt", std::ios::out | std::ios::app);
		if (file.is_open())
		{
			file << transfer_record << "\n";
			file.close();
		}
	}
};

