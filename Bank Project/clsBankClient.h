#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"clsString.h"
#include"clsDate.h"
#include"clsPerson.h"

using namespace std;
class clsBankClient : public clsPerson
{
	string _PinCode;
	string _AccNum;
	double _Balance;
	bool _MarkForDelete = false;

	enum enMode { EmptyMode, UpdateMode, AddNewMode };
	enMode _Mode;
	struct stTransferRegister;

	static clsBankClient _ConvertLineToClientObject(string line)
	{
		vector<string>vClient = clsString::splitstring(line, "#//#");
		return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));
	}
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string Line = "";
		Line = Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.PinCode + Seperator;
		Line += Client.AccNum() + Seperator;
		Line += to_string(Client.Balance);

		return Line;
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadDataFromFile(string FileName)
	{
		vector<clsBankClient>vClients;
		fstream myfile;

		myfile.open(FileName, ios::in);
		if (myfile.is_open())
		{
			string line;

			while (getline(myfile, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				vClients.push_back(Client);
			}
			myfile.close();
		}
		return vClients;
	}
	static void _SaveDataToFile(vector<clsBankClient>vClients, string FileName)
	{
		fstream myfile;

		myfile.open(FileName, ios::out);
		if (myfile.is_open())
		{
			string line;
			for (clsBankClient Client : vClients)
			{
				if ((Client.MarkedForDelete() == false))
				{
					line = _ConvertClientObjectToLine(Client);
					myfile << line << endl;
				}

			}
			myfile.close();
		}
	}
	static void _AddClientDataToFile(string line)
	{
		fstream myfile;

		myfile.open("Clients.txt", ios::out | ios::app);
		if (myfile.is_open())
		{

			if (line != "")
				myfile << line << endl;

			myfile.close();
		}
	}

	static stTransferRegister _ConvertLineToTransferRegRecord(string line)
	{
		vector<string>vLogRecords = clsString::splitstring(line, "#//#");
		stTransferRegister rec;

		rec.DateAndTime = vLogRecords[0];
		rec.SenderAccNum = vLogRecords[1];
		rec.AcceptorAccNum = vLogRecords[2];
		rec.Amount = stod(vLogRecords[3]);
		rec.SenderBalance = stod(vLogRecords[4]);
		rec.AcceptorBalance = stod(vLogRecords[5]);
		rec.SenderUserName = vLogRecords[6];

		return rec;
	}
	string _PrepareTransferRecord(clsBankClient Acceptor, float Amount, string Seperator = "#//#")
	{
		string Line = "";
		Line += clsDate::GetCurrentDateTimeString() + Seperator;
		Line += AccNum() + Seperator;
		Line += Acceptor.AccNum() + Seperator;
		Line += to_string(Amount) + Seperator;
		Line += to_string(Balance) + Seperator;
		Line += to_string(Acceptor.Balance) + Seperator;
		Line += CurrentUser.UserName;

		return Line;
	}
	static vector<stTransferRegister> _LoadDataFromTransferRegFile(string FileName)
	{
		vector<stTransferRegister>vLogRecords;
		fstream myfile;
		string line;

		myfile.open(FileName, ios::in);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				stTransferRegister Record = _ConvertLineToTransferRegRecord(line);
				vLogRecords.push_back(Record);
			}
			myfile.close();
		}
		return vLogRecords;
	}
	void _RegisterTransfer(clsBankClient ClientAcceptor, short Amount)
	{
		fstream myfile;
		string line = _PrepareTransferRecord(ClientAcceptor, Amount);

		myfile.open("TransferReg.txt", ios::out | ios::app);
		if (myfile.is_open())
		{
			myfile << line << endl;
			myfile.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient> vClients = _LoadDataFromFile("Clients.txt");
		for (clsBankClient& C : vClients)
		{
			if (C.AccNum() == AccNum())
			{
				C = *this;
				break;
			}
		}
		_SaveDataToFile(vClients, "Clients.txt");
	}
	void _AddNew()
	{
		_AddClientDataToFile(_ConvertClientObjectToLine(*this));
	}
public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string PinCode, string AccNum, double Balance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_PinCode = PinCode;
		_AccNum = AccNum;
		_Balance = Balance;
		_Mode = Mode;
	}

	struct stTransferRegister
	{
		string DateAndTime;
		string SenderAccNum;
		string AcceptorAccNum;
		float Amount;
		float SenderBalance;
		float AcceptorBalance;
		string SenderUserName;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccNum()
	{
		return _AccNum;
	}

	void SetBalance(double Balance)
	{
		_Balance = Balance;
	}
	double GetBalance()
	{
		return _Balance;
	}
	__declspec(property(put = SetBalance, get = GetBalance))double Balance;

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(put = SetPinCode, get = GetPinCode))string PinCode;

	bool Delete()
	{
		vector<clsBankClient> vClients = _LoadDataFromFile("Clients.txt");
		for (clsBankClient& C : vClients)
		{
			if (C.AccNum() == AccNum())
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveDataToFile(vClients, "Clients.txt");
		*this = _GetEmptyClientObject();
		
		return true;
	}
	bool MarkedForDelete()
	{
		return _MarkForDelete;
	}

	void Deposite(double Amount)
	{
		_Balance += Amount;
		Save();
	}

	void WithDraw(double Amount)
	{
		_Balance -= Amount;
		Save();
	}

	enum enSave { svFailedEmptyObject, svFailedExistObject, svSucceeded };
	enSave Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return svFailedEmptyObject;

		case clsBankClient::AddNewMode:
			if (IsClientExist(AccNum()))
			{
				return svFailedExistObject;
			}
			_AddNew();
			_Mode = enMode::UpdateMode;
			return svSucceeded;

		case clsBankClient::UpdateMode:
			_Update();
			return svSucceeded;
		}
	}

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient>vClients;
		fstream myfile;

		myfile.open("Clients.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				if (Client.AccNum() == AccountNumber)
				{
					myfile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			myfile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient>vClients;
		fstream myfile;

		myfile.open("clients.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsBankClient Client = _ConvertLineToClientObject(line);
				if (Client.AccNum() == AccountNumber && Client.PinCode == PinCode)
				{
					myfile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			myfile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient GetNewClientObject(string AccNum)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", "", AccNum, 0);
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadDataFromFile("Clients.txt");
	}

	bool Transfer(clsBankClient& ClientAcceptor, short Amount)
	{
		if (Amount > Balance)
			return false;
		
		WithDraw(Amount);
		ClientAcceptor.Deposite(Amount);
		_RegisterTransfer(ClientAcceptor, Amount);
		return true;
	}
	static vector<stTransferRegister> GetTransferRegList()
	{
		return _LoadDataFromTransferRegFile("TransferReg.txt");
	}
};