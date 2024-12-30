#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsUser.h"
using namespace std;

class clsUsersListScreen : protected clsScreen
{
	static void _DisplayUser(clsUser User)
	{
		cout << setw(10) << left << "" << "|" << left << setw(13) << User.UserName;
		cout << "|" << left << setw(16) << User.FullName();
		cout << "|" << left << setw(15) << User.Phone;
		cout << "|" << left << setw(25) << User.Email;
		cout << "|" << left << setw(13) << User.Password;
		cout << "|" << left << setw(5) << User.Permissions;
		cout << endl;

	}

public:

	static void ShowUsersList()
	{
		system("cls");
		
		vector<clsUser>vUsers = clsUser::GetUsersList();

		string SubTitle = "\t   (" + to_string(vUsers.size()) + ") User(s)";
		string Title = "\tUser List Screen";
		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t-----------------------------------------------------------------------------------------------------\n";
		cout << setw(10) << left << "" << "|" << left << setw(13) << "User Name";
		cout << "|" << left << setw(16) << "Full Name";
		cout << "|" << left << setw(15) << "Phone";
		cout << "|" << left << setw(25) << "Email";
		cout << "|" << left << setw(13) << "Password";
		cout << "|" << left << setw(5) << "Permissions";
		cout << "\n\t-----------------------------------------------------------------------------------------------------\n";

		if (vUsers.size() == 0)
			cout << "\n No Users Available on the system";

		else
		{
			for (clsUser& Data : vUsers)
			{
				_DisplayUser(Data);
			}
		}
		cout << "\t-----------------------------------------------------------------------------------------------------\n";
	}
};