#pragma once
#include<iostream>
#include"Global.h"
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsClientsListScreen.h"
#include"clsAddNewClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransactionsMenuScreen.h"
#include"clsManageUsersScreen.h"
#include"clsLoginRegisterScreen.h"
#include"clsCurrencyExchangeScreen.h"
#include"clsInputValidate.h"

using namespace std;

class clsMainMenuScreen : protected clsScreen
{
private:
	enum enChoice {
		enShowClientsList = 1, enAddNewClients = 2,
		enDeleteClient = 3, enUpdateClient = 4,
		enFindClient = 5, enTransactions = 6, 
		enManageUsers = 7, enLogReg = 8, 
		enCurrencyExhange = 9 ,enLogout = 10
	};

	static void _GoBackToMainMenue()
	{
		cout << "\n\nPress any key to go back to Main Menue...";
		system("pause>0");
		ShowMainMenuScreen();
	}
	
	static short _ReadMainMenuOptions()
	{
		cout << setw(37) << left  << "" << "Choose What to do from [1] to [10]: ";
		short choice = clsInputValidate<short>::ReadNumberBetween(1, 10, "Choose Number between [1 : 10]: ");
		return choice;
	}

	static void _ShowClientsList()
	{
		if (!_CheckAccessRights(clsUser::ShowClientsPermission))
			return;
		
		clsClientsListScreen::ShowClientsList();
	}
	static void _AddNewClients()
	{
		if (!_CheckAccessRights(clsUser::AddClientPermission))
			return;
		
		clsAddNewClientScreen::AddNewClient();
	}
	static void _DeleteAcount()
	{
		if (!_CheckAccessRights(clsUser::DeleteClientPermission))
			return;
		
		clsDeleteClientScreen::DeleteClient();
	}
	static void _UpdateAcount()
	{
		if (!_CheckAccessRights(clsUser::UpdateClientPermission))
		{
			return;
		}
		clsUpdateClientScreen::Update();
	}
	static void _FindClient()
	{
		if (!_CheckAccessRights(clsUser::FindClientPermission))
			return;
		
		clsFindClientScreen::FindClientScreen();
	}
	static void _ShowTransactionsScreen()
	{
		if (!_CheckAccessRights(clsUser::TransactionsPermission))
			return;

		clsTransactionsMenuScreen::ShowTransactionsScreen();
	}
	static void _ShowManageUsersMenuScreen()
	{
		if (!_CheckAccessRights(clsUser::ManageUsersPermission))
			return;
		
		clsManageUsersScreen::ShowManageUsersMenuScreen();
	}
	static void _ShowLogRegScreen()
	{
		if (!_CheckAccessRights(clsUser::LoginRegister))
			return;

		clsLoginRegisterScreen::ShowLogRegList();
	}
	static void _ShowCurrencyExchangeScreen()
	{
		if (!_CheckAccessRights(clsUser::CurrencyExchangePermission))
			return;
		
		clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
	}
	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _ExecuteChoice(enChoice Choice)
	{
		switch (Choice)
		{
		case enChoice::enShowClientsList:
			system("CLS");
			_ShowClientsList();
			_GoBackToMainMenue();
			break;

		case enChoice::enAddNewClients:
			system("CLS");
			_AddNewClients();
			_GoBackToMainMenue();
			break;

		case enChoice::enDeleteClient:
			system("CLS");
			_DeleteAcount();
			_GoBackToMainMenue();
			break;

		case enChoice::enUpdateClient:
			system("CLS");
			_UpdateAcount();
			_GoBackToMainMenue();
			break;
		case enChoice::enFindClient:
			system("CLS");
			_FindClient();
			_GoBackToMainMenue();
			break;

		case enTransactions:
			system("CLS");
			_ShowTransactionsScreen();
			_GoBackToMainMenue();
			break;

		case enManageUsers:
			system("CLS");
			_ShowManageUsersMenuScreen();
			_GoBackToMainMenue();
			break;

		case enLogReg:
			system("CLS");
			_ShowLogRegScreen();
			_GoBackToMainMenue();
			break;

		case enCurrencyExhange:
			system("CLS");
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenue();
			break;

		case enChoice::enLogout:
			_Logout();
			break;
		}
	}

public:
	static void ShowMainMenuScreen()
	{
		short Choice = 0;
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "                Main Menu Screen\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t [1] Show Clients List\n";
		cout << setw(37) << left << "" << "\t [2] Add Client\n";
		cout << setw(37) << left << "" << "\t [3] Delete Client\n";
		cout << setw(37) << left << "" << "\t [4] Update Client\n";
		cout << setw(37) << left << "" << "\t [5] Find Client\n";
		cout << setw(37) << left << "" << "\t [6] Transactions\n";
		cout << setw(37) << left << "" << "\t [7] Manage Users\n";
		cout << setw(37) << left << "" << "\t [8] Login Register\n";
		cout << setw(37) << left << "" << "\t [9] Currency Exchange\n";
		cout << setw(37) << left << "" << "\t [10] Logout\n";
		cout << setw(37) << left << "" << "==============================================\n";

		_ExecuteChoice(enChoice(_ReadMainMenuOptions()));
	}
};