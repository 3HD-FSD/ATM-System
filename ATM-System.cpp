#include <iostream>
#include "client.h"
#include "input.h"
#include "format.h"
#include "transactions.h"

using namespace std;
using namespace client;
using namespace format;
using namespace input;
using namespace transactions;

void login();
void handleMainMenu();

enum enMainMenuOption
{
    QuickWithdraw = 1,
    NormalWithdraw = 2,
    Deposit = 3,
    CheckBalance = 4,
    Logout = 5,
};

Client currentClient;

void displayLoginMenu()
{
    system("cls");
    printHeader("| Login |");
}

void displayPermissionsDeniedMenu()
{
    system("cls");
    printHeader("| Permissions Denied |");
    cout << "\nSorry, the client was not found in the system :(" << endl;
    cout << "Please contact support for help...\n" << endl;
    cout << "\a";
}

void displayMainMenu()
{
    system("cls");
    printHeader(" | ATM System |");
    cout << "|" << "    [1] Quick Withdraw" << formatString(17, "|", RIGHT) << endl;
    cout << "|" << "    [2] Normal Withdraw" << formatString(16, "|", RIGHT) << endl;
    cout << "|" << "    [3] Deposit" << formatString(24, "|", RIGHT) << endl;
    cout << "|" << "    [4] Check Balance" << formatString(18, "|", RIGHT) << endl;
    cout << "|" << "    [5] Logout" << formatString(25, "|", RIGHT) << endl;
    printFooter("| Made By 3HD ", RIGHT);
}

// Perform Main Menu Option.
void performMainMenuOption(enMainMenuOption choice)
{
    switch (choice)
    {
    case enMainMenuOption::QuickWithdraw:
        if (isStillFound(currentClient))
        {
            system("cls");
            quickWithdraw(currentClient);
            cout << "Press ENTER key to back to main menu...";
            system("pause>0");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            cout << "Press ENTER key to back to login menu...";
            system("pause>0");
            login();
        }
        break;
    case enMainMenuOption::NormalWithdraw:
        if (isStillFound(currentClient))
        {
            system("cls");
            normalWithdraw(currentClient);
            cout << "Press ENTER key to back to main menu...";
            system("pause>0");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            cout << "Press ENTER key to back to login menu...";
            system("pause>0");
            login();
        }
        break;
    case enMainMenuOption::Deposit:
        if (isStillFound(currentClient))
        {
            system("cls");
            deposit(currentClient);
            cout << "Press ENTER key to back to main menu...";
            system("pause>0");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            cout << "Press ENTER key to back to login menu...";
            system("pause>0");
            login();
        }
        break;
    case enMainMenuOption::CheckBalance:
        if (isStillFound(currentClient))
        {
            system("cls");
            checkBalance(currentClient);
            cout << "Press ENTER key to back to main menu...";
            system("pause>0");
            handleMainMenu();
        }
        else
        {
            displayPermissionsDeniedMenu();
            cout << "Press ENTER key to back to login menu...";
            system("pause>0");
            login();
        }
        break;
    case enMainMenuOption::Logout:
        login();
        break;
    default:
        cout << "Error!" << endl;
        break;
    }
}
// Show Main Menu.
void handleMainMenu()
{
    displayMainMenu();
    enMainMenuOption choice = enMainMenuOption(readNumberInRange("Choose any service [1 -> 5] : ", 1, 5));
    performMainMenuOption(choice);
}

// Find Client In File.
bool isClientFound(Client clientInfo)
{
    vector<Client> vClients = loadClientsDataFromFile();
    for (Client client : vClients)
    {
        if (clientInfo.accountNumber == client.accountNumber && clientInfo.pinCode == client.pinCode)
        {
            currentClient = client;
            return true;
        }
    }
    return false;
}

// Read Login Info.
Client readLoginInfo()
{
    Client client;
    client.accountNumber = readString("Enter account number : ");
    client.pinCode = readString("Enter PIN code : ");
    return client;
}
// Login Menu
void login()
{
    displayLoginMenu();
    bool isFound = false;
    do
    {
        Client client = readLoginInfo();
        if (isClientFound(client))
        {
            isFound = true;
            handleMainMenu();
        }
        else
        {
            displayLoginMenu();
            cout << "Invalid account number/PIN code :(" << endl;
        }
    } while (isFound == false);
}
// Start App.
int main()
{
    login();
    return 0;
}