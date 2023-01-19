#ifndef __CLOCK_H
#define __CLOCK_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>

enum StringLocation { startDay, endDay, startMonth = 3, endMonth = 4, startYear = 6, endYear = 9 };
enum Dates{minDay=1, maxDay=31, minMonth=1, maxMonth=12, minYear=1900, maxYear=2023};

class Clock
{
	int _day;
	int _month;
	int _year;
	int _hours;
	int _minutes;
	int _seconds;

public:
	Clock();
	Clock(int day, int month, int year) throw (const char*); // to enter date manually (e.g. in birthday)

	int stringToNumber(string& str, int start, int end);
	Clock& getBirthdayInput();
	void displayDate() const;
	void displayHour() const;

	// implamented in Functions.h
	friend ostream& operator<<(ostream& out, const Clock& date); 
	friend istream& operator>>(istream& in, Clock& date);
};

#endif

