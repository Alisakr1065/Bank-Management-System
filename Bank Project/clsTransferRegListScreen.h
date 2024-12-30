#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"

class clsTransferRegListScreen : protected clsScreen
{
	static void _DisplayReg(clsBankClient::stTransferRegister Trans)
	{
		cout << setw(9) << left << "" << "|" << left << setw(25) << Trans.DateAndTime;
		cout << "|" << left << setw(12) << Trans.SenderAccNum;
		cout << "|" << left << setw(12) << Trans.AcceptorAccNum;
		cout << "|" << left << setw(9) << Trans.Amount;
		cout << "|" << left << setw(12) << Trans.SenderBalance;
		cout << "|" << left << setw(12) << Trans.AcceptorBalance;
		cout << "|" << left << setw(5) << Trans.SenderUserName;
		cout << endl;

	}

public:

	static void ShowLogRegList()
	{
		system("cls");

		vector<clsBankClient::stTransferRegister>vRecords = clsBankClient::GetTransferRegList();

		string Title = "\Transfer Register List Screen";
		string SubTitle = "\t   (" + to_string(vRecords.size()) + ") records(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t-----------------------------------------------------------------------------------------------------\n";
		cout << setw(9) << left << "" << "|" << left << setw(25) << "Date - Time";
		cout << "|" << left << setw(12) << "S.AccNum";
		cout << "|" << left << setw(12) << "A.AccNum";
		cout << "|" << left << setw(9) << "Amount";
		cout << "|" << left << setw(12) << "S.Balance";
		cout << "|" << left << setw(12) << "A.Balance";
		cout << "|" << left << setw(5) << "S.UserName";
		cout << "\n\t-----------------------------------------------------------------------------------------------------\n";

		if (vRecords.size() == 0)
			cout << "\n No Users Available on the system";

		else
		{
			for (clsBankClient::stTransferRegister& Data : vRecords)
			{
				_DisplayReg(Data);
			}
		}
		cout << "\t-----------------------------------------------------------------------------------------------------\n";
	}
	
};