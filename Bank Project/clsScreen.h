#pragma once
#include<iostream>
#include<iomanip>
#include"clsDate.h"
#include"clsUser.h"
using namespace std;

class clsScreen
{
protected:
	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\t User: " << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\t Date: " << clsDate::DateToString(clsDate());

        cout << "\n\t\t\t\t\t______________________________________\n\n";

	}
    static bool _CheckAccessRights(clsUser::enMainMenuPermissions Permission)
    {

        if (!CurrentUser.HasPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }
};