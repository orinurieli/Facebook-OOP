#include "TextStatus.h"

// when an entity wants to insert a status
void TextStatus::insertStatus()
{
	cout << "Please insert text: ";
	cin.ignore();
	getline(cin, _text);
	cout << "Text Status Uploaded!" << endl << endl;
}

// prints out the status to the screen
void TextStatus::display()
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