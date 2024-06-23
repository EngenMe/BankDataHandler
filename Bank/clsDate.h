#pragma once
#pragma warning(disable : 4996) // Disable warning 4996

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

#include "clsString.h"; // Include header file for clsString class

class clsDate
{
private:
	enum _enDateFormat
	{
		dd_mm_yy,       // Day-Month-Year format
		mm_dd_yy,       // Month-Day-Year format
		dd_month_yy     // Day-MonthName-Year format
	};

	std::vector<std::string> _v_month_names =
	{
		"",             // Index 0 is not used, month names start from index 1
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	std::vector<std::string> _v_week_days =
	{
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};

	std::vector<std::string> _v_weekend_days =
	{
		"Saturday",
		"Sunday"
	};

	// Function to return "st", "nd", "rd", or "th" for day formatting
	std::string _GetStNdRd(short day)
	{
		if (day == 1 || day == 21 || day == 31)
			return "st";
		else if (day == 2 || day == 22)
			return "nd";
		else if (day == 3 || day == 23)
			return "rd";
		else
			return "th";
	}

	// Function to check if a year is leap year
	bool _IsLeap(short year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}

	// Function to return number of days in a year (364 or 365)
	short _HowManyDaysInYear(short year)
	{
		return _IsLeap(year) ? 365 : 364;
	}

	// Function to return number of days in a month, considering leap year
	short _HowManyDaysInMonth(short month, bool is_leap)
	{
		short arr_month_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (month == 2) ? (is_leap ? 29 : 28) : arr_month_days[month - 1];
	}

	// Function to calculate and return a date from day order in a year
	clsDate _GetDateFromDayOrderInYear(short day_order_in_year, short year)
	{
		clsDate date;

		date._year = year;
		date._is_leap = _IsLeap(_year);
		date._month = 1;
		date._day = day_order_in_year;

		while (true)
		{
			short how_many_days_in_month = _HowManyDaysInMonth(date._month, date._is_leap);

			if (date._day >= how_many_days_in_month)
			{
				date._day -= how_many_days_in_month;
				date._month++;
			}
			else
				break;
		}

		return date;
	}

	// Function to validate if a given date is valid
	bool _IsValidDate(short day, short month, short year, bool is_leap)
	{
		if (year < 0 ||
			month < 0 || month > 12 ||
			day < 0 || day > _HowManyDaysInMonth(month, is_leap))
		{
			std::cerr << "Error: Invalid date!" << std::endl;
			exit(EXIT_FAILURE);
			return false;
		}

		return true;
	}

	// Function to calculate day of week order (0 to 6) for a given date
	short _DayOfWeekOrder(clsDate date)
	{
		short a, y, m;
		a = (14 - date._month) / 12;
		y = date._year - a;
		m = date._month + (12 * a) - 2;
		return (date._day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	// Function to calculate number of years in days and adjust days accordingly
	short _CalculateHowManyYearsInDays(int& days, short current_year)
	{
		short how_many_years = 0;
		short how_many_days_in_year = _HowManyDaysInYear(current_year);

		while (days >= how_many_days_in_year)
		{
			how_many_years++;
			days -= how_many_days_in_year;
			how_many_days_in_year = _HowManyDaysInYear(++current_year);
		}

		return how_many_years;
	}

	// Function to check if an element exists in a vector of strings
	bool _IsElementInVect(std::string element, std::vector<std::string> vec)
	{
		for (std::string s : vec)
		{
			if (s == element)
				return true;
		}

		return false;
	}

	// Function to find the index of an element in a vector of strings
	short _FindIndex(std::string element, std::vector<std::string> vec)
	{
		for (short i = 0; i < vec.size(); i++)
		{
			if (vec[i] == element)
				return i;
		}

		return -1;
	}

	short _day;         // Day of the date
	short _month;       // Month of the date
	short _year;        // Year of the date
	bool _is_leap;      // Is the year a leap year
	bool _is_valid_date;// Is the date valid

public:
	// Default constructor initializes date to current system date
	clsDate()
	{
		time_t t = time(0); tm* now = localtime(&t);
		_day = now->tm_mday;
		_month = now->tm_mon + 1;
		_year = now->tm_year + 1900;
		_is_leap = _IsLeap(_year);
	}

	// Constructor initializes date from string in format "day/month/year"
	clsDate(std::string str_date)
	{
		std::vector<std::string> v_str_date = clsString::Split(str_date, "/");
		_day = stoi(v_str_date[0]);
		_month = stoi(v_str_date[1]);
		_year = stoi(v_str_date[2]);
		_is_leap = _IsLeap(_year);
		_is_valid_date = _IsValidDate(_day, _month, _year, _is_leap);
	}

	// Constructor initializes date from day, month, year
	clsDate(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
		_is_leap = _IsLeap(_year);
		_is_valid_date = _IsValidDate(_day, _month, _year, _is_leap);
	}

	// Constructor initializes date from day order in year and year
	clsDate(short day_order_in_year, short year)
	{
		clsDate date = _GetDateFromDayOrderInYear(day_order_in_year, year);
		_day = date._day;
		_month = date._month;
		_year = date._year;
		_is_leap = date._is_leap;
		_is_valid_date = _IsValidDate(_day, _month, _year, _is_leap);
	}

	// Static method to get the current system date as a clsDate object
	static clsDate GetSystemDate()
	{
		return clsDate();
	}

	// Setter methods for day, month, and year
	void SetDay(short day)
	{
		_day = day;
	}

	void SetMonth(short month)
	{
		_month = month;
	}

	void SetYear(short year)
	{
		_year = year;
		_is_leap = _IsLeap(_year);
	}

	// Getter methods for day, month, year, leap year status, and validity of the date
	short GetDay()
	{
		return _day;
	}

	short GetMonth()
	{
		return _month;
	}

	short GetYear()
	{
		return _year;
	}

	bool GetIsLeap()
	{
		return _is_leap;
	}

	bool GetIsValidDate()
	{
		return _IsValidDate(_day, _month, _year, _is_leap);
	}

	// Property declarations using __declspec(property)
	__declspec(property(get = GetDay, put = SetDay)) short day;
	__declspec(property(get = GetMonth, put = SetMonth)) short month;
	__declspec(property(get = GetYear, put = SetYear)) short year;
	__declspec(property(get = GetIsLeap)) bool is_leap;
	__declspec(property(get = GetIsValidDate)) bool is_valid_date;

	// Static method to display a given date in a specified format
	static void DisplayDate(clsDate date, _enDateFormat en_date_format = _enDateFormat::dd_month_yy)
	{
		std::cout << "Date: ";

		switch (en_date_format)
		{
		case _enDateFormat::dd_mm_yy:
			std::cout << date.day << "/" << date.month << "/" << date.year << std::endl;
			break;
		case _enDateFormat::mm_dd_yy:
			std::cout << date.month << "/" << date.month << "/" << date.year << std::endl;
			break;
		default:
			std::cout << date.day << date._GetStNdRd(date.day) << " " <<
				date._v_month_names[date.month] << " " << date.year << std::endl;
		}
	}

	// Method to display the current object's date in a specified format
	void DisplayDate(_enDateFormat en_date_format = _enDateFormat::dd_month_yy)
	{
		DisplayDate(*this, en_date_format);
	}

	// Static method to get the weekday name for a given date
	static std::string WeekDayName(clsDate date)
	{
		return date._v_week_days[date._DayOfWeekOrder(date)];
	}

	// Method to get the weekday name for the current object's date
	std::string WeekDayName()
	{
		return WeekDayName(*this);
	}

	// Static method to print a calendar for a specific month and year
	static void PrintMonthCalendar(short month, short year)
	{
		clsDate date;

		int current = date._DayOfWeekOrder(clsDate(1, month, year));
		int number_of_days = date._HowManyDaysInMonth(month, date._IsLeap(year));

		printf("\n  _______________%s_______________\n\n", date._v_month_names[month].substr(0, 3).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;
		for (i = 0; i < current; i++)
			printf("     ");
		for (int j = 1; j <= number_of_days; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n  _________________________________\n");
	}

	// Method to print the calendar for the current object's month and year
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_month, _year);
	}

	// Static method to print the calendar for a specific year
	static void PrintYearCalendar(int year)
	{
		printf("\n  _________________________________\n\n");
		printf("           Calendar - %d\n", year);
		printf("  _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, year);
		}
	}

	// Method to print the calendar for the current object's year
	void PrintYearCalendar()
	{
		PrintYearCalendar(_year);
	}

	// Static method to calculate the number of days from the beginning of the year for a given date
	static short DaysFromTheBeginingOfTheYear(clsDate date)
	{
		short total_days = 0;

		if (date._month == 1)
			return date._day;

		for (short i = 1; i < date._month; i++)
		{
			total_days += date._HowManyDaysInMonth(i, date._is_leap);
		}

		return total_days + date._day;
	}

	// Method to calculate the number of days from the beginning of the year for the current object's date
	short DaysFromTheBeginingOfTheYear()
	{
		return DaysFromTheBeginingOfTheYear(*this);
	}

	// Static method to add a specified number of days to a given date
	static clsDate AddDays(int days, clsDate date)
	{
		date._day += days;

		while (date._day > date._HowManyDaysInMonth(date._month, date._is_leap))
		{
			date._day -= date._HowManyDaysInMonth(date._month, date._is_leap);
			date._month++;
			if (date._month > 12)
			{
				date._month = 1;
				date._year++;
				date._is_leap = date._IsLeap(date._year);
			}
		}

		return date;
	}

	// Method to add a specified number of days to the current object's date
	void AddDays(int days)
	{
		*this = AddDays(days, *this);
	}

	// Static method to subtract a specified number of days from a given date
	static clsDate SubstractDays(int days, clsDate date)
	{
		date._day -= days;

		while (date._day <= 0)
		{
			date._month--;
			if (date._month < 1)
			{
				date._month = 12;
				date._year--;
				date._is_leap = date._IsLeap(date._year);
			}
			date._day += date._HowManyDaysInMonth(date._month, date._is_leap);
		}

		return date;
	}

	// Method to subtract a specified number of days from the current object's date
	void SubstractDays(int days)
	{
		*this = SubstractDays(days, *this);
	}

	// Static method to check if date1 is before date2
	static bool IsDate1BeforeDate2(clsDate date1, clsDate date2)
	{
		if (date1._year < date2._year)
		{
			return true;
		}
		else if (date1._year == date2._year)
		{
			if (date1._month < date2._month)
			{
				return true;
			}
			else if (date1._month == date2._month)
			{
				if (date1._day < date2._day)
				{
					return true;
				}
			}
		}
		return false;
	}

	// Method to check if the current object's date is before date2
	bool IsDateBeforeDate2(clsDate date2)
	{
		return IsDate1BeforeDate2(*this, date2);
	}

	// Static method to check if date1 is equal to date2
	static bool IsDate1EqualDate2(clsDate date1, clsDate date2)
	{
		return (date1._year == date2._year && date1._month == date2._month && date1._day == date2._day);
	}

	// Method to check if the current object's date is equal to date2
	bool IsDateEqualDate2(clsDate date2)
	{
		return IsDate1EqualDate2(*this, date2);
	}

	// Static method to check if the date is the last day in its month
	static bool IsLastDayInMonth(clsDate date)
	{
		return date._day == date._HowManyDaysInMonth(date._month, date._is_leap);
	}

	// Method to check if the current object's date is the last day in its month
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	// Static method to check if the month is December
	static bool IsLastMonthInYear(clsDate date)
	{
		return date._month == 12;
	}

	// Method to check if the current object's month is December
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(*this);
	}

	// Static method to swap two clsDate objects
	static void SwapDates(clsDate& date1, clsDate& date2)
	{
		clsDate temp_date;
		temp_date = date1;
		date1 = date2;
		date2 = temp_date;
	}

	// Static method to calculate the difference in days between two dates
	static int CalculateDateDifference(clsDate date1, clsDate date2)
	{
		if (date1._year == date2._year && date1._month == date2._month)
		{
			return abs(date1.day - date2.day);
		}

		clsDate min_date = IsDate1BeforeDate2(date1, date2) ? date1 : date2;
		clsDate max_date = IsDate1BeforeDate2(date1, date2) ? date2 : date1;

		int days = min_date._HowManyDaysInMonth(min_date._month, min_date._is_leap) - min_date._day;

		min_date._month++;
		while (min_date._year < max_date._year ||
			(min_date._year == max_date._year && min_date._month < max_date._month))
		{
			days += min_date._HowManyDaysInMonth(min_date._month, min_date._is_leap);
			min_date._month++;
			if (min_date._month > 12)
			{
				min_date._month = 1;
				min_date._year++;
				min_date._is_leap = min_date._IsLeap(min_date._year);
			}
		}

		days += max_date._day;

		return days;
	}

	// Method to calculate age in days from the current object's date to a specified age
	int CalculateAgeInDays(clsDate age)
	{
		return CalculateDateDifference(*this, age);
	}

	// Static method to increase a date by one week
	static clsDate IncreaseDateByOneWeek(clsDate date)
	{
		date.AddDays(7);

		return date;
	}

	// Method to increase the current object's date by one week
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	// Static method to increase a date by a specified number of weeks
	static clsDate IncreaseDateByNWeeks(clsDate date, short n_weeks)
	{
		date.AddDays(7 * n_weeks);

		return date;
	}

	// Method to increase the current object's date by a specified number of weeks
	void IncreaseDateByNWeeks(short n_weeks)
	{
		*this = IncreaseDateByNWeeks(*this, n_weeks);
	}

	// Static method to increase a date by one month
	static clsDate IncreaseDateByOneMonth(clsDate date)
	{
		date._month++;

		if (date._month > 12)
		{
			date._year++;
			date._is_leap = date._IsLeap(date._year);
			date._month = 1;
		}

		short how_many_days_in_month = date._HowManyDaysInMonth(date._month, date._is_leap);
		if (date._day > how_many_days_in_month)
		{
			date._day -= how_many_days_in_month;
			date._month++;
		}

		return date;
	}

	// Method to increase the current object's date by one month
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	// Static method to increase a date by a specified number of months
	static clsDate IncreaseDateByNMonths(clsDate date, short n_months)
	{
		for (int i = 1; i <= n_months; i++)
		{
			date.IncreaseDateByOneMonth();
		}

		return date;
	}

	// Method to increase the current object's date by a specified number of months
	void IncreaseDateByNMonths(short n_months)
	{
		*this = IncreaseDateByNMonths(*this, n_months);
	}

	// Static method to increase a date by one year
	static clsDate IncreaseDateByOneYear(clsDate date)
	{
		date._year++;

		return date;
	}

	// Method to increase the current object's date by one year
	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	// Static method to increase a date by a specified number of years
	static clsDate IncreaseDateByNYears(clsDate date, short n_years)
	{
		date._year += n_years;

		return date;
	}

	// Method to increase the current object's date by a specified number of years
	void IncreaseDateByNYears(short n_years)
	{
		*this = IncreaseDateByNYears(*this, n_years);
	}

	// Static method to increase a date by one decade
	static clsDate IncreaseDateByOneDecade(clsDate date)
	{
		date._year += 10;

		return date;
	}

	// Method to increase the current object's date by one decade
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	// Static method to increase a date by a specified number of decades
	static clsDate IncreaseDateByNDecades(clsDate date, short n_decades)
	{
		date._year += 10 * n_decades;

		return date;
	}

	// Method to increase the current object's date by a specified number of decades
	void IncreaseDateByNDecades(short n_decades)
	{
		*this = IncreaseDateByNDecades(*this, n_decades);
	}

	// Static method to increase a date by one century
	static clsDate IncreaseDateByOneCentury(clsDate date)
	{
		date._year += 100;

		return date;
	}

	// Method to increase the current object's date by one century
	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	// Static method to increase a date by a specified number of centuries
	static clsDate IncreaseDateByNCenturies(clsDate date, short n_centuries)
	{
		date._year += 100 * n_centuries;

		return date;
	}

	// Method to increase the current object's date by a specified number of centuries
	void IncreaseDateByNCenturies(short n_centuries)
	{
		*this = IncreaseDateByNCenturies(*this, n_centuries);
	}

	// Static method to increase a date by one millennium
	static clsDate IncreaseDateByOneMillennium(clsDate date)
	{
		date._year += 1000;

		return date;
	}

	// Method to increase the current object's date by one millennium
	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}

	// Static method to increase a date by a specified number of millennia
	static clsDate IncreaseDateByNMillennia(clsDate date, short n_millennia)
	{
		date._year += 1000 * n_millennia;

		return date;
	}

	// Method to increase the current object's date by a specified number of millennia
	void IncreaseDateByNMillennia(short n_millennia)
	{
		*this = IncreaseDateByNMillennia(*this, n_millennia);
	}

	// Static method to decrease a date by one week
	static clsDate DecreaseDateByOneWeek(clsDate date)
	{
		date.SubstractDays(7);

		return date;
	}

	// Method to decrease the current object's date by one week
	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	// Static method to decrease a date by a specified number of weeks
	static clsDate DecreaseDateByNWeeks(clsDate date, short n_weeks)
	{
		date.SubstractDays(7 * n_weeks);

		return date;
	}

	// Method to decrease the current object's date by a specified number of weeks
	void DecreaseDateByNWeeks(short n_weeks)
	{
		*this = DecreaseDateByNWeeks(*this, n_weeks);
	}

	// Static method to decrease a date by one month
	static clsDate DecreaseDateByOneMonth(clsDate date)
	{
		date._month--;

		if (date._month < 1)
		{
			date._year--;
			date._is_leap = date._IsLeap(date._year);
			date._month = 12;
		}

		short how_many_days_in_month = date._HowManyDaysInMonth(date._month, date._is_leap);
		if (date._day > how_many_days_in_month)
		{
			date._day = how_many_days_in_month;
		}

		return date;
	}

	// Method to decrease the current object's date by one month
	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	// Static method to decrease a date by a specified number of months
	static clsDate DecreaseDateByNMonths(clsDate date, short n_months)
	{
		for (int i = 1; i <= n_months; i++)
		{
			date.DecreaseDateByOneMonth();
		}

		return date;
	}

	// Method to decrease the current object's date by a specified number of months
	void DecreaseDateByNMonths(short n_months)
	{
		*this = DecreaseDateByNMonths(*this, n_months);
	}

	// Static method to decrease a date by one year
	static clsDate DecreaseDateByOneYear(clsDate date)
	{
		date._year--;

		return date;
	}

	// Method to decrease the current object's date by one year
	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	// Static method to decrease a date by a specified number of years
	static clsDate DecreaseDateByNYears(clsDate date, short n_years)
	{
		date._year -= n_years;

		return date;
	}

	// Method to decrease the current object's date by a specified number of years
	void DecreaseDateByNYears(short n_years)
	{
		*this = DecreaseDateByNYears(*this, n_years);
	}

	// Static method to decrease a date by one decade
	static clsDate DecreaseDateByOneDecade(clsDate date)
	{
		date._year -= 10;

		return date;
	}

	// Method to decrease the current object's date by one decade
	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	// Static method to decrease a date by a specified number of decades
	static clsDate DecreaseDateByNDecades(clsDate date, short n_decades)
	{
		date._year -= 10 * n_decades;

		return date;
	}

	// Method to decrease the current object's date by a specified number of decades
	void DecreaseDateByNDecades(short n_decades)
	{
		*this = DecreaseDateByNDecades(*this, n_decades);
	}

	// Static method to decrease a date by one century
	static clsDate DecreaseDateByOneCentury(clsDate date)
	{
		date._year -= 100;

		return date;
	}

	// Method to decrease the current object's date by one century
	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	// Static method to decrease a date by a specified number of centuries
	static clsDate DecreaseDateByNCenturies(clsDate date, short n_centuries)
	{
		date._year -= 100 * n_centuries;

		return date;
	}

	// Method to decrease the current object's date by a specified number of centuries
	void DecreaseDateByNCenturies(short n_centuries)
	{
		*this = DecreaseDateByNCenturies(*this, n_centuries);
	}

	// Static method to decrease a date by one millennium
	static clsDate DecreaseDateByOneMillennium(clsDate date)
	{
		date._year -= 1000;

		return date;
	}

	// Method to decrease the current object's date by one millennium
	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}

