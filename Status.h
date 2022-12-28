#ifndef __STATUS_H
#define __STATUS_H

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <string>
#include "Clock.h"

//#include <string.h>
const int MAX_CHARACTERS = 256;

class Status
{
	//char* _text;
	string _text;
	Clock _time;

public:
	Status() : _text("") {}
	//Status(const char* text, Clock time);
	Status(const string& text, Clock time) : _text(text), _time(time) {}

	//char* getText() { return _text; }
	const string getText() { return _text; }
	Clock getDateAndHour() { return _time; }
	Clock getStatusTime();
	void getStatusInfo(Status* newStatus);

	bool operator==(Status& other);
	bool operator!=(Status& other);

	~Status();
};

#endif // __STATUS_H