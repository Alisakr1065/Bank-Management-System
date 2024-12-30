#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"clsString.h"
#include"clsPerson.h"
#include"clsDate.h"
#include"clsUtil.h"

using namespace std;
class clsUser : public clsPerson
{
	string _UserName;
	string _Password;
	short _Permissions;
	bool _MarkForDelete = false;
	struct stLoginRegister;

	enum enMode { EmptyMode, UpdateMode, AddNewMode };
	enMode _Mode;

	static clsUser _ConvertLineToUserObject(string line)
	{
		vector<string>vUser = clsString::splitstring(line, "#//#");
		return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], clsUtil::Decrypt(vUser[5]), stoi(vUser[6]));
	}
	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string Line = "";
		Line = User.FirstName + Seperator;
		Line += User.LastName + Seperator;
		Line += User.Email + Seperator;
		Line += User.Phone + Seperator;
		Line += User._UserName + Seperator;
		Line += clsUtil::Encrypt(User._Password) + Seperator;
		Line += to_string(User._Permissions);

		return Line;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _LoadDataFromUsersFile(string FileName)
	{
		vector<clsUser>vUsers;
		fstream myfile;
		string line;

		myfile.open(FileName, ios::in);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				clsUser User = _ConvertLineToUserObject(line);
				vUsers.push_back(User);
			}
			myfile.close();
		}
		return vUsers;
	}
	static void _SaveDataToUsersFile(vector<clsUser>vUsers, string FileName)
	{
		fstream myfile;
		string line;

		myfile.open(FileName, ios::out);
		if (myfile.is_open())
		{
			for (clsUser& User : vUsers)
			{
				if ((User.MarkedForDelete() == false))
				{
					line = _ConvertUserObjectToLine(User);
					myfile << line << endl;
				}

			}
			myfile.close();
		}
	}
	static void _AddUserDataToFile(string line)
	{
		fstream myfile;

		myfile.open("Users.txt", ios::out | ios::app);
		if (myfile.is_open())
		{

			if (line != "")
				myfile << line << endl;

			myfile.close();
		}
	}

	static stLoginRegister _ConvertLineToLogRegRecord(string line)
	{
		vector<string>vLogRecords = clsString::splitstring(line, "#//#");
		stLoginRegister rec;

		rec.DateAndTime = vLogRecords[0];
		rec.UserName = vLogRecords[1];
		rec.Password = clsUtil::Decrypt(vLogRecords[2]);
		rec.Permissions = stoi(vLogRecords[3]);

		return rec;
	}
	string _PrepareLoginRecord(string Seperator = "#//#")
	{
		string Line = "";
		Line += clsDate::GetCurrentDateTimeString() + Seperator;
		Line += UserName + Seperator;
		Line += clsUtil::Encrypt(Password)+Seperator;
		Line += to_string(Permissions);

		return Line;
	}
	static vector<stLoginRegister> _LoadDataFromLogRegFile(string FileName)
	{
		vector<stLoginRegister>vLogRecords;
		fstream myfile;
		string line;

		myfile.open(FileName, ios::in);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				stLoginRegister Record = _ConvertLineToLogRegRecord(line);
				vLogRecords.push_back(Record);
			}
			myfile.close();
		}
		return vLogRecords;
	}

	void _Update()
	{
		vector<clsUser> vUsers = _LoadDataFromUsersFile("Users.txt");
		for (clsUser& C : vUsers)
		{
			if (C.UserName == UserName)
			{
				C = *this;
				break;
			}
		}
		_SaveDataToUsersFile(vUsers, "Users.txt");
	}
	void _AddNew()
	{
		_AddUserDataToFile(_ConvertUserObjectToLine(*this));
	}

public:
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, short Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	struct stLoginRegister
	{
		string DateAndTime = "";
		string UserName = "";
		string Password = "";
		short Permissions = 0;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string GetUserName()
	{
		return _UserName;
	}
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	__declspec(property(put = SetUserName, get = GetUserName))string UserName;

	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}
	short GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(put = SetPermissions, get = GetPermissions))short Permissions;

	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(put = SetPassword, get = GetPassword))string Password;

	enum enMainMenuPermissions
	{
		AllAccess = -1, ShowClientsPermission = 1, AddClientPermission = 2, DeleteClientPermission = 4, UpdateClientPermission = 8,
		FindClientPermission = 16, TransactionsPermission = 32, ManageUsersPermission = 64, CurrencyExchangePermission = 128,
		LoginRegister = 256
	};
	bool HasPermission(enMainMenuPermissions Permission)
	{
		if ((this -> Permissions == AllAccess))
			return true;

		else if ((this -> Permissions & Permission) == Permission)
			return true;

		return false;
	}

	enum enSave { svFailedEmptyObject, svFailedExistObject, svSucceeded };
	enSave Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			return svFailedEmptyObject;

		case clsUser::AddNewMode:
			if (IsUserExist(UserName))
			{
				return svFailedExistObject;
			}
			_AddNew();
			_Mode = enMode::UpdateMode;
			return svSucceeded;

		case clsUser::UpdateMode:
			_Update();
			return svSucceeded;
		}
	}

	bool Delete()
	{
		vector<clsUser> vUsers = _LoadDataFromUsersFile("Users.txt");
		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}
		_SaveDataToUsersFile(vUsers, "Users.txt");
		*this = _GetEmptyUserObject();

		return true;
	}
	bool MarkedForDelete()
	{
		return _MarkForDelete;
	}

	void RegisterLogin()
	{
		fstream myfile;
		string line = _PrepareLoginRecord();

		myfile.open("LogReg.txt", ios::out | ios::app);
		if (myfile.is_open())
		{
			myfile << line << endl;
			myfile.close();
		}
	}

	static clsUser Find(string UserName)
	{
		vector<clsUser>vUsers;
		fstream myfile;

		myfile.open("Users.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsUser User = _ConvertLineToUserObject(line);
				if (User.UserName == UserName)
				{
					myfile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			myfile.close();
		}
		return _GetEmptyUserObject();
	}
	static clsUser Find(string UserName, string Password)
	{
		vector<clsUser>vUsers;
		fstream myfile;

		myfile.open("Users.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsUser User = _ConvertLineToUserObject(line);
				if (User.UserName == UserName && User.Password == Password)
				{
					myfile.close();
					return User;
				}
				vUsers.push_back(User);
			}
			myfile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser GetNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = Find(UserName);
		return (!User.IsEmpty());
	}
	static bool IsUserExist(string UserName, string Password)
	{
		clsUser User = Find(UserName, Password);
		return (!User.IsEmpty());
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadDataFromUsersFile("Users.txt");
	}
	static vector<stLoginRegister> GetLogRegList()
	{
		return _LoadDataFromLogRegFile("LogReg.txt");
	}

};