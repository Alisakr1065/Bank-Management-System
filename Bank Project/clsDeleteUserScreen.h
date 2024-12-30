#pragma once
#include"clsUser.h"
#include"clsScreen.h"
#include"clsInputValidate.h"


class clsDeleteUser : protected clsScreen
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
	static void DeleteUser()
	{
		_DrawScreenHeader("\tDelete User Screen");
		string UserName = clsInputValidate<string>::ReadString("Inter UserName to Delete: ");
		while (!clsUser::IsUserExist(UserName))
		{
			UserName = clsInputValidate<string>::ReadString("UserName isn't Exist, Inter Another one: ");
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char ConfirmDelete = 'N';
		cout << "Are you Sure you want to delete this Account?[Y][N]:  ";
		cin >> ConfirmDelete;

		if (toupper(ConfirmDelete) == 'Y')
		{
			if (User.Delete())
			{
				cout << "User Deleted Successfully\n";
				_PrintUser(User);
			}
			else
			{
				cout << "Failed to Delete the Account\n";
			}
		}
	}
};