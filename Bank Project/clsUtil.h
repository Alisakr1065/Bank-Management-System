#pragma once
#include<iostream>
#include<string>
#include<cstdlib>
#include"clsDate.h"

using namespace std;
class clsUtil
{
	enum enType { Digits = 1, SpecialChars = 2, SmallLetters = 3, CapitalLetters = 4, MixChars = 5 };

public:
	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static short GetRandomNum(short from, short to)
	{
		int num = 0;
		num = rand() % (to - from + 1) + from;
		return num;
	}
	static char GetRandomChar(enType type)
	{
		switch (type)
		{
		case Digits:
		{
			return char(GetRandomNum(48, 57));
		}
		case SpecialChars:
		{
			return char(GetRandomNum(33, 47));
		}
		case SmallLetters:
		{
			return char(GetRandomNum(97, 122));
		}
		case CapitalLetters:
		{
			return char(GetRandomNum(65, 90));
		}
		case MixChars:
		{
			return char(GetRandomNum(48, 122));
		}
		}

	}

	static void Tabs(short NumOfTabs)
	{
		for (short i = 0; i < NumOfTabs; i++)
			cout << "\t";

	}

	static void FillArrayWithRandNums(int arr[100], int length)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = GetRandomNum(1, 100);
		}
	}
	static void FillArrayWithRandWords(string arr[100], short arrlength, enType Type, short WrdLength)
	{
		for (short i = 0; i < arrlength; i++)
		{
			arr[i] = GenerateWord(Type, WrdLength);
		}
	}
	static void FillArrayWithRandKeys(string arr[100], short arrlength, enType Type, short WrdLength)
	{
		for (short i = 0; i < arrlength; i++)
		{
			arr[i] = GenerateKey(Type);
		}
	}

	static void PrintArray(int arr[100], int length)
	{
		for (int i = 0; i < length; i++)
		{
			cout << arr[i] << " ";
		}
		cout << '\n';
	}

	static string Encrypt(string Text, short EncryptionKey = 2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char(int(Text[i]) + EncryptionKey);
		}
		return Text;
	}
	static string Decrypt(string Text, short EncryptionKey = 2)
	{
		for (int i = 0; i <= Text.length(); i++)
		{
			Text[i] = char(int(Text[i]) - EncryptionKey);
		}
		return Text;
	}

	static string GenerateWord(enType type, short length)
	{
		string word;
		for (int i = 1; i <= length; i++)
		{
			word = word + GetRandomChar(type);
		}
		return word;
	}
	static string GenerateKey(enType Type)
	{
		string key = "";
		key = GenerateWord(Type, 4) + "-";
		key = key + GenerateWord(Type, 4) + "-";
		key = key + GenerateWord(Type, 4) + "-";
		key = key + GenerateWord(Type, 4);

		return key;
	}
	static void PrintNumofKeys(short Number, enType Type)
	{

		for (short i = 1; i <= Number; i++)
		{
			cout << "key [ " << i << " ]: " << GenerateKey(Type) << endl;
		}
	}

	static int MaxNumberinArray(int arr[100], int length)
	{
		int Max = 0;
		for (int i = 0; i < length; i++)
		{
			if (arr[i] > Max)
			{
				Max = arr[i];
			}
		}
		return Max;
	}
	static int MinNumberinArray(int arr[100], int length)
	{
		int Min = arr[0];
		for (int i = 0; i < length; i++)
		{
			if (arr[i] < Min)
			{
				Min = arr[i];
			}
		}
		return Min;
	}

	float SumofNumsinArray(int arr[100], int length)
	{
		float sum = 0;
		for (int i = 0; i < length; i++)
		{
			sum += arr[i];
		}
		return sum;
	}
	float AverageNumsinArray(int arr[100], int length)
	{
		return float(SumofNumsinArray(arr, length) / length);
	}

	void Swap(int& n1, int& n2)
	{
		int temp = 0;
		temp = n1;
		n1 = n2;
		n2 = temp;
	}
	void Swap(float& n1, float& n2)
	{
		float temp = 0;
		temp = n1;
		n1 = n2;
		n2 = temp;
	}
	void Swap(string& S1, string& S2)
	{
		string temp = "";
		temp = S1;
		S1 = S2;
		S2 = temp;
	}
	void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate temp;
		temp = Date1;
		Date1 = Date2;
		Date2 = temp;
	}


	void ShuffleArray(int arr[100], int length)
	{
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GetRandomNum(1, length) - 1], arr[GetRandomNum(1, length) - 1]);
		}
	}
	void ShuffleArray(string arr[100], int length)
	{
		for (int i = 0; i < length; i++)
		{
			Swap(arr[GetRandomNum(1, length) - 1], arr[GetRandomNum(1, length) - 1]);
		}
	}

	static string NumToText(int Num)
	{

		if (Num == 0)
			return "";

		if (Num >= 1 && Num <= 999)
		{

			if (Num >= 1 && Num <= 19)      //Units
			{
				string text[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven",
									"Tweleve","Thirteen","Fourteen","Fifteen","Sixteen","Eeventeen","Eighteen","Ninteen" };
				return text[Num];
			}

			if (Num >= 20 && Num <= 99)     //Tens
			{
				string text[] = { "", "", "Tewenty","Thirty","Fourty", "Fifty", "Sixty","Seventy","Eighty","Ninty" };

				return text[Num / 10] + " " + NumToText(Num % 10);
			}

			if (Num >= 100 && Num <= 999)   //Hundreds
			{
				string text[] = { "", "One","Two","Three","Four","Five","Six","Seven","Eight","Nine" };

				if ((Num / 100) > 1)
					return text[Num / 100] + " " + "Hundreds" + " " + NumToText(Num % 100);
				else
					return text[Num / 100] + " " + "Hundred" + " " + NumToText(Num % 100);

			}
		}

		else if (Num >= 1000 && Num <= 999999)
		{
			return NumToText(Num / 1000) + " " + "Thousands" + " " + NumToText(Num % 1000);
		}

		else if (Num >= 1000000 && Num <= 999999999)
		{
			return NumToText(Num / 1000000) + " " + "Millions" + " " + NumToText(Num % 1000000);
		}

		else if (Num >= 1000000000 && Num <= 999999999999)
		{
			return NumToText(Num / 1000000000) + " " + "Billions" + " " + NumToText(Num % 1000000000);
		}
	}

};