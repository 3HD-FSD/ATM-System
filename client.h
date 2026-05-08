#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "format.h"
#include "input.h"

using namespace std;
using namespace format;
using namespace input;

namespace client
{
    //*************************************************************
    // Client Data Functions.
    //*************************************************************
    // Client Members.
    struct Client
    {
        string accountNumber = "";
        string pinCode = "";
        string fullName = "";
        string phoneNumber = "";
        double balance = 0;
    };
    // Make Clients Data File Be In The Project Folder.
    const string fileName_CLIENTS = "C:\\Users\\aheda\\Documents\\Visual Studio Code\\C++\\Bank-System\\clients.txt";
    // Counvert Line That Has Client Data To Record.
    Client convertLineToRecord(string &line)
    {
        Client clientRecord;
        vector<string> vClientData = format::splitString(line, ",");
        clientRecord.accountNumber = vClientData[0];
        clientRecord.pinCode = vClientData[1];
        clientRecord.fullName = vClientData[2];
        clientRecord.phoneNumber = vClientData[3];
        clientRecord.balance = stod(vClientData[4]);
        return clientRecord;
    }
    // Load Client Data From File To Recoed.
    vector<Client> loadClientsDataFromFile()
    {
        vector<Client> vClients;
        fstream file;
        file.open(fileName_CLIENTS, ios::in);
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line != "")
                {
                    vClients.push_back(convertLineToRecord(line));
                }
            }
        }
        file.close();
        return vClients;
    }
    // Counvert Client Recorded Data To Line.
    string convertRecordToLine(Client clientRecord, string separator)
    {
        string clientDataInLine = "";
        clientDataInLine += clientRecord.accountNumber + separator;
        clientDataInLine += clientRecord.pinCode + separator;
        clientDataInLine += clientRecord.fullName + separator;
        clientDataInLine += clientRecord.phoneNumber + separator;
        clientDataInLine += to_string(clientRecord.balance);
        return clientDataInLine;
    }
    // Save Clients Data From Vector To File After Counvert Them To Lines.
    void saveClientDataFromVectorToFile(vector<Client> vClients)
    {
        fstream file;
        file.open(fileName_CLIENTS, ios::out);
        if (file.is_open())
        {
            for (Client &clientRecord : vClients)
            {
                file << convertRecordToLine(clientRecord, ",") << endl;
            }
        }
        file.close();
    }
    //*************************************************************
    // Client Functions.******************
    // Is Client Still Found In File.
    //*******************************************
    bool isStillFound(Client currentClient)
    {
        vector<Client> vClients = loadClientsDataFromFile();
        for (Client client : vClients)
        {
            if (currentClient.accountNumber == client.accountNumber && currentClient.pinCode == client.pinCode)
            {
                return true;
            }
        }
        return false;
    }
    //*************************************************************
}
