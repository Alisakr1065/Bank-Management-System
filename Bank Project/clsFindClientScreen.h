#pragma once
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsScreen.h"

class clsFindClientScreen : protected clsScreen
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
	static void FindClientScreen()
	{
		_DrawScreenHeader("Find Client Screen");
		string AccNum = clsInputValidate<string>::ReadString("Inter Account Number to Find: ");
		while (!clsBankClient::IsClientExist(AccNum))
		{
			AccNum = clsInputValidate<string>::ReadString("Account Number isn't Exist, Inter Another one: ");
		}
		clsBankClient Client = clsBankClient::Find(AccNum);
		_PrintClient(Client);
	}
};