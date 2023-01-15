#include "Clock.h"

Clock::Clock()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d-%m-%Y : %X", &tstruct);

	string buffer = buf;

	_day = stringToNumber(buffer, startDay, endDay);
	_month = stringToNumber(buffer, startMonth, endMonth);
	_year = stringToNumber(buffer, startYear, endYear);
	_hours = tstruct.tm_hour;
	_minutes = tstruct.tm_min;
	_seconds = tstruct.tm_sec;
}

// in order to enter date manually
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

// takes a string of char numbers from a certain place, and returns the number
int Clock::stringToNumber(string& str, int start, int end)
{
	int res = 0;
	for (int i = start; i <= end; i++)
	{
		res *= 10;
		res += (str[i] - '0');
	}

	return res;
}

void Clock::displayDate() const
{
	cout << setfill('0') << setw(2) << _day << ".";
	cout << setfill('0') << setw(2) << _month << "." << _year;
}

void Clock::displayHour() const
{
	cout << setfill('0') << setw(2) << _hours << ":";
	cout << setfill('0') << setw(2) << _minutes << ":";
	cout << setfill('0') << setw(2) << _seconds;
}

// to enter a date manually
Clock& Clock::getBirthdayInput() noexcept(false)
{
	int d, m, y;

	cout << "Please enter date of birth:\n";
	cout << "Day: ";
	cin >> d;
	while (true)
	{
		try
		{
			if (d > 31 || d < 0) throw invalid_argument("Invalid Day input.");
			else break;
		}
		catch (const invalid_argument& err)
		{
			cout << endl << err.what() << endl;
			cout << "Please choose a day between 1-31: ";
			cin >> d;
		}
	}

	cout << "Month: ";
	cin >> m;
	while (true)
	{
		try
		{
			if (m > 12 || m < 1) throw invalid_argument("Invalid Month input");
			else break;
		}
		catch (const invalid_argument& err)
		{
			cout << endl << err.what() << endl;
			cout << "Please choose a month between 1-12: ";
			cin >> m;
		}
	}

	cout << "Year: ";
	cin >> y;
	while (true)
	{
		try
		{
			if (y > 2023 || y < 1900) throw invalid_argument("Invalid Year input");
			else break;
		}
		catch (const invalid_argument& err)
		{
			cout << endl << err.what() << endl;
			cout << "Please choose year between 1900-2023: ";
			cin >> y;
		}
	}

	Clock res(d, m, y);
	return res;
}

ostream& Clock::operator<<(ostream& out)
{
	out << " ";
	out << this->getDay();
	out << " ";
	out << this->getMonth();
	out << " ";
	out << this->getYear();
	out << " ";
	out << this->getHours();
	out << " ";
	out << this->getMinutes();
	out << " ";
	out << this->getSeconds();
	out << " ";

	return out;
}