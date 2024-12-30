#pragma once
#include<iostream>
#include<string>

using namespace std;
template <class T> class clsInputValidate
{
public:

	static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}	

	static T ReadT(string Massege = "Invalid, Enter again\n")
	{
		T Num;
		cin >> Num;
		while (cin.fail())
		{
			cin.clear(); //clear failure error
			cin.ignore(std::numeric_limits < std::streamsize>::max(), '\n');//ignore all the line
			cout << Massege;
			cin >> Num;
		}
		return Num;
	}
	
	static string ReadString()
	{
		string st = "";

		getline(cin >> ws, st);
		return st;
	}
	static string ReadString(string Massage)
	{
		string st = "";
		cout << Massage;
		getline(cin >> ws, st);
		return st;
	}

	static T ReadNumberBetween(T From, T To, string ErrorMassege)
	{
		T Num;
		Num = ReadT();
		while (!IsNumberBetween(Num, From, To))
		{
			cout << ErrorMassege << endl;
			Num = ReadT();
		}
		return Num;
	}


};