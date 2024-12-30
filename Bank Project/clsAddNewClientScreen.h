#pragma once
#include<iostream>
#include<iomanip>
#include"clsPerson.h"
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

using namespace std;
class clsAddNewClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "-------------------------------------\n";
		cout << "Inter FirstName: ";
		Client.FirstName = clsInputValidate<string>::ReadString();
		cout << "\nInter LastName: ";
		Client.LastName = clsInputValidate<string>::ReadString();
		cout << "\nInter Email: ";
		Client.Email = clsInputValidate<string>::ReadString();
		cout << "\nInter Phone: ";
		Client.Phone = clsInputValidate<string>::ReadString();
		cout << "\nInter PinCode: ";
		Client.PinCode = clsInputValidate<string>::ReadString();
		cout << "\nInter Balance: ";
		Client.Balance = clsInputValidate<double>::ReadT();
		cout << "-------------------------------------\n";

	}

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
	static void AddNewClient()
	{
		_DrawScreenHeader("\tAdd New Client Screen");
		
		string AccNum = clsInputValidate<string>::ReadString("\nInter Account Number: ");
		while (clsBankClient::IsClientExist(AccNum))
		{
			AccNum = clsInputValidate<string>::ReadString("Account Number is Already Exist, Inter Another one: ");
		}
		clsBankClient Client = clsBankClient::GetNewClientObject(AccNum);

		cout << "\n\nAdding New Client\n";
		_ReadClientInfo(Client);

		clsBankClient::enSave SaveResult;
		SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::svSucceeded:
			cout << "\nSaved Successfully";
			_PrintClient(Client);
			break;

		case clsBankClient::svFailedEmptyObject:
			cout << "\nSave Faild due to Empty object";
			break;

		case clsBankClient::svFailedExistObject:
			cout << "\nSave Faild due to Exist object";
			break;

		}
	}
};

