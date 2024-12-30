#pragma warning(disable:4996)
#pragma once
#include<iostream>
#include<string>
#include"clsString.h"
#include<iomanip>
using namespace std;


class clsDate
{
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:
	enum CompareDatesresult { Before = -1, Equal = 0, After = 1 };

	clsDate()
	{
		time_t t = time(0);
		tm* CDate = localtime(&t);

		_Day = CDate-> tm_mday;
		_Month = (CDate -> tm_mon) + 1;
		_Year = (CDate -> tm_year) + 1900;
	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(string sDate)
	{
		vector<string>vDate = clsString::splitstring(sDate, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Year)
	{
		clsDate Date = DateFromOrderOfDay(Day, Year);
		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	__declspec(property(put = SetDay, get = GetDay))short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(put = SetMonth, get = GetMonth))short Month;

	void SetYear(short Year)
	{
		_Day = Year;
	}
	short GetYear()
	{
		return _Year;
	}
	__declspec(property(put = SetYear, get = GetYear))short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	static bool CheckLeapYear(short year)
	{
		return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0));
	}
	bool CheckLeapYear()
	{
		return CheckLeapYear(_Year);
	}

	int DaysInYear(short year)
	{
		return (CheckLeapYear(year)) ? 366 : 365;
	}

	static int DaysInMonth(short Month, short year)
	{
		if (Month < 1 || Month > 12)
			return 0;

		short Days[] = { 31,28,31,30,31,30,31,31,30,31, 30, 31 };

		return ((Month == 2) ? (CheckLeapYear(year) ? 29 : 28) : Days[Month - 1]);
	}
	int DaysInMonth()
	{
		return DaysInMonth(_Month, _Year);
	}

