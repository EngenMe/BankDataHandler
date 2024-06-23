#pragma once

#include <fstream>      // Include standard file stream header for file operations
#include "clsPerson.h"  // Include header file for clsPerson class
#include "clsString.h"  // Include header file for clsString class

class clsClient : public clsPerson
{
private:
    std::string _account_number;
    std::string _pin;
    float _balance;
    bool mark_for_delete = false;

    enum enMode
    {
        empty,
        update,
        add_new
    };
    enMode _mode;

    // Private method to convert string representation to clsClient object
    static clsClient _ConvertStrToClient(std::string str)
    {
        std::vector<std::string> v_client = clsString::Split(str, ", ");

        return clsClient(enMode::update, v_client[0], v_client[1], v_client[2], v_client[3], v_client[4],
            v_client[5], std::stof(v_client[6]));
    }

    // Private method to convert clsClient object to string representation
    std::string _ConvertClientToStr(clsClient client, std::string delimiter = ", ")
    {
        return client.first_name + delimiter +
            client.last_name + delimiter +
            client.email + delimiter +
            client.phone + delimiter +
            client._account_number + delimiter +
            client._pin + delimiter +
            std::to_string(client.balance);
    }

    // Private method to create an empty clsClient object
    static clsClient _EmptyClient()
    {
        return clsClient(enMode::empty, "", "", "", "", "", "", 0.0);
    }

    // Private method to load clients from a text file
    static std::vector<clsClient> _LoadClientsFromTxt()
    {
        std::vector<clsClient> v_clients;

        std::fstream file;
        file.open("Clients.txt", std::ios::in);
        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                v_clients.push_back(_ConvertStrToClient(line));
            }

            file.close();
        }

        return v_clients;
    }

    // Private method to save clients to a text file
    void _SaveClientsToTxt(std::vector<clsClient> v_clients)
    {
        std::fstream file;
        file.open("Clients.txt", std::ios::out);

        if (file.is_open())
        {
            for (clsClient c : v_clients)
            {
                if (c.mark_for_delete)
                    continue;

                file << _ConvertClientToStr(c) << std::endl;
            }

            file.close();
        }
    }

    // Private method to add a client string to a text file
    void _AddClientToTxt(std::string client_str)
    {
        std::fstream file;
        std::string line;
        file.open("Clients.txt", std::ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {

            }
            file.close();
        }

        file.open("Clients.txt", std::ios::out | std::ios::app);
        if (file.is_open())
        {
            if (!line.empty())
                file << std::endl;

            file << client_str << std::endl;
            file.close();
        }
    }

    // Private method to update client information in the text file
    void _Update()
    {
        std::vector<clsClient> v_clients = _LoadClientsFromTxt();

        for (clsClient& c : v_clients)
        {
            if (c._account_number == GetAccountNumber())
            {
                c = *this;
                break;
            }
        }

        _SaveClientsToTxt(v_clients);
    }

    // Private method to add a new client to the text file
    void _AddNew()
    {
        _AddClientToTxt(_ConvertClientToStr(*this));
    }

public:
    // Constructor to initialize clsClient object with specified parameters
    clsClient(enMode mode, std::string first_name, std::string last_name, std::string email, std::string phone,
        std::string account_number, std::string pin, float balance) :
        clsPerson(first_name, last_name, email, phone)
    {
        _mode = mode;
        _account_number = account_number;
        _pin = pin;
        _balance = balance;
    }

    // Enumeration to indicate save operation status
    enum enSave
    {
        success,
        failed_empty_obj,
        failed_already_exist
    };

    // Setter method for setting client PIN
    void SetPin(std::string pin)
    {
        _pin = pin;
    }

    // Setter method for setting client balance
    void SetBalance(float balance)
    {
        _balance = balance;
    }

    // Method to check if the client object is empty
    bool IsEmpty()
    {
        return _mode == enMode::empty;
    }

    // Static method to check if a client with specified account number exists
    static bool IsClientExist(std::string account_number)
    {
        return !Find(account_number).IsEmpty();
    }

    // Getter method for retrieving client account number
    std::string GetAccountNumber()
    {
        return _account_number;
    }

    // Getter method for retrieving client PIN
    std::string GetPin()
    {
        return _pin;
    }

    // Getter method for retrieving client balance
    float GetBalance()
    {
        return _balance;
    }

    // Property declaration for client PIN
    __declspec(property(get = GetPin, put = SetPin)) std::string pin;

    // Property declaration for client balance
    __declspec(property(get = GetBalance, put = SetBalance)) float balance;

    // Static method to find a client by account number
    static clsClient Find(std::string account_number)
    {
        std::fstream file;
        file.open("Clients.txt", std::ios::in);

        while (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                clsClient client = _ConvertStrToClient(line);
                if (client._account_number == account_number)
                {
                    file.close();
                    return client;
                }
            }

            file.close();
        }

        return _EmptyClient();
    }

    // Static method to find a client by account number and PIN
    static clsClient Find(std::string account_number, std::string pin)
    {
        std::fstream file;
        file.open("Clients.txt", std::ios::in);

        while (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                clsClient client = _ConvertStrToClient(line);
                if (client._account_number == account_number && client._pin == pin)
                {
                    file.close();
                    return client;
                }
            }

            file.close();
        }

        return _EmptyClient();
    }

    // Method to save the client information based on current mode
    enSave Save()
    {
        switch (_mode)
        {
        case enMode::empty:
            if (IsEmpty())
                return enSave::failed_empty_obj;
        case enMode::update:
            _Update();
            return enSave::success;
        case enMode::add_new:
            if (IsClientExist(_account_number))
                return enSave::failed_already_exist;
            else
            {
                _AddNew();
                _mode = enMode::add_new;
                return enSave::success;
            }
        }
    }

    // Static method to create a new client object with specified account number
    static clsClient NewClientObj(std::string account_number)
    {
        return clsClient(enMode::add_new, "", "", "", "", account_number, "", 0.0);
    }

    // Method to mark the client for deletion and update the text file
    bool Delete()
    {
        std::vector<clsClient> v_clients = _LoadClientsFromTxt();

        for (clsClient& c : v_clients)
        {
            if (c._account_number == GetAccountNumber())
            {
                c.mark_for_delete = true;
                break;
            }
        }

        _SaveClientsToTxt(v_clients);
        *this = _EmptyClient();

        return true;
    }

    // Static method to get the list of all clients from the text file
    static std::vector<clsClient> GetClientsList()
    {
        return _LoadClientsFromTxt();
    }

    // Method to deposit funds into the client's account and save the updated balance
    void Deposit(float amount)
    {
        _balance += amount;
        Save();
    }

    // Method to withdraw funds from the client's account if sufficient balance is available
    bool Withdraw(float amount)
    {
        if (amount > _balance)
            return false;

        _balance -= amount;
        Save();
        return true;
    }

    // Static method to transfer funds from source client to destination client
    static void Transfer(clsClient& source_client, clsClient& destination_client, float amount)
    {
        source_client.Withdraw(amount);
        destination_client.Deposit(amount);

        source_client.Save();
        destination_client.Save();
    }

    // Static method to return an empty client object
    static clsClient GetEmptyClient()
    {
        return clsClient(enMode::empty, "", "", "", "", "", "", 0.0);
    }
};
