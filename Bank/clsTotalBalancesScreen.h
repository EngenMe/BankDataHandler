#pragma once

#include <iomanip> // For std::setw
#include <vector>
#include "clsScreen.h" // Assuming clsScreen is defined here
#include "clsClient.h" // Assuming clsClient is defined here
#include "clsNumber.h" // Assuming clsNumber is defined here

class clsTotalBalancesScreen : protected clsScreen
{
public:
    // Static function to display total balances list
    static void ShowTotalBalancesList()
    {
        // Clear screen
        system("cls");

        // Get list of clients
        std::vector<clsClient> v_clients = clsClient::GetClientsList();

        // Print header with total number of clients
        PrintHead("Total Balances [" + std::to_string(v_clients.size()) + "] Client(s)");

        // Table header
        std::cout << "\n--------------------------------------------------------------------\n";
        std::cout << "| " << std::left << std::setw(15) << "Account Number";
        std::cout << "| " << std::left << std::setw(25) << "Client Name";
        std::cout << "| " << std::left << std::setw(15) << "Balance";
        std::cout << "\n--------------------------------------------------------------------\n";

        // Vector to store balances
        std::vector<float> v_balances;

        // Print client details and accumulate balances
        for (int i = 0; i < v_clients.size(); i++)
        {
            clsClient client = v_clients[i];

            std::cout << "| " << std::left << std::setw(15) << client.GetAccountNumber();
            std::cout << "| " << std::left << std::setw(25) << client.GetFullName();
            std::cout << "| " << std::left << std::setw(15) << client.balance;
            std::cout << std::endl;

            v_balances.push_back(client.balance);
        }

        // Table footer
        std::cout << "--------------------------------------------------------------------\n";

        // Calculate and display total balance
        float sum = clsNumber::Sum(v_balances);
        std::cout << "\n\t\tTotal Balances = " << sum << std::endl;
        std::cout << "\t\t( " << clsNumber::NumberToText(sum) << ")\n\n";
    }
};

