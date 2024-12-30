#pragma once
#include"clsUser.h"
#include"clsInputValidate.h"
#include"clsScreen.h"

class clsAddNewUser: protected clsScreen
{
private:
	enum enMainMenuPermissions
	{
		AllAccess = -1, ShowClientsPermission = 1, AddClientPermission = 2, DeleteClientPermission = 4, UpdateClientPermission = 8,
		FindClientPermission = 16, TransactionsPermission = 32, ManageUsersPermission = 64, LoginRegister = 128
	};

	static short _ReadUserPermissions()
	{
		char choice = 'n';
		short Permissions = 0;

		cout << "Have All Access? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			return enMainMenuPermissions::AllAccess;
		}

		cout << "Have Access To Show Clients List? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::ShowClientsPermission;
		}

		cout << "Have Access To Add Client? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::AddClientPermission;
		}

		cout << "Have Access To Delete Client? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::DeleteClientPermission;
		}

		cout << "Have Access To Update Client? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::UpdateClientPermission;
		}

		cout << "Have Access To Find Client? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::FindClientPermission;
		}

		cout << "Have Access To Transactions? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::TransactionsPermission;
		}

		cout << "Have Access To  Manage Users? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::ManageUsersPermission;
		}

		cout << "Have Access To Show Login Register List? [Y]/[N]: ";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{
			Permissions |= enMainMenuPermissions::LoginRegister;
		}

		return Permissions;
	}
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "-------------------------------------\n";
		cout << "Inter FirstName: ";
		User.FirstName = clsInputValidate<string>::ReadString();
		cout << "\nInter LastName: ";
		User.LastName = clsInputValidate<string>::ReadString();
		cout << "\nInter Email: ";
		User.Email = clsInputValidate<string>::ReadString();
		cout << "\nInter Phone: ";
		User.Phone = clsInputValidate<string>::ReadString();
		cout << "\nInter Password: ";
		User.Password = clsInputValidate<string>::ReadString();
		cout << "\nRead Permissions\n ";
		User.Permissions = _ReadUserPermissions();
		cout << "-------------------------------------\n";
	}

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
	static void AddNewUser()
	{
		_DrawScreenHeader("\tAdd New User Screen");

		string UserName = clsInputValidate<string>::ReadString("\nInter UserName: ");
		while (clsUser::IsUserExist(UserName))
		{
			UserName = clsInputValidate<string>::ReadString("UserName is Already Exist, Inter Another one: ");
		}
		clsUser User = clsUser::GetNewUserObject(UserName);

		cout << "\n\nAdding New User\n";
		_ReadUserInfo(User);

		clsUser::enSave SaveResult;
		SaveResult = User.Save();

		switch (SaveResult)
		{
		case clsUser::svSucceeded:
			cout << "\nSaved Successfully";
			_PrintUser(User);
			break;

		case clsUser::svFailedEmptyObject:
			cout << "\nSave Faild due to Empty object";
			break;

		case clsUser::svFailedExistObject:
			cout << "\nSave Faild due to Exist object";
			break;

		}
	}
};
