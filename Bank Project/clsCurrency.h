#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"clsString.h"

using namespace std;

class clsCurrency
{
	string _Country = "";
	string _Code = "";
	string _Name = "";
	float _Rate = 0;

	enum enMode { EmptyMode, UpdateMode };
	enMode _Mode;

	static clsCurrency _ConvertLineToCurrencyObject(string line)
	{
		vector<string>vCurrency = clsString::splitstring(line, "#//#");
		return clsCurrency(enMode::UpdateMode ,vCurrency[0], vCurrency[1], vCurrency[2],stod(vCurrency[3]));
	}
	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string Line = "";
		Line = Currency.Country() + Seperator;
		Line += Currency.Code() + Seperator;
		Line += Currency.Name() + Seperator;
		Line += to_string(Currency.Rate());

		return Line;
	}

	static vector<clsCurrency> _LoadDataFromFile(string FileName)
	{
		vector<clsCurrency>vClients;
		fstream myfile;

		myfile.open(FileName, ios::in);
		if (myfile.is_open())
		{
			string line;

			while (getline(myfile, line))
			{
				clsCurrency Client = _ConvertLineToCurrencyObject(line);
				vClients.push_back(Client);
			}
			myfile.close();
		}
		return vClients;
	}
	static void _SaveDataToFile(vector<clsCurrency>vCurrencies, string FileName)
	{
		fstream myfile;

		myfile.open(FileName, ios::out);
		if (myfile.is_open())
		{
			string line;
			for (clsCurrency Currency : vCurrencies)
			{
				line = _ConvertCurrencyObjectToLine(Currency);
				myfile << line << endl;
			}
			myfile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> vCurrencies = _LoadDataFromFile("Currencies.txt");
		for (clsCurrency& C : vCurrencies)
		{
			if (C.Code() == Code())
			{
				C = *this;
				break;
			}
		}
		_SaveDataToFile(vCurrencies, "Currencies.txt");
	}
public:

	clsCurrency(enMode Mode ,string Country, string Code, string Name, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_Code = Code;
		_Name = Name;
		_Rate = Rate;
	}

	string Country()
	{
		return _Country;
	}
	
	string Code()
	{
		return _Code;
	}
	
	string Name()
	{
		return _Name;
	}
	
	float Rate()
	{
		return _Rate;
	}
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	static bool IsCurrencyExistByCode(string Code)
	{
		clsCurrency Currency = FindByCode(Code);
		return (!Currency.IsEmpty());
	}
	static bool IsCurrencyExistByCountry(string Country)
	{
		clsCurrency Currency = FindByCountry(Country);
		return (!Currency.IsEmpty());
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadDataFromFile("Currencies.txt");
	}

	static clsCurrency _GetEmptyClientObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static clsCurrency FindByCode(string Code)
	{
		Code = clsString::AllLettertoUpper(Code);

		vector<clsCurrency>vCurrencies;
		fstream myfile;

		myfile.open("Currencies.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				if (Currency.Code() == Code)
				{
					myfile.close();
					return Currency;
				}
				vCurrencies.push_back(Currency);
			}
			myfile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::AllLettertoUpper(Country);
		
		vector<clsCurrency>vCurrencies;
		fstream myfile;

		myfile.open("Currencies.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				if (clsString::AllLettertoUpper(Currency.Country()) == Country)
				{
					myfile.close();
					return Currency;
				}
				vCurrencies.push_back(Currency);
			}
			myfile.close();
		}
		return _GetEmptyClientObject();
	}

	float ConvertToUSD(float Amount)
	{
		return float(Amount / Rate());
	}
	float ConvertToOtherCurrency(clsCurrency CurrencyTo, float Amount)
	{
		float InUSD = ConvertToUSD(Amount);

		if (CurrencyTo.Code() == "USD")
		{
			return InUSD;
		}

		return CurrencyTo.Rate() * InUSD;
	}
};