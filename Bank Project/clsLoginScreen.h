#pragma once
#include"clsUser.h"
#include"clsInputValidate.h"
#include"clsMainMenuScreen.h"
#include"clsScreen.h"
#include"Global.h"

class clsLoginScreen : protected clsScreen
{
private:
	static void _Login()
	{
		string Name, Password;
		bool loginfailed = false;
		short Trials = 3;
		do
		{
			system("cls");
			_DrawScreenHeader("\t\tLogin Screeen");

			if (loginfailed)
			{ 
				--Trials;

				if (Trials == 0)
				{
					Blocked = true;
					cout << "You are locked After 3 Trials\n";
					return;
				}
				
				cout << "Invalid UserName or Password\n";
				cout << "You have " << Trials << " left\n";

			}

			Name = clsInputValidate<string>::ReadString("Inter UserName: ");
			Password = clsInputValidate<string>::ReadString("Inter Password: ");

			CurrentUser = clsUser::Find(Name, Password);
			loginfailed = CurrentUser.IsEmpty();
		} while (loginfailed);
		
		CurrentUser.RegisterLogin();
		clsMainMenuScreen::ShowMainMenuScreen();
	}

public:
	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screeen");
		_Login();
	}
};
