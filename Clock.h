#ifndef __CLOCK_H
#define __CLOCK_H
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <ctime>  
#include <string.h>

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
	Clock(int day, int month, int year); // to enter date manually (e.g. in birthday)

	int stringToNumber(string& str, int start, int end);
	void currentDateTime();
	int getDay() { return _day; }
	int getMonth() { return _month; }
	int getYear() { return _year; }
	int getHours() { return _hours; }
	int getMinutes() { return _minutes; }
	int getSeconds() { return _seconds; }

	Clock& getDate() { return *this; }
	Clock& getHour() { return *this; }

	void displayDate();
	void displayHour();
	Clock getBirthdayInput();
};

#endif // __CLOCK_H
