#ifndef __CLOCK_H
#define __CLOCK_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>

enum StringLocation{startDay, endDay, startMonth=3, endMonth=4,	startYear=6, endYear=9};

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

	int getDay() const { return _day; }
	int getMonth() const { return _month; }
	int getYear() const { return _year; }
	int getHours() const { return _hours; }
	int getMinutes() const { return _minutes; }
	int getSeconds() const { return _seconds; }
	int stringToNumber(string& str, int start, int end);

	Clock& getDate() { return *this; }
	//Clock& getHour() { return *this; }
	Clock& getBirthdayInput();

	ostream& operator<<(ostream& out);

	void displayDate() const;
	void displayHour() const;
};

#endif
