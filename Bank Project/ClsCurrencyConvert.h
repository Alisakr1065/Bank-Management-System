#pragma once
#include<iostream>
#include"clsCurrency.h"
#include"clsInputValidate.h"
#include"clsScreen.h"
#include<string>

class ClsCurrencyConvert : protected clsScreen
{
	static clsCurrency _GetCurrency(string Massage)
	{
		string Code = clsInputValidate<string>::ReadString(Massage);
		while (!clsCurrency::IsCurrencyExistByCode(Code))
		{
			Code = clsInputValidate<string>::ReadString("Code isn't Exist, Inter Another one: ");
		}
		return clsCurrency::FindByCode(Code);
	}

	static float _ReadAmount()
	{
		cout << "Inter an Amount to Exchange: ";
		float Amount = clsInputValidate<double>::ReadT();
		return Amount;
	}

	static void _PrintCurrency(clsCurrency Currency, string Title = "Currency Card")
	{
		cout << "\n\n" << Title;
		cout << "\n-------------------------------------\n";
		cout << "Country : " << Currency.Country() << "\n";
		cout << "Code    : " << Currency.Code() << "\n";
		cout << "Name    : " << Currency.Name() << "\n";
		cout << "Rate(1$): " << Currency.Rate() << "\n";
		cout << "-------------------------------------\n";

	}

	static void _PrintConversionResult(clsCurrency Currency1, clsCurrency Currency2, float Amount)
	{

		_PrintCurrency(Currency1, "Convert From");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);
		cout << endl << Amount << " " << Currency1.Code() << " = " << AmountInUSD << " " << Currency2.Code();

		if (Currency2.Code() != "USD")
		{
			cout << "\n\n Convert From USD to: \n";
			_PrintCurrency(Currency2,"Convert From USD to:" );

			float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Currency2, Amount);
			cout << endl << Amount << " " << Currency1.Code() << " = " << AmountInCurrency2 << " " << Currency2.Code();
		}
	}
public:
	
	static void ShowCurrencyConvertScreen()
	{
		char Confirm;
		do
		{
			system("cls");
			_DrawScreenHeader("Convert Currencies Screen");

			clsCurrency Currency1 = _GetCurrency("Inter Currency 1 Code: ");
			clsCurrency Currency2 = _GetCurrency("Inter Currency 2 Code: ");
			float Amount = _ReadAmount();

			_PrintConversionResult(Currency1, Currency2, Amount);

			cout << "\nDo you want to update the rate of this currency [Y],[N]: ";
			Confirm = clsInputValidate<char>::ReadT();

		} while (toupper(Confirm) == 'Y');
	}

};