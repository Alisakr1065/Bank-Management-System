#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsUser.h"

class clsLoginRegisterScreen : clsScreen
{
	static void _DisplayUser(clsUser::stLoginRegister User)
	{
		cout << setw(10) << left << "" << "|" << left << setw(35) << User.DateAndTime;
		cout << "|" << left << setw(16) << User.UserName;
		cout << "|" << left << setw(13) << User.Password;
		cout << "|" << left << setw(5) << User.Permissions;
		cout << endl;

	}

public:

	static void ShowLogRegList()
	{
		system("cls");

		vector<clsUser::stLoginRegister>vRecords = clsUser::GetLogRegList();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t   (" + to_string(vRecords.size()) + ") records(s)";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t-----------------------------------------------------------------------------------------------------\n";
		cout << setw(10) << left << "" << "|" << left << setw(35) << "Date - Time";
		cout << "|" << left << setw(16) << "UserName";;
		cout << "|" << left << setw(13) << "Password";
		cout << "|" << left << setw(5) << "Permissions";
		cout << "\n\t-----------------------------------------------------------------------------------------------------\n";

		if (vRecords.size() == 0)
			cout << "\n No Users Available on the system";

		else
		{
			for (clsUser::stLoginRegister& Data : vRecords)
			{
				_DisplayUser(Data);
			}
		}
		cout << "\t-----------------------------------------------------------------------------------------------------\n";
	}
};