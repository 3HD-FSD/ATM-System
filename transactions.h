#pragma once
#include <iostream>
#include "client.h"
#include "format.h"
#include "input.h"

using namespace std;
using namespace client;
using namespace format;
using namespace input;

namespace transactions
{
    //*************************************************************
    // Trasactions Functions.
    //*************************************************************
    // Add Amount To Balance Withdraw/Deposit.
    void addAmountToBalance(double amount, Client &currentClient, string transactionStatus, vector<Client> &vClients)
    {
        for (Client &clientData : vClients)
        {
            if (clientData.accountNumber == currentClient.accountNumber)
            {
                clientData.balance += amount;
                currentClient.balance = clientData.balance;
                cout << transactionStatus << "New balance : " << clientData.balance << "$" << endl;
                break;
            }
        }
    }

    // Show Quick Withdraw Amounts.
    void showQuickWithdrawAmountsMenu()
    {
        system("cls");
        printHeader("| Quick Withdraw |");
        cout << "|" << "    [1] 20 " << "    [2] 50  " << formatString(16, "|", RIGHT) << endl;
        cout << "|" << "    [3] 100" << "    [4] 200 " << formatString(16, "|", RIGHT) << endl;
        cout << "|" << "    [5] 400" << "    [6] 600 " << formatString(16, "|", RIGHT) << endl;
        cout << "|" << "    [7] 800" << "    [8] 1000" << formatString(16, "|", RIGHT) << endl;
        cout << "|" << "    [9] Exit" << formatString(27, "|", RIGHT) << endl;
        cout << characters('-', 40) << endl;
    }

    //[1] Quick Withdraw.
    void quickWithdraw(Client &currentClient)
    {
        showQuickWithdrawAmountsMenu();
        cout << "Your balance is " << currentClient.balance << "$." << endl;
        short amount = readNumberInRange("Choose withdraw amount or exit [1 -> 9] : ", 1, 9);
        if (amount == 9)
        {
            cout << "\n";
            return;
        }
        int amounts[] = {0, 20, 50, 100, 200, 400, 600, 800, 1000};
        while (currentClient.balance < amounts[amount])
        {
            cout << "\nAmount exceeds the balance, you can withdraw up to " << currentClient.balance << endl;
            amount = readNumberInRange("\nChoose withdraw amount or exit [1 -> 9] : ", 1, 9);
            if (amount == 9)
            {
                cout << "\n";
                return;
            }
        }
        char choice = readChar("\nAre you sure you want to perform this transaction? Y / N : ");
        if (toupper(choice) == 'Y')
        {
            vector<Client> vClients = loadClientsDataFromFile();
            addAmountToBalance(-1 * amounts[amount], currentClient, "\nWithdraw successfully, ", vClients);
            saveClientDataFromVectorToFile(vClients);
        }
        cout << endl;
    }

    // Read Withdraw Amount And Check It If Exceeds The Balance.
    double readWithdrawAmount(Client &currentClient)
    {
        double amount;
        do
        {
            amount = readPositiveNumber("Enter withdraw amount : ");
            if (amount <= currentClient.balance)
            {
                break;
            }
            cout << "\nAmount exceeds the balance, you can withdraw up to " << currentClient.balance << endl;
        } while (amount > currentClient.balance);
        return amount;
    }

    //[2] Withdraw Money.
    void normalWithdraw(Client &currentClient)
    {
        printHeader("| Normal Withdraw |");
        cout << "\nYour Balance is " << currentClient.balance << "$.\n" << endl;
        double amount = readWithdrawAmount(currentClient);
        char choice = readChar("\nAre you sure you want to perform this transaction? Y / N : ");
        if (toupper(choice) == 'Y')
        {
            vector<Client> vClients = loadClientsDataFromFile();
            addAmountToBalance(-1 * amount, currentClient, "\nWithdraw successfully, ", vClients);
            saveClientDataFromVectorToFile(vClients);
        }
        cout << endl;
    }

    //[3] Deposit Money.
    void deposit(Client &currentClient)
    {
        printHeader("| Deposit |");
        cout << "\nYour Balance is " << currentClient.balance << "$.\n" << endl;
        double amount = readPositiveNumber("Enter deposit amount : ");
        char choice = readChar("\nAre you sure you want to perform this transaction? Y / N : ");
        if (toupper(choice) == 'Y')
        {
            vector<Client> vClients = loadClientsDataFromFile();
            addAmountToBalance(amount, currentClient, "\nDeposit successfully, ", vClients);
            saveClientDataFromVectorToFile(vClients);
        }
        cout << endl;
    }

    //[4] Check Balance.
    void checkBalance(Client &currentClient)
    {
        printHeader("| Check Balance |");
        cout << "\nYour Balance is " << currentClient.balance << "$.\n"
             << endl;
    }
    //*************************************************************
}