#pragma once
#include<iomanip>
#include"clsPerson.h"
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient NewClient)
	{
		cout << "Client Card\n";
		cout << "-------------------------------------\n";
		cout << "FirstName      : " << NewClient.FirstName << "\n";
		cout << "LastName       : " << NewClient.LastName << "\n";
		cout << "FullName       : " << NewClient.FullName() << "\n";
		cout << "Email          : " << NewClient.Email << "\n";
		cout << "Phone          : " << NewClient.Phone << "\n";
		cout << "Account Number : " << NewClient.AccNum() << "\n";
		cout << "Pin Code       : " << NewClient.PinCode << "\n";
		cout << "Balance        : " << NewClient.Balance << "\n";
		cout << "-------------------------------------\n";

	}

public:
	static void DeleteClient()
	{
		_DrawScreenHeader("\tDelete Client Screen");
		string AccNum = clsInputValidate<string>::ReadString("Inter Account Number to Delete: ");
		while (!clsBankClient::IsClientExist(AccNum))
		{
			AccNum = clsInputValidate<string>::ReadString("Account Number isn't Exist, Inter Another one: ");
		}
		clsBankClient Client = clsBankClient::Find(AccNum);
		_PrintClient(Client);

		char ConfirmDelete = 'N';
		cout << "Are you Sure you want to delete this Account?[Y][N]:  ";
		cin >> ConfirmDelete;

		if (toupper(ConfirmDelete) == 'Y')
		{
			if (Client.Delete())
			{
				cout << "Account Deleted Successfully\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "Failed to Delete the Account\n";
			}
		}
	}
};