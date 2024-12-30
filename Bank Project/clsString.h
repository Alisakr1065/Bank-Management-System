#pragma once
#include<iostream>
#include<string>
#include<cctype>
#include<vector>

using namespace std;
enum enCase { Upper = 1, Lower = 2, Digit = 3, Punct = 4, blank = 5, All = 6 };

class clsString
{
	string _Value;
	short _Counter = 0;

public:

	clsString()
	{
		_Value = "";
	}
	clsString(string st)
	{
		_Value = st;
	}

	string GetString()
	{
		return _Value;
	}
	void SetString(string st)
	{
		_Value = st;
	}
	__declspec(property(put = SetString, get = GetString))string Value;

	static char InvertCharCase(char x)
	{
		return (isupper(x)) ? tolower(x) : toupper(x);
	}
	static string InvertStringlettersCase(string st)
	{
		for (short i = 0; i < st.length(); i++)
		{
			st[i] = InvertCharCase(st[i]);
		}
		return st;
	}
	string InvertStringlettersCase()
	{
		return InvertStringlettersCase(_Value);
	}

	static void Print1stLetter(string st)
	{
		bool FirstLetter = true;

		cout << "First Letter from each word in the string:\n";
		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ' && FirstLetter)
			{
				cout << st[i] << endl;
			}
			FirstLetter = ((st[i] == ' ') ? true : false);
		}
	}
	void Print1stLetter()
	{
		Print1stLetter(_Value);
	}

	static string FirstLettertoUpper(string st)
	{
		bool FirstLetter = true;
		for (short i = 0; i < st.length(); i++)
		{
			if (!isspace(st[i]) && FirstLetter)
			{
				st[i] = toupper(st[i]);
			}
			FirstLetter = ((st[i] == ' ') ? true : false);
		}
		return st;
	}
	string FirstLettertoUpper()
	{
		return FirstLettertoUpper(_Value);
	}

	static string FirstLettertoLower(string st)
	{
		bool FirstLetter = true;
		for (short i = 0; i < st.length(); i++)
		{
			if (!isspace(st[i]) && FirstLetter)
			{
				st[i] = tolower(st[i]);
			}
			FirstLetter = ((st[i] == ' ') ? true : false);
		}
		return st;
	}
	string FirstLettertoLower()
	{
		return FirstLettertoLower(_Value);
	}

	static string AllLettertoUpper(string st)
	{
		for (short i = 0; i < st.length(); i++)
			st[i] = toupper(st[i]);

		return st;
	}
	void AllLettertoUpper()
	{
		AllLettertoUpper(_Value);
	}

	static string AllLettertoLower(string st)
	{
		for (short i = 0; i < st.length(); i++)
			st[i] = tolower(st[i]);

		return st;
	}
	void AllLettertoLower()
	{
		AllLettertoLower(_Value);
	}

	static short CountCharInString(string st, char c)
	{
		short counter = 0;
		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] == c)
				counter++;
		}
		return counter;
	}
	short CountCharInString(char c)
	{
		return CountCharInString(_Value, c);
	}

	static short CountLetterCases(string st, enCase WhatToCount = All)
	{
		if (WhatToCount == All)
			return (short)st.length();

		short Counter = 0;
		for (short i = 0; i < st.length(); i++)
		{
			if (WhatToCount == Upper && isupper(st[i]))
				Counter++;
			else if (WhatToCount == Lower && islower(st[i]))
				Counter++;
			else if (WhatToCount == blank && isblank(st[i]))
				Counter++;
			else if (WhatToCount == Digit && isdigit(st[i]))
				Counter++;
			else if (WhatToCount == Punct && ispunct(st[i]))
				Counter++;
		}
		return Counter;
	}
	short CountLetterCases()
	{
		return CountLetterCases(_Value);
	}

	static void PrintEachWord(string st)
	{
		string delim = " ";
		short pos = 0;
		string word;

		while ((pos = st.find(delim)) != st.npos)
		{
			word = st.substr(0, pos);

			if (word != "")
			{
				cout << word << endl;
			}
			st.erase(0, pos + delim.length());
		}

		if (st != "")
		{
			cout << st << endl;
		}

	}
	void PrintEachWord()
	{
		PrintEachWord(_Value);
	}

	static short CountWords(string st)
	{
		short counter = 0;

		string delim = " ";
		short pos = 0;
		string word;

		while ((pos = st.find(delim)) != st.npos)
		{
			word = st.substr(0, pos);

			if (word != "")
			{
				counter++;
			}
			st.erase(0, pos + delim.length());
		}

		if (st != "")
		{
			counter++;
		}
		return counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static void PrintSTVector(vector<string>vST)
	{
		for (string& parameter : vST)
		{
			cout << parameter;
		}
	}

	static string TrimLeft(string st)
	{
		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ')
			{
				return st.substr(i, st.length() - i);
			}
		}
		return "";
	}
	string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static string TrimRight(string st)
	{
		for (int i = st.length() - 1; i >= 0; i--)
		{
			if (st[i] != ' ')
			{
				return st.substr(0, i + 1);
			}
		}
		return "";
	}
	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string Trim(string st)
	{
		return TrimLeft(TrimRight(st));
	}
	string Trim()
	{
		return Trim(_Value);
	}

	string JoinString(vector<string> vString, string delim)
	{
		string st = "";
		for (string& param : vString)
		{
			st += param.append(delim);
		}
		return st.substr(0, st.length() - delim.length());
	}
	string JoinString(string arrString[1000], short length, string delim)
	{
		string st = "";
		for (short i = 0; i < length; i++)
		{
			st += arrString[i].append(delim);
		}
		return st.substr(0, st.length() - delim.length());
	}

	static vector<string>splitstring(string st, string delim)
	{
		vector<string> SplitedString;
		short pos = 0;
		string word;

		while ((pos = st.find(delim)) != st.npos)
		{
			word = st.substr(0, pos);
			SplitedString.push_back(word);
			st.erase(0, pos + delim.length());
		}

		if (st != "")
		{
			SplitedString.push_back(st);
		}
		return SplitedString;
	}
	vector<string>splitstring(string delim)
	{
		return splitstring(_Value, delim);
	}

	static string ReverseString(string st)
	{
		string st2 = "";
		vector <string> vstring = splitstring(st, " ");
		vector <string>::iterator it = vstring.end();

		while (it != vstring.begin())
		{
			it--;
			st2 += *it + " ";
		}
		//return st2 = st2.substr(0, st2.length() - 1);
		return TrimRight(st2);
	}
	string ReverseString()
	{
		return ReverseString(_Value);
	}

	static string ReplaceWord(string st, string Join, string Replace)
	{
		short pos = st.find(Replace);
		while (pos != string::npos)
		{
			/*st.erase(pos, Replace.length());  they do the same function of replace method
			st.insert(pos, Join);*/
			st.replace(pos, Replace.length(), Join);
			pos = st.find(Replace);
		}
		return st;
	}
	string ReplaceWord(string Join, string Replace)
	{
		return ReplaceWord(_Value, Join, Replace);
	}

	static string RemovePunct(string st)
	{
		string st2 = "";

		for (short i = 0; i < st.length(); i++)
		{
			if (!ispunct(st[i]))
			{
				st2 += st[i];
			}
		}
		return st2;
	}
	string RemovePunct()
	{
		return RemovePunct(_Value);
	}
};