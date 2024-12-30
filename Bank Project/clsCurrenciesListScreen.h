#pragma once
#include"clsScreen.h"
#include"clsUtil.h"
#include"clsCurrency.h"

class clsCurrenciesListScreen : protected clsScreen
{
	static void _DisplayCurrency(clsCurrency Currency)
	{
		cout << setw(16) << left << "" << "|" << left << setw(30) << Currency.Country();
		cout << "|" << left << setw(10) << Currency.Code();
		cout << "|" << left << setw(40) << Currency.Name();
		cout << "|" << left << setw(10) << Currency.Rate();
		cout << endl;
	}

public:
	static void ShowCurrenciesListScreen()
	{
		vector<clsCurrency>vCurrencies = clsCurrency::GetCurrenciesList();

		string SubTitle = "\t\t(" + to_string(vCurrencies.size()) + ")Currency/s";

		_DrawScreenHeader("\tCurrencies List", SubTitle);
		cout << "\t\t---------------------------------------------------------------------------------------------\n";
		cout << setw(16) << left << "" << "|" << left << setw(30) << "Country ";
		cout << "|" << left << setw(10) << "Code";
		cout << "|" << left << setw(40) << "Name";
		cout << "|" << left << setw(10) << "Rate(1$)";
		cout << "\n\t\t---------------------------------------------------------------------------------------------\n";

		for (clsCurrency& Data : vCurrencies)
		{
			_DisplayCurrency(Data);
		}
		cout << "\t\t---------------------------------------------------------------------------------------------\n";
	}
};