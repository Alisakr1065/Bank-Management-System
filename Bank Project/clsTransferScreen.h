#pragma once
#include"clsBankClient.h"
#include"clsWithDrawScreen.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
	static float _ReadAmount(clsBankClient SenderClient)
	{
		float Amount = 0;
		cout << "Please inter Transfer Amount: ";
		cin >> Amount;

		while (Amount > SenderClient.Balance)
		{
			cout << "Amount Exceeds the Balance, you can Transfer up to: " << SenderClient.Balance << endl;
			cout << "Please inter another Amount: ";
			cin >> Amount;
		}
		return Amount;
	}
	static clsBankClient _ReadAndFindClient(bool TransferFrom = true)
	{
		string AccNum = "";
		if(TransferFrom)
		{
			AccNum = clsInputValidate<string>::ReadString("Inter Account Number to Transfer from: ");
		}
		else
		{
			AccNum = clsInputValidate<string>::ReadString("Inter Account Number to Transfer to: ");
		}
		while (!clsBankClient::IsClientExist(AccNum))
		{
			AccNum = clsInputValidate<string>::ReadString("Account Number isn't Exist, Inter Another one: ");
		}
		clsBankClient Client = clsBankClient::Find(AccNum);
		return Client;
	}
	static void _PrintClient(clsBankClient Client)
	{
		cout << "Client Card\n";
		cout << "-------------------------------------\n";
		cout << "FullName       : " << Client.FullName() << "\n";
		cout << "Account Number : " << Client.AccNum() << "\n";
		cout << "Balance        : " << Client.Balance << "\n";
		cout << "-------------------------------------\n";
	}
public:
	static void TransferScreen()
	{
		_DrawScreenHeader("Transfer Screen");

		clsBankClient SenderClient = _ReadAndFindClient();
		_PrintClient(SenderClient);

		clsBankClient AcceptorClient = _ReadAndFindClient(false);
		_PrintClient(AcceptorClient);
		
		float Amount = _ReadAmount(SenderClient);

		char Confirm = 'n';
		cout << "Are you Sure you want to perform this Transfer?[Y][N]:  ";
		cin >> Confirm;

		if (toupper(Confirm) == 'Y')
		{
			if(SenderClient.Transfer(AcceptorClient, Amount))
			{
				cout << "\nTransfer performed Successfully";
				cout << "\n" << SenderClient.FullName() << " Balance is: " << SenderClient.Balance;
				cout << "\n" << AcceptorClient.FullName() << " Balance is: " << AcceptorClient.Balance;
			}
			else
			{
				cout << "\nTransfer Was Failed";
			}
		}
		else
		{
			cout << "\n Process Was Cancelled";
		}
	}

};

