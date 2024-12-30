#pragma once
#include<iomanip>
#include"clsPerson.h"
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;


class clsUpdateClientScreen : protected clsScreen
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
	static void Update()
	{
		_DrawScreenHeader("\tUpdate Client Screen");
		string AccNum = clsInputValidate<string>::ReadString("Inter Account Number: ");
		while (!clsBankClient::IsClientExist(AccNum))
		{
			AccNum = clsInputValidate<string>::ReadString("Account Number Not Found, Inter Another one: ");
		}
		clsBankClient Client = clsBankClient::Find(AccNum);
		_PrintClient(Client);

		cout << "\n\nUpdating Client\n";
		_ReadClientInfo(Client);

		clsBankClient::enSave SaveResult;
		SaveResult = Client.Save();

		switch (SaveResult)
		{
		case clsBankClient::svFailedEmptyObject:
			cout << "\nSave Faild due to Empty object";
			break;
		case clsBankClient::svSucceeded:
			cout << "\nSaved Successfully";
			_PrintClient(Client);

			break;
		}
	}
};