	// Static method to decrease a date by a specified number of millennia
	static clsDate DecreaseDateByNMillennia(clsDate date, short n_millennia)
	{
		date._year -= 1000 * n_millennia;

		return date;
	}

	// Method to decrease the current object's date by a specified number of millennia
	void DecreaseDateByNMillennia(short n_millennia)
	{
		*this = DecreaseDateByNMillennia(*this, n_millennia);
	}

	// Static method to check if the date is at the end of the week
	static bool IsEndOfWeek(clsDate date)
	{
		return date.WeekDayName() == date._v_week_days.back();
	}

	// Method to check if the current object's date is at the end of the week
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	// Static method to check if the date falls on a weekend
	static bool IsWeekEnd(clsDate date)
	{
		return date._IsElementInVect(date.WeekDayName(), date._v_weekend_days);
	}

	// Method to check if the current object's date falls on a weekend
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	// Static method to check if the date is a business day
	static bool IsBusinessDay(clsDate date)
	{
		return !date.IsWeekEnd();
	}

	// Method to check if the current object's date is a business day
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	// Static method to calculate the number of days until the end of the week
	static short DaysUntilTheEndOfWeek(clsDate date)
	{
		return date._FindIndex(date.WeekDayName(), date._v_week_days);
	}

	// Method to calculate the number of days until the end of the week for the current object's date
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	// Static method to calculate the number of days until the end of the month
	static short DaysUntilTheEndOfMonth(clsDate date)
	{
		clsDate end_of_month_date(date._HowManyDaysInMonth(date._month, date._is_leap), date._month, date._year);

		return clsDate::CalculateDateDifference(date, end_of_month_date);
	}

