#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>

using namespace std;
#include "Status.h"



// checks if 2 statuses are identical in their text
bool Status::operator==(const Status& other) const
{
	return(_text == other._text);
}

// checks if 2 statuses are not identical in their text
bool Status::operator!=(const Status& other) const
{
	return(_text != other._text);
}

// this function prints a status
void Status::display()
{
	cout << "-----------------------------------" << endl;
	cout << "Text: " << _text << endl;
	cout << "Uploaded on: ";
	_time.displayDate();
	cout << " | ";
	_time.displayHour();
	cout << endl;
	cout << "-----------------------------------" << endl;
}
