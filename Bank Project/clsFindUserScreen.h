#pragma once
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser NewUser)
	{
		cout << "User Card\n";
		cout << "-------------------------------------\n";
		cout << "FirstName      : " << NewUser.FirstName << "\n";
		cout << "LastName       : " << NewUser.LastName << "\n";
		cout << "FullName       : " << NewUser.FullName() << "\n";
		cout << "Email          : " << NewUser.Email << "\n";
		cout << "Phone          : " << NewUser.Phone << "\n";
		cout << "UserName       : " << NewUser.UserName << "\n";
		cout << "Password       : " << NewUser.Password << "\n";
		cout << "Permissions    : " << NewUser.Permissions << "\n";
		cout << "-------------------------------------\n";

	}

public:

	static void FindClientScreen()
	{
		_DrawScreenHeader("Find User Screen");
		string UserName = clsInputValidate<string>::ReadString("Inter UserName to Find: ");
		while (!clsUser::IsUserExist(UserName))
		{
			UserName = clsInputValidate<string>::ReadString("UserName isn't Exist, Inter Another one: ");
		}
		clsUser Client = clsUser::Find(UserName);
		_PrintUser(Client);
	}
};