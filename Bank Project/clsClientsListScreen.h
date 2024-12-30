#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"
using namespace std;

class clsClientsListScreen : protected clsScreen
{
	static void _DisplayClient(clsBankClient Client)
	{
		cout << setw(16) << left << "" << "|" << left << setw(16) << Client.AccNum();
		cout << "|" << left << setw(20) << Client.FullName();
		cout << "|" << left << setw(15) << Client.Phone;
		cout << "|" << left << setw(20) << Client.Email;
		cout << "|" << left << setw(9) << Client.PinCode;
		cout << "|" << left << setw(16) << Client.Balance;
		cout << endl;
	}
	
public:
	static void ShowClientsList()
	{
		vector<clsBankClient>vClients = clsBankClient::GetClientsList();
		
		string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client(s)";
		string Title = "\tClient List Screen";
		_DrawScreenHeader(Title, SubTitle);
		cout<< "\n\t\t----------------------------------------------------------------------------------------------\n";
		cout << setw(16) << left << "" << "|" << left << setw(16) << "Acount Number";
		cout << "|" << left << setw(20) << "Client Name";
		cout << "|" << left << setw(15) << "Phone";
		cout << "|" << left << setw(20) << "Email";
		cout << "|" << left << setw(9) << "Pin Code";
		cout << "|" << left << setw(16) << "Balance";
		cout << "\n\t\t----------------------------------------------------------------------------------------------\n";

		for (clsBankClient& Data : vClients)
		{
			_DisplayClient(Data);
		}
		//cout << setw(8) << left << "";
		cout << "\t\t----------------------------------------------------------------------------------------------\n";

	}
};