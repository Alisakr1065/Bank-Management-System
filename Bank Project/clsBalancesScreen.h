#pragma once
#include"clsScreen.h"
#include"clsUtil.h"
#include"clsBankClient.h"

class clsBalancesScreen : protected clsScreen
{
private:

	static double _DisplayClientBalance(clsBankClient Client)
	{
		cout << setw(16) << left << "" << "|" << left << setw(29) << Client.AccNum();
		cout << "|" << left << setw(30) << Client.FirstName;
		cout << "|" << left << setw(16) << Client.Balance;
		cout << endl;
		return Client.Balance;
	}

public:
	static void ClientsBalncesList()
	{
		vector<clsBankClient>vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;

		string SubTitle = "\t\t(" + to_string(vClients.size()) + ")Client/s";
		_DrawScreenHeader("\tBalances List", SubTitle);
		cout << "\t\t----------------------------------------------------------------------------------------\n";
		cout << setw(16) << left << "" << "|" << left << setw(13) << "Acount Number";
		cout << setw(16) << left << "" << "|" << left << setw(30) << "Client Name";
		cout << setw(0) << left << "" << "|" << left << setw(10) << "Balance";
		cout << "\n\t\t----------------------------------------------------------------------------------------\n";

		for (clsBankClient& Data : vClients)
		{
			TotalBalances += _DisplayClientBalance(Data);
		}
		cout << "\t\t----------------------------------------------------------------------------------------\n";
		cout << "\t\t\tTotalBalances: " << TotalBalances << endl;
		cout << "\t\t\t( " << clsUtil::NumToText((int)TotalBalances) << " )";
	}
};

