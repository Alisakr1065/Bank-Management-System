#pragma once
#include<iostream>
#include<iomanip>
#include"clsCurrency.h"
#include"clsCurrenciesListScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateRateScreen.h"
#include"ClsCurrencyConvert.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
	enum enTransact
	{
		enCurrenciesList = 1, enFind = 2,
		enUpdateRate = 3, enCurrencyCalc = 4, enMainMenu = 5
	};

	static short _ReadTransactionsOptions()
	{
		cout << setw(37) << left << "" << "Choose What to do from [1] to [5]: ";
		short choice = clsInputValidate<short>::ReadNumberBetween(1, 5, "Choose Number between [1 : 5]: ");
		return choice;
	}

	static void _ShowCurrenciesList()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	static void _ShowFindScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen()
	{
		clsUpdateRateScreen::UpdateRateScreen();
	}
	static void _ShowCurrencyConvertScreen()
	{
		ClsCurrencyConvert::ShowCurrencyConvertScreen();
	}
	static void _GoBackToCurrencyExchangeMenu()
	{
		cout << "\n\nPress any key to go back to Currency Exchange Menu...";
		system("pause>0");
		ShowCurrencyExchangeScreen();
	}
	
	static void _ExecuteTransactChoice(enTransact Choice)
	{

		switch (Choice)
		{
		case enCurrenciesList:
			system("CLS");
			_ShowCurrenciesList();
			_GoBackToCurrencyExchangeMenu();
			break;

		case enFind:
			system("CLS");
			_ShowFindScreen();
			_GoBackToCurrencyExchangeMenu();
			break;

		case enUpdateRate:
			system("CLS");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMenu();
			break;

		case enCurrencyCalc:
			system("CLS");
			_ShowCurrencyConvertScreen();
			_GoBackToCurrencyExchangeMenu();
			break;

		case enMainMenu:
			break;
		}
	}
public:

	static void ShowCurrencyExchangeScreen()
	{
		short Transact = 0;
		system("CLS");

		_DrawScreenHeader("\Currency Exchange Screen");
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "          Currency Exchange Menu Screen\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t [1] Currencies List\n";
		cout << setw(37) << left << "" << "\t [2] Find Currency\n";
		cout << setw(37) << left << "" << "\t [3] Update Rate\n";
		cout << setw(37) << left << "" << "\t [4] Convert Currency\n";
		cout << setw(37) << left << "" << "\t [5] Back To Main Menu\n";
		cout << setw(37) << left << "" << "==============================================\n";
		_ExecuteTransactChoice(enTransact(_ReadTransactionsOptions()));
	}
};