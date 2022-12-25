#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

#include "Clock.h"

Clock::Clock()
{
	_hours = 0;
	_minutes = 0;
	_seconds = 0;
	_day = 0;
	_month = 0;
	_year = 0;

	currentDateTime();
}

// to enter date manually
Clock::Clock(int day, int month, int year) throw (const char*)
{
	try
	{
		_day = day;
		_month = month;
		_year = year;
		if (_day > 31 || _day < 0) throw "Invalid Day in Clock C'tor";
		if (_month > 12 || _month < 1) throw "Invalid Month in Clock C'tor";
		if (_year > 2023 || _year < 1900) throw "Invalid Year in Clock C'tor";
	}
	catch (const char* err)
	{
		cout << err << endl << endl;
	}


	_hours = 0; // in birthday the hour is not important
	_minutes = 0;
	_seconds = 0;
}

Clock Clock::getDate()
{
	return *this;
}

Clock Clock::getHour()
{
	return *this;
}

void Clock::displayDate()
{
	cout << setfill('0') << setw(2) << _day << ".";
	cout << setfill('0') << setw(2) << _month << "." << _year;
}

void Clock::displayHour()
{
	cout << setfill('0') << setw(2) << _hours << ":";
	cout << setfill('0') << setw(2) << _minutes << ":";
	cout << setfill('0') << setw(2) << _seconds;
}

// to enter a date manually
Clock Clock::getBirthdayInput() throw (const char*)
{
	int d, m, y;

	cout << "Please enter date of birth:\n";
	cout << "Day: ";
	cin >> d;
	if (d > 31 || d < 0) throw "Invalid Day";

	cout << "Month: ";
	cin >> m;
	if (m > 12 || m < 1) throw "Invalid Month";

	cout << "Year: ";
	cin >> y;
	if (y > 2023 || y < 1900) throw "Invalid Year";

	Clock res(d, m, y);

	return res;
}

// takes a string of char numbers from a certain place, and returns the number
int Clock::stringToNumber(char* str, int start, int end)
{
	int res = 0;
	for (int i = start; i <= end; i++)
	{
		res *= 10;
		res += (str[i] - '0');
	}

	return res;
}

// returns current date and hour
char* Clock::currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d-%m-%Y : %X", &tstruct);

	_day = stringToNumber(buf, 0, 1);
	_month = stringToNumber(buf, 3, 4);
	_year = stringToNumber(buf, 6, 9);
	_hours = tstruct.tm_hour;
	_minutes = tstruct.tm_min;
	_seconds = tstruct.tm_sec;

	return buf;
}