	static short DayIndexInWeek(short Day, short Month, short year)
	{
		short a = ((14 - Month) / 12);
		short y = year - a;
		short m = Month + 12 * a - 2;
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	static short DayIndexInWeek(clsDate Date)
	{
		return DayIndexInWeek(Date._Day, Date._Month, Date._Year);
	}

	static string DayName(short OrderOfDay)
	{
		string Days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri","Sat" };
		return Days[OrderOfDay];
	}

	static void PrintMonthCalender(short Month, short year)
	{
		string MonName[] = { "Jan", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov","Dec" };

		cout << "\n" << setw(2) << " " << "---------------(" << MonName[Month - 1] << ")-------------\n";
		for (short i = 0; i < 7; i++)
		{
			cout << setw(5) << DayName(i);
		}

		cout << endl;

		short ord = DayIndexInWeek(1, Month, year);
		short c = 0;

		for (short i = 1; i <= DaysInMonth(Month, year); i++)
		{

			if (i == 1)
			{
				for (short i = 0; i < ord; i++)
				{
					cout << setw(5) << " ";
					c++;
				}
			}

			cout << setw(5) << i;
			c++;

			if (c == 7)
			{
				cout << endl;
				c = 0;
			}
		}
		cout << "\n" << setw(2) << " " << "---------------------------------\n";
	}
	void PrintMonthCalender()
	{
		PrintMonthCalender(_Month, _Year);
	}

	static void PrintYearCalender(short year)
	{
		for (short i = 0; i < 12; i++)
		{
			PrintMonthCalender(i, year);
		}
	}
	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}

	short DayOrderInYear(short Day, short Month, short year)
	{
		short count = 0;

		for (short i = 1; i < Month; i++)
		{
			count += DaysInMonth(i, year);
		}
		count += Day;
		return count;
	}
	short DayOrderInYear(clsDate Date)
	{
		return DayOrderInYear(Date._Day, Date._Month, Date._Year);
	}

	clsDate DateFromOrderOfDay(short DayOrder, short year)
	{
		clsDate Date;
		Date._Year = year;
		Date._Month = 1;

		short RemainingDays = DayOrder;
		short MonthDays = 0;

		while (true)
		{
			MonthDays = DaysInMonth(Date._Month, year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}
	clsDate DateAfterAddingDays(short AdditionDays, clsDate Date)
	{
		short RemainingDays = AdditionDays + DayOrderInYear(Date._Day, Date._Month, Date._Year);
		Date._Month = 1;
		short MonthDays = 0;

		while (true)
		{
			MonthDays = DaysInMonth(Date._Month, Date._Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;
				if (Date._Month > 12)
				{
					Date._Year++;
					Date._Month = 1;
				}
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : (Date1._Year == Date2._Year) ? ((Date1._Month < Date2._Month) ? true : (Date1._Month == Date2._Month) ? (Date1._Day < Date2._Day) : false) : false;
	}
	static bool IsEqualDates(clsDate Date1, clsDate Date2)
	{
		return ((Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? Date1._Day == Date2._Day : false) : false);
	}
	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsEqualDates(Date1, Date2));
	}
	static short CompareTwoDates(clsDate Date1, clsDate Date2)
	{
		return ((IsDate1BeforeDate2(Date1, Date2)) ? -1 : (IsEqualDates(Date1, Date2)) ? 0 : 1);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date._Day == DaysInMonth(Date._Month, Date._Year);
	}
	bool IsLastDayInMonth()
	{
		IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IsLastMonthInYear()
	{
		IsLastMonthInYear(_Month);
	}

	static short DiffBetweenTwoDates(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		short Diff = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Diff++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return (IncludeEndDay) ? ++Diff : Diff;
	}

	static clsDate GetCurrentDate()
	{
		time_t t = time(0);
		tm* CDate = localtime(&t);

		clsDate CurrentDate;
		CurrentDate._Day = CDate->tm_mday;
		CurrentDate._Month = (CDate->tm_mon) + 1;
		CurrentDate._Year = (CDate->tm_year) + 1900;
		return CurrentDate;
	}
	static string GetCurrentTime()
	{

		time_t t = time(0);
		tm* now = localtime(&t);

		short Hours = 0, Mins = 0, Secs = 0;
		Hours = now->tm_hour;
		Mins = now->tm_min;
		Secs = now->tm_sec;
		
		return  to_string(Hours) + ":" + to_string(Mins) + ":" + to_string(Secs);
	
	}
	static string GetCurrentDateTimeString()
	{
		return DateToString(clsDate()) + " - " + clsDate::GetCurrentTime();
	}

	static short AgeInDays(clsDate Age)
	{
		clsDate CurrentDate = GetCurrentDate();
		return DiffBetweenTwoDates(Age, CurrentDate, true);
	}

	void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate Temp;
		Temp._Day = Date1._Day;
		Temp._Month = Date1._Month;
		Temp._Year = Date1._Year;

		Date1._Day = Date2._Day;
		Date1._Month = Date2._Month;
		Date1._Year = Date2._Year;

		Date2._Day = Temp._Day;
		Date2._Month = Temp._Month;
		Date2._Year = Temp._Year;
	}

	static bool IsValidateDate(clsDate Date)
	{
		return (Date._Day >= 1 && Date._Day <= DaysInMonth(Date._Month, Date._Year)) && (Date._Month <= 12 && Date._Month >= 1) && (Date._Year > 0);
	}
	bool IsValidateDate()
	{
		return IsValidateDate(*this);
	}

	clsDate StringToDate(string sDate)
	{
		clsDate Date;
		vector<string>vDate = clsString::splitstring(sDate, "/");

		Date._Day = stoi(vDate[0]);
		Date._Month = stoi(vDate[1]);
		Date._Year = stoi(vDate[2]);

		return Date;
	}

	static string DateToString(clsDate Date)
	{
		string sDate;
		if (!IsValidateDate(Date))
		{
			return "Null";
		}
		return	to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}
	string DateToString()
	{
		return DateToString(*this);
	}
	string FormatDate(clsDate Date, string Format = "dd/mm/yyyy")
	{
		string FormattedDate = "";

		FormattedDate = clsString::ReplaceWord(Format, "dd", to_string(Date._Day));
		FormattedDate = clsString::ReplaceWord(FormattedDate, "mm", to_string(Date._Month));
		FormattedDate = clsString::ReplaceWord(FormattedDate, "yyyy", to_string(Date._Year));

		return FormattedDate;
	}

	static clsDate IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date._Month))
			{
				Date._Day = 1;
				Date._Month = 1;
				Date._Year++;
			}

			else
			{
				Date._Day = 1;
				Date._Month++;
			}
		}

