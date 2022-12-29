#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
using namespace std;
#include "Status.h"

//Status::Status() // todo- delete once the string works
//{
//	_text = new char[MAX_CHARACTERS];
//	_time = Clock();
//}

//Status::Status(const char* text, Clock time) // todo- delete if string works
//{
//	_text = _strdup(text);
//	_time = time;
//}

//Clock Status::getStatusTime()
//{
//	return _time;
//}

void Status::getStatusInfo(Status* newStatus)
{
	string text;

	cout << "Please insert your status: ";
	getline(cin, text);
	
	newStatus->_text = text;
	/*char* tempStr = new char[MAX_CHARACTERS]; // todo- delete once the string works

	cout << "Please insert your status: ";
	cin.getline(tempStr, MAX_CHARACTERS);
	int size = strlen(tempStr) + 1;

	newStatus->_text = tempStr;
	tempStr = nullptr;
	delete[] tempStr;

	cout << endl;*/
}

// checks if 2 statuses are identical in their text
bool Status::operator==(Status& other)
{
	return(_text == other._text);
}

// checks if 2 statuses are not identical in their text
bool Status::operator!=(Status& other)
{
	return(_text != other._text);
}

Status::~Status()
{
	//delete _text;
}