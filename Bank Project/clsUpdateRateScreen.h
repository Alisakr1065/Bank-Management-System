#pragma once
#include<iostream>
#include<iomanip>
#include"clsCurrency.h"
#include"clsCurrenciesListScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsUpdateRateScreen : protected clsScreen
{
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\n\nCurrency Card\n";
		cout << "-------------------------------------\n";
		cout << "Country : " << Currency.Country() << "\n";
		cout << "Code    : " << Currency.Code() << "\n";
		cout << "Name    : " << Currency.Name() << "\n";
		cout << "Rate    : " << Currency.Rate() << "\n";
		cout << "-------------------------------------\n";

	}

public:

	static void UpdateRateScreen()
	{
		_DrawScreenHeader("Update Rate Screen");

		string Choice = clsInputValidate<string>::ReadString("Inter Currency Code: ");
		while (!clsCurrency::IsCurrencyExistByCode(Choice))
		{
			Choice = clsInputValidate<string>::ReadString("Code isn't Exist, Inter Another one: ");
		}
		clsCurrency Currency = clsCurrency::FindByCode(Choice);
		
		_PrintCurrency(Currency);

		cout << "Are you sure you want to update the rate of this Currency [Y],[N]: ";
		char Confirm = clsInputValidate<char>::ReadT();
		if(toupper(Confirm) == 'Y')
		{
			cout << "Inter The New Rate: ";
			float NewRate = clsInputValidate<float>::ReadT();
			Currency.UpdateRate(NewRate);
			cout << "Rate Updated successfully.\n";
		}
		cout << "Process Cancelled.\n";
	}
};