	// Method to calculate the number of days until the end of the month for the current object's date
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	// Static method to calculate the number of days until the end of the year
	static short DaysUntilTheEndOfYear(clsDate date)
	{
		return clsDate::CalculateDateDifference(date, clsDate(31, 12, date._year));
	}

	// Method to calculate the number of days until the end of the year for the current object's date
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	// Static method to calculate how many business days are between two dates
	static short HowManyBusinessDays(clsDate starting_date, clsDate ending_date)
	{
		short counter = 0;

		while (clsDate::IsDate1BeforeDate2(starting_date, ending_date))
		{
			if (clsDate::IsBusinessDay(starting_date))
				counter++;

			starting_date.AddDays(1);
		}

		return counter;
	}

	// Method to calculate how many business days are between the current object's date and a given end date
	short HowManyBusinessDays(clsDate ending_date)
	{
		return HowManyBusinessDays(*this, ending_date);
	}

	// Static method to calculate how many weekend days are between two dates
	static short HowManyWeekendDays(clsDate starting_date, clsDate ending_date)
	{
		short counter = 0;

		while (clsDate::IsDate1BeforeDate2(starting_date, ending_date))
		{
			if (clsDate::IsWeekEnd(starting_date))
				counter++;

			starting_date.AddDays(1);
		}

		return counter;
	}

	// Method to calculate how many weekend days are between the current object's date and a given end date
	short HowManyWeekendDays(clsDate ending_date)
	{
		return HowManyWeekendDays(*this, ending_date);
	}

	// Static method to calculate the return date after a vacation period
	static clsDate CalculateVacationReturnDate(clsDate starting_date, short vacation_days)
	{
		while (vacation_days > 0)
		{
			starting_date.AddDays(1);

			if (starting_date.IsBusinessDay())
				vacation_days--;
		}

		return starting_date;
	}

	// Method to calculate the return date after a vacation period starting from the current object's date
	clsDate CalculateVacationReturnDate(short vacation_days)
	{
		return CalculateVacationReturnDate(*this, vacation_days);
	}

	// Static method to get the current system date and time as a string
	static std::string GetSystemDateTimeStr()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		return std::to_string(now->tm_mday) + "/" +
			std::to_string(now->tm_mon + 1) + "/" +
			std::to_string(now->tm_year + 1900) + " - " +
			std::to_string(now->tm_hour) + ":" +
			std::to_string(now->tm_min) + ":" +
			std::to_string(now->tm_sec);
	}
};

