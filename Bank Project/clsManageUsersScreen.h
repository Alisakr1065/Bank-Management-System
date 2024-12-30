#pragma once
#include<iostream>
#include<iomanip>
#include"clsBankClient.h"
#include"clsUser.h"
#include"clsScreen.h"
#include"clsUsersListScreen.h"
#include"clsAddNewUserScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"
#include"clsInputValidate.h"

class clsManageUsersScreen : protected clsScreen
{
private:

	enum enManageAllUsers
	{
		enListUsers = 1, enAddNewUser = 2,
		enDeleteUser = 3, enUpdateUser = 4,
		enFindUser = 5, enToMainMenu = 6
	};

	enum enMainMenuPermissions
	{
		AllAccess = -1, ShowClientsPermission = 1, AddClientPermission = 2, DeleteClientPermission = 4, UpdateClientPermission = 8,
		FindClientPermission = 16, TransactionsPermission = 32, ManageUsersPermission = 64,
	};

	static short _ReadManageUsersOptions()
	{
		cout << setw(37) << left << "" << "Choose What to do from [1] to [6]: ";
		short choice = clsInputValidate<short>::ReadNumberBetween(1, 6, "Choose Number between [1 : 6]: ");
		return choice;
	}
	
	static void _GoBackToManageUsersMenu()
	{

		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");
		ShowManageUsersMenuScreen();
	}

	static void _ShowUsersList()
	{
		clsUsersListScreen::ShowUsersList();
	}
	
	static void _AddNewUser()
	{
		clsAddNewUser::AddNewUser();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUser::DeleteUser();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::Update();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::FindClientScreen();
	}

	static void ExecuteManageUsersChoice(enManageAllUsers Choice)
	{
		switch (Choice)
		{
		case enListUsers:
			system("CLS");
			_ShowUsersList();
			_GoBackToManageUsersMenu();
			break;

		case enAddNewUser:
			system("CLS");
			_AddNewUser();
			_GoBackToManageUsersMenu();
			break;

		case enDeleteUser:
			system("CLS");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case enUpdateUser:
			system("CLS");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case enFindUser:
			system("CLS");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;

		case enToMainMenu:
			break;
		}
	}

public:
	static void ShowManageUsersMenuScreen()
	{
		system("CLS");
		_DrawScreenHeader("\tManage Users Screen");
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "          Manage Users Menu Screen\n";
		cout << setw(37) << left << "" << "==============================================\n";
		cout << setw(37) << left << "" << "\t [1] List Users\n";
		cout << setw(37) << left << "" << "\t [2] Add New User\n";
		cout << setw(37) << left << "" << "\t [3] Delete User \n";
		cout << setw(37) << left << "" << "\t [4] Update User \n";
		cout << setw(37) << left << "" << "\t [5] Find User \n";
		cout << setw(37) << left << "" << "\t [6] Back To Main Menu\n";
		cout << setw(37) << left << "" << "==============================================\n";

		ExecuteManageUsersChoice(enManageAllUsers(_ReadManageUsersOptions()));
	}

};