		else
			Date._Day++;

		return Date;
	}
	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, short AddOns)
	{
		for (short i = 0; i < AddOns; i++)
			Date = IncreaseDateByOneDay(Date);

		return Date;
	}
	void IncreaseDateByXDays(short AddOns)
	{
		IncreaseDateByXDays(*this, AddOns);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		return IncreaseDateByXDays(Date, 7);
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, short AddOns)
	{
		for (short i = 0; i < AddOns; i++)
			Date = IncreaseDateByOneWeek(Date);

		return Date;
	}
	void IncreaseDateByXWeeks(short AddOns)
	{
		IncreaseDateByXWeeks(*this, AddOns);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsLastMonthInYear(Date._Month))
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
			Date._Month++;

		short MonthDays = DaysInMonth(Date._Month, Date._Year);
		if (Date._Day > MonthDays)
		{
			Date._Day = MonthDays;
		}

		return Date;
	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short AddOns)
	{
		for (short i = 0; i < AddOns; i++)
			Date = IncreaseDateByOneMonth(Date);

		return Date;
	}
	void IncreaseDateByXMonths(short AddOns)
	{
		IncreaseDateByXMonths(*this, AddOns);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date._Year++;
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short AddOns)
	{
		Date._Year += AddOns;
		return Date;
	}
	void IncreaseDateByXYears(short AddOns)
	{
		IncreaseDateByXYears(*this, AddOns);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date._Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, short AddOns)
	{
		Date._Year += AddOns * 10;
		return Date;
	}
	void IncreaseDateByXDecades(short AddOns)
	{
		IncreaseDateByXDecades(*this, AddOns);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date._Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date._Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date._Day == 1)
		{
			if (Date._Month == 1)
			{
				Date._Year--;
				Date._Month = 12;
				Date._Day = 31;
			}

			else
			{
				Date._Month--;
				Date._Day = DaysInMonth(Date._Month, Date._Year);
			}
		}

		else
			Date._Day--;

		return Date;
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate& Date, short AddOns)
	{
		for (short i = 0; i < AddOns; i++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}
	void DecreaseDateByXDays(short AddOns)
	{
		DecreaseDateByXDays(*this, AddOns);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		return DecreaseDateByXDays(Date, 7);
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate& Date, short AddOns)
	{
		for (short i = 0; i < AddOns; i++)
			Date = DecreaseDateByOneWeek(Date);

		return Date;
	}
	void DecreaseDateByXWeeks(short AddOns)
	{
		DecreaseDateByXWeeks(*this, AddOns);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;

		short MonthDays = DaysInMonth(Date._Month, Date._Year);
		if (Date._Day > MonthDays)
		{
			Date._Day = MonthDays;
		}

		return Date;
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate& Date, short AddOns)
	{
		for (short i = 0; i < AddOns; i++)
			Date = DecreaseDateByOneMonth(Date);

		return Date;
	}
	void DecreaseDateByXMonths(short AddOns)
	{
		DecreaseDateByXMonths(*this, AddOns);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date._Year--;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short AddOns)
	{
		Date._Year -= AddOns;
		return Date;
	}
	void DecreaseDateByXYears(short AddOns)
	{
		DecreaseDateByXYears(*this, AddOns);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date._Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short AddOns)
	{
		Date._Year -= AddOns * 10;
		return Date;
	}
	void DecreaseDateByXDecades(short AddOns)
	{
		DecreaseDateByXDecades(*this, AddOns);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date._Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date._Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	bool IsEndOfWeek(clsDate Date)
	{
		return (DayIndexInWeek(Date) == 6);
	}
	bool IsWeekend(clsDate Date)
	{
		return (DayIndexInWeek(Date) == 6 || DayIndexInWeek(Date) == 5);
	}
	bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekend(Date);
	}

	short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return (6 - DayIndexInWeek(Date));
	}
	short DaysUntilTheEndOfMonth(clsDate Date)
	{
		return (DaysInMonth(Date._Month, Date._Year) - Date._Day) + 1;
	}
	short DaysUntilTheEndOfYear(clsDate Date)
	{
		return (DaysInYear(Date._Year)) - DayOrderInYear(Date) + 1;
	}
	short CalcVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short count = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				count++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return count;
	}
};