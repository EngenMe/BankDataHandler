#pragma once

#include <vector>

#include "Global.h"
#include "clsBool.h"
#include "clsUser.h"
#include "clsDate.h"
#include "clsClient.h"
#include "clsNumber.h"
#include "clsCurrency.h"

class clsScreen
{
protected:
    // Enumeration for different table printing modes
    enum enTableMode
    {
        short_table,
        long_table
    };

    // Enumeration for different client card printing modes
    enum enClientCardMode
    {
        long_card,
        short_card
    };

    // Function to print header information
    static void PrintHead(std::string title, enTableMode table_mode = enTableMode::short_table, short size = 0,
        std::string size_title = "")
    {
        // Display current user and date/time
        std::cout << "User: " << current_user.user_name << std::endl;
        std::cout << "Date: " << clsDate::GetSystemDateTimeStr() << std::endl << std::endl;

        // Print header based on table mode
        if (table_mode == enTableMode::long_table)
        {
            std::cout << "\n================================================================================================================================================\n";
            std::cout << "\n\t\t\t\t\t\t\t *** " << title << " [" << size << "] " << size_title << "(s) ***\n";
            std::cout << "\n================================================================================================================================================\n";
        }
        else if (table_mode == enTableMode::short_table && size > 0)
        {
            std::cout << "============================================================================================\n";
            std::cout << "\t\t\t *** " << title << " [" << size << "] " << size_title << "(s) ***\n";
            std::cout << "============================================================================================\n";
        }
        else
        {
            std::cout << "========================================================================\n";
            std::cout << "\t\t\t *** " << title << " ***\n";
            std::cout << "========================================================================\n";
        }
    }

    // Function to print a list of options
    static void PrintOptions(std::vector<std::string> v_options)
    {
        for (int i = 1; i <= v_options.size(); i++)
        {
            std::cout << "\t\t [" << i << "] " << v_options[i - 1] << std::endl;
        }
        std::cout << "========================================================================\n";
    }

    // Function to read an account number, with validation
    static std::string ReadAccountNumber(std::string error_message, bool exist_case,
        std::string message = "Enter account number: ")
    {
        std::string account_number = clsString::ReadString(message);

        // Validate account number existence based on exist_case flag
        while (clsClient::IsClientExist(account_number) != exist_case)
        {
            std::cout << error_message;
            account_number = clsString::ReadString("Enter Another One: ");
        }

        return account_number;
    }

    // Function to read a username, with validation
    static std::string ReadUserName(std::string error_message, bool exist_case)
    {
        std::string user_name = clsString::ReadString("Enter username: ");
        while (clsUser::IsUserExist(user_name) != exist_case)
        {
            std::cout << error_message;
            user_name = clsString::ReadString("Enter Another One: ");
        }

        return user_name;
    }

    // Function to read country name, with validation
    static std::string ReadCountryName(std::string error_message, bool exist_case)
    {
        std::string country_name = clsString::ReadString("Enter country name: ");
        while (clsCurrency::IsCurrencyExistByCountryName(country_name) != exist_case)
        {
            std::cout << error_message;
            country_name = clsString::ReadString("Enter Another One: ");
        }

        return country_name;
    }

    // Function to read currency code, with validation
    static std::string ReadCurrencyCode(std::string error_message, bool exist_case)
    {
        std::string currency_code = clsString::ReadString("Enter currency code: ");
        while (clsCurrency::IsCurrencyExistByCurrencyCode(currency_code) != exist_case)
        {
            std::cout << error_message;
            currency_code = clsString::ReadString("Enter Another One: ");
        }

        return currency_code;
    }

    // Function to read client information and populate a clsClient object
    static void ReadClientInfo(clsClient& client)
    {
        client.first_name = clsString::ReadString("Enter First Name: ");
        client.last_name = clsString::ReadString("Enter Last Name: ");
        client.email = clsString::ReadString("Enter Email: ");
        client.phone = clsString::ReadString("Enter Phone: ");
        client.pin = clsString::ReadString("Enter PIN: ");
        client.balance = clsNumber::ReadFloatNumber("Enter Balance: ");
    }

