#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "clsPerson.h"
#include "clsString.h"
#include "InterfaceCommunication.h"

class clsUser : public clsPerson, public InterfaceCommunication
{
private:
    std::string _user_name;
    std::string _password;
    short _permissions;
    bool mark_for_delete = false;

    enum enMode
    {
        empty,
        update,
        add_new
    };
    enMode _mode;

    // Static method to get encryption key
    static short _GetEncryptionKey()
    {
        return 44;
    }

    // Static method to convert string to clsUser object
    static clsUser _ConvertStrToUser(std::string str)
    {
        std::vector<std::string> v_user = clsString::Split(str, ", ");

        return clsUser(enMode::update, v_user[0], v_user[1], v_user[2], v_user[3], v_user[4],
            DecryptPassword(v_user[5]), stoi(v_user[6]));
    }

    // Method to convert clsUser object to string
    std::string _ConvertUserToStr(clsUser user, std::string delimiter = ", ")
    {
        return user.first_name + delimiter +
            user.last_name + delimiter +
            user.email + delimiter +
            user.phone + delimiter +
            user._user_name + delimiter +
            EncryptPassword(user._password) + delimiter +
            std::to_string(user._permissions);
    }

    // Static method to return an empty clsUser object
    static clsUser _EmptyUser()
    {
        return clsUser(enMode::empty, "", "", "", "", "", "", 0);
    }

    // Static method to load users from "Users.txt"
    static std::vector<clsUser> _LoadUsersFromTxt()
    {
        std::vector<clsUser> v_users;

        std::fstream file;
        file.open("Users.txt", std::ios::in);
        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                v_users.push_back(_ConvertStrToUser(line));
            }

            file.close();
        }

        return v_users;
    }

    // Method to save users to "Users.txt"
    void _SaveUsersToTxt(std::vector<clsUser> v_users)
    {
        std::fstream file;
        file.open("Users.txt", std::ios::out);

        if (file.is_open())
        {
            for (clsUser c : v_users)
            {
                if (c.mark_for_delete)
                    continue;

                file << _ConvertUserToStr(c) << std::endl;
            }

            file.close();
        }
    }

    // Method to add user string to "Users.txt"
    void _AddUserToTxt(std::string user_str)
    {
        std::fstream file;
        std::string line;
        file.open("Users.txt", std::ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {

            }
            file.close();
        }

        file.open("Users.txt", std::ios::out | std::ios::app);
        if (file.is_open())
        {
            if (!line.empty())
                file << std::endl;

            file << user_str << std::endl;
            file.close();
        }
    }

    // Method to update user information
    void _Update()
    {
        std::vector<clsUser> v_users = _LoadUsersFromTxt();

        for (clsUser& c : v_users)
        {
            if (c.user_name == user_name)
            {
                c = *this;
                break;
            }
        }

        _SaveUsersToTxt(v_users);
    }

    // Method to add new user
    void _AddNew()
    {
        _AddUserToTxt(_ConvertUserToStr(*this));
    }

