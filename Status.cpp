#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
using namespace std;
#include "Status.h"

Status::Status()
{
	_text = new char[MAX_CHARACTERS];
	_time = Clock();
}

Status::Status(const char* text, Clock time)
{
	_text = _strdup(text);
	_time = time;
}

Clock Status::getStatusTime()
{
	return _time;
}

void Status::getStatusInfo(Status* newStatus)
{
	char* tempStr = new char[MAX_CHARACTERS];

	cout << "Please insert your status: ";
	cin.getline(tempStr, MAX_CHARACTERS);
	int size = strlen(tempStr) + 1;

	newStatus->_text = tempStr;
	tempStr = nullptr;
	delete[] tempStr;

	cout << endl;
}

Status::~Status()
{
	delete _text;
}