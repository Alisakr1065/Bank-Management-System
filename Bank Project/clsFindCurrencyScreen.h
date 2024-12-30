#pragma once
#include"clsCurrency.h"
#include"clsInputValidate.h"
#include"clsScreen.h"

class clsFindCurrencyScreen : protected clsScreen
{
	enum enFindBy {Code = 1, Country = 2};
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "Currency Card\n";
		cout << "-------------------------------------\n";
		cout << "Country : " << Currency.Country() << "\n";
		cout << "Code    : " << Currency.Code() << "\n";
		cout << "Name    : " << Currency.Name() << "\n";
		cout << "Rate(1$): " << Currency.Rate() << "\n";
		cout << "-------------------------------------\n";

	}
	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("Find Currency Screen");
		cout << "Find by Code [1] or Country [2]: ";
		enFindBy Choose = enFindBy(clsInputValidate<short>::ReadNumberBetween(1, 2, "Choose between 1 & 2: "));
		string Choice = "";
		clsCurrency Currency = clsCurrency::_GetEmptyClientObject();

		if (Choose == clsFindCurrencyScreen::Code)
		{
			Choice = clsInputValidate<string>::ReadString("Inter Code: ");
			Currency = clsCurrency::FindByCode(Choice);
			_ShowResults(Currency);
		}

		else if (Choose == clsFindCurrencyScreen::Country)
		{
			Choice = clsInputValidate<string>::ReadString("Inter Country Name: ");
			Currency = clsCurrency::FindByCountry(Choice);
			_ShowResults(Currency);
		}

	}
};