public:
    // Constructor to initialize clsUser object
    clsUser(enMode mode, std::string first_name, std::string last_name, std::string email, std::string phone,
        std::string user_name, std::string password, short permissions) :
        clsPerson(first_name, last_name, email, phone)
    {
        _mode = mode;
        _user_name = user_name;
        _password = password;
        _permissions = permissions;
    }

    // Enum for save operation result
    static enum enSave
    {
        success,
        failed_empty_obj,
        failed_already_exist
    };

    // Enum for user permissions
    static enum enPermissions
    {
        all = -1,
        list_clients = 1,
        add_new_client = 2,
        delete_client = 4,
        update_client = 8,
        find_client = 16,
        transactions = 32,
        manage_users = 64,
        login_register = 128,
        currency_exchange = 256
    };

    // Enum for access permission result
    static enum enAccessPermission
    {
        authorised,
        denied
    };

    // Setter for user_name property
    void SetUserName(std::string user_name)
    {
        _user_name = user_name;
    }

    // Setter for password property
    void SetPassword(std::string password)
    {
        _password = password;
    }

    // Setter for permissions property
    void SetPermissions(short permissions)
    {
        _permissions = permissions;
    }

    // Getter for user_name property
    std::string GetUserName()
    {
        return _user_name;
    }

    // Getter for password property
    std::string GetPassword()
    {
        return _password;
    }

    // Getter for permissions property
    short GetPermissions()
    {
        return _permissions;
    }

    // Method to check if user object is empty
    bool IsEmpty()
    {
        return _mode == enMode::empty;
    }

    // Static method to check if user exists by username
    static bool IsUserExist(std::string user_name)
    {
        return !Find(user_name).IsEmpty();
    }

    // Property for user_name using __declspec
    __declspec(property(get = GetUserName, put = SetUserName)) std::string user_name;

    // Property for password using __declspec
    __declspec(property(get = GetPassword, put = SetPassword)) std::string password;

    // Property for permissions using __declspec
    __declspec(property(get = GetPermissions, put = SetPermissions)) short permissions;

    // Static method to find user by username
    static clsUser Find(std::string user_name)
    {
        std::fstream file;
        file.open("Users.txt", std::ios::in);

        while (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                clsUser user = _ConvertStrToUser(line);
                if (user.user_name == user_name)
                {
                    file.close();
                    return user;
                }
            }

            file.close();
        }

        return _EmptyUser();
    }

    // Static method to find user by username and password
    static clsUser Find(std::string user_name, std::string password)
    {
        std::fstream file;
        file.open("Users.txt", std::ios::in);

        while (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                clsUser user = _ConvertStrToUser(line);
                if (user.user_name == user_name && user.password == password)
                {
                    file.close();
                    return user;
                }
            }

            file.close();
        }

        return _EmptyUser();
    }

    // Method to save user changes
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
            if (IsUserExist(_user_name))
                return enSave::failed_already_exist;
            else
            {
                _AddNew();
                _mode = enMode::add_new;
                return enSave::success;
            }
        }
    }

    // Static method to create a new empty user object
    static clsUser NewUserObj(std::string user_name)
    {
        return clsUser(enMode::add_new, "", "", "", "", user_name, "", 0);
    }

    // Method to delete user from users list
    bool Delete()
    {
        std::vector<clsUser> v_users = _LoadUsersFromTxt();

        for (clsUser& c : v_users)
        {
            if (c.user_name == user_name)
            {
                c.mark_for_delete = true;
                break;
            }
        }

        _SaveUsersToTxt(v_users);
        *this = _EmptyUser();

        return true;
    }

    // Static method to get list of all users
    static std::vector<clsUser> GetUsersList()
    {
        return _LoadUsersFromTxt();
    }

    // Method to check access permissions for user
    bool CheckAccessPermission(enPermissions permissions)
    {
        if ((this->permissions == enPermissions::all) || (permissions & this->permissions) == permissions)
            return enAccessPermission::authorised;

        return enAccessPermission::denied;
    }

    // Static method to get an empty user object
    static clsUser GetEmptyUser()
    {
        return clsUser(enMode::empty, "", "", "", "", "", "", 0);
    }

    // Static method to encrypt password
    static std::string EncryptPassword(std::string password)
    {
        short encryption_key = _GetEncryptionKey();
        std::string decrypted_password = "";
        for (char c : password)
        {
            decrypted_password += (char)((int)c + encryption_key);
        }

        return decrypted_password;
    }

    // Static method to decrypt password
    static std::string DecryptPassword(std::string encrypted_password)
    {
        short encryption_key = _GetEncryptionKey();
        std::string decrypted_password = "";
        for (char c : encrypted_password)
        {
            decrypted_password += (char)((int)c - encryption_key);
        }

        return decrypted_password;
    }

    // Method to send email (from InterfaceCommunication)
    void SendEmail(std::string destination_email, std::string title, std::string body)
    {
        // Placeholder method for sending email
    }

    // Method to send SMS (from InterfaceCommunication)
    void SendSMS(std::string destination_phone, std::string message)
    {
        // Placeholder method for sending SMS
    }
};

