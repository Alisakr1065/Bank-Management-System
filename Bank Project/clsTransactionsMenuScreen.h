#pragma once
#include<iostream>
#include<iomanip>
#include"clsBankClient.h"
#include"clsDepositeScreen.h"
#include"clsBalancesScreen.h"
#include"clsWithDrawScreen.h"
#include"clsTransferScreen.h"
#include"clsTransferRegListScreen.h"


class clsTransactionsMenuScreen : protected clsScreen
{
private:
	enum enTransact
	{
		enDeposite = 1, enWithdraw = 2,
		enTotalBalances = 3,  enTransfer = 4,enTransferRegList = 5, enMainMenu = 6
	};

	static short _ReadTransactionsOptions()
	{
		cout << setw(37) << left << "" << "Choose What to do from [1] to [6]: ";
		short choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Choose Number between [1 : 6]: ");
		return choice;
	}

	static void _ShowClientsBalncesList()
	{
		clsBalancesScreen::ClientsBalncesList();
	}

	static void _WithdrawScreen()
	{
		clsWithDrawScreen::ShowWithDrawScreen();
	}

	static void _DepositeScreen()
	{
		clsDepositeScreen::ShowDepositeScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::TransferScreen();
	}

	static void _ShowTransferRegisterListScreen()
	{
		clsTransferRegListScreen::ShowLogRegList();
	}

	static void _GoBackToTransactionMenu()
	{
		cout << "\n\nPress any key to go back to Transaction Menu...";
		system("pause>0");
		ShowTransactionsScreen();
	}
	static void _ExecuteTransactChoice(enTransact Choice)
	{
		switch (Choice)
		{
		case enDeposite:
			system("CLS");
			_DepositeScreen();
			_GoBackToTransactionMenu();
			break;

		case enWithdraw:
			system("CLS");
			_WithdrawScreen();
			_GoBackToTransactionMenu();
			break;

		case enTotalBalances:
			system("CLS");
			_ShowClientsBalncesList();
			_GoBackToTransactionMenu();
			break;

		case enTransfer:
			system("CLS");
			_ShowTransferScreen();
			_GoBackToTransactionMenu();
			break;

		case enTransferRegList:
			system("CLS");
			_ShowTransferRegisterListScreen();
			_GoBackToTransactionMenu();
			break;

		case enMainMenu:
			break;
		}
	}

public:

	static void ShowTransactionsScreen()
	{
		short Transact = 0;
		system("CLS");

		_DrawScreenHeader("\tTransactions Screen");
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "          Transactions Menu Screen\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t [1] Deposite\n";
		cout << setw(37) << left << "" << "\t [2] Withdraw\n";
		cout << setw(37) << left << "" << "\t [3] Total Balances\n";
		cout << setw(37) << left << "" << "\t [4] Transfer\n";
		cout << setw(37) << left << "" << "\t [5] Transfer Register List\n";
		cout << setw(37) << left << "" << "\t [6] Back To Main Menu\n";
		cout << setw(37) << left << "" << "==============================================\n";
		_ExecuteTransactChoice(enTransact(_ReadTransactionsOptions()));
	}

};