    // Function to read user information and populate a clsUser object
    static void ReadUserInfo(clsUser& user)
    {
        user.first_name = clsString::ReadString("Enter First Name: ");
        user.last_name = clsString::ReadString("Enter Last Name: ");
        user.email = clsString::ReadString("Enter Email: ");
        user.phone = clsString::ReadString("Enter Phone: ");
        user.password = clsString::ReadString("Enter Password: ");
    }

    // Function to read user permissions and set them in a clsUser object
    static void ReadUserPermissions(clsUser& user)
    {
        std::cout << "\nEnter Permissions:\n";
        if (clsBool::GetYesNo("Full permissions (Y/N): "))
        {
            user.permissions = -1; // Full permissions flag
            return;
        }

        user.permissions = 0; // Initialize permissions
        user.permissions += ((clsBool::GetYesNo("List Clients Permission (Y/N): ")) ?
            clsUser::enPermissions::list_clients : 0);
        user.permissions += ((clsBool::GetYesNo("Add New Client Permission (Y/N): ")) ?
            clsUser::enPermissions::add_new_client : 0);
        user.permissions += ((clsBool::GetYesNo("Delete Client Permission (Y/N): ")) ?
            clsUser::enPermissions::delete_client : 0);
        user.permissions += ((clsBool::GetYesNo("Update Clients Permission (Y/N): ")) ?
            clsUser::enPermissions::update_client : 0);
        user.permissions += ((clsBool::GetYesNo("Find Client Permission (Y/N): ")) ?
            clsUser::enPermissions::find_client : 0);
        user.permissions += ((clsBool::GetYesNo("Transactions Permission (Y/N): ")) ?
            clsUser::enPermissions::transactions : 0);
        user.permissions += ((clsBool::GetYesNo("Manage Users Permission (Y/N): ")) ?
            clsUser::enPermissions::manage_users : 0);
        user.permissions += ((clsBool::GetYesNo("Login Register Permission (Y/N): ")) ?
            clsUser::enPermissions::login_register : 0);
    }

    // Function to print client information in card format
    static void PrintClientCard(clsClient client, enClientCardMode mode = enClientCardMode::long_card)
    {
        if (mode == enClientCardMode::short_card)
        {
            std::cout << "\nClient Card:";
            std::cout << "\n___________________";
            std::cout << "\nFull Name   : " << client.GetFullName();
            std::cout << "\nAcc. Number : " << client.GetAccountNumber();
            std::cout << "\nBalance     : " << client.balance;
            std::cout << "\n___________________\n";
        }
        else
        {
            std::cout << "\nClient Card:";
            std::cout << "\n___________________";
            std::cout << "\nFirstName   : " << client.first_name;
            std::cout << "\nLastName    : " << client.last_name;
            std::cout << "\nFull Name   : " << client.GetFullName();
            std::cout << "\nEmail       : " << client.email;
            std::cout << "\nPhone       : " << client.phone;
            std::cout << "\nAcc. Number : " << client.GetAccountNumber();
            std::cout << "\nPassword    : " << client.pin;
            std::cout << "\nBalance     : " << client.balance;
            std::cout << "\n___________________\n";
        }
    }

    // Function to print user information in card format
    static void PrintUserCard(clsUser user)
    {
        std::cout << "\nUser Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << user.first_name;
        std::cout << "\nLastName    : " << user.last_name;
        std::cout << "\nFull Name   : " << user.GetFullName();
        std::cout << "\nEmail       : " << user.email;
        std::cout << "\nPhone       : " << user.phone;
        std::cout << "\nUsername    : " << user.user_name;
        std::cout << "\nPassword    : " << user.password;
        std::cout << "\nPermissions : " << user.permissions;
        std::cout << "\n___________________\n";
    }

    // Function to print currency information in card format
    static void PrintCurrencyCard(clsCurrency currency)
    {
        std::cout << "\nCurrency:";
        std::cout << "\n___________________";
        std::cout << "\nCountry       : " << currency.GetCountryName();
        std::cout << "\nCurrency Code : " << currency.GetCurrencyCode();
        std::cout << "\nCurrency Name : " << currency.GetCurrencyName();
        std::cout << "\nUSD Rate      : " << currency.GetUSDRate();
        std::cout << "\n___________________\n";
    }

    // Function to display an access denied screen
    static void AccessDeniedScreen()
    {
        system("cls");
        PrintHead("Access Denied - Contact Your Admin!");
    }
};

