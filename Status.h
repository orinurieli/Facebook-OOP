#ifndef __STATUS_H
#define __STATUS_H

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <string>
#include "Clock.h"

//#include <string.h> // todo delete once string works
const int MAX_CHARACTERS = 256; // todo delete once string works

class Status
{
	//char* _text; // todo delete once string works
	string _text;
	Clock _time;

public:
	Status() : _text("") {}
	//Status(const char* text, Clock time); // todo delete once string works
	Status(const string& text, Clock& time) : _text(text), _time(time) {}

	//char* getText() { return _text; } // todo delete once string works
	const string& getText() const { return _text; }
	//Clock& getDateAndHour() { return _time; } // todo - change to const ref! // delete this func
	const Clock& getStatusTime() { return _time; } // todo - change to const ref

	void getStatusInfo(Status& newStatus);

	bool operator==(const Status& other) const;
	bool operator!=(const Status& other) const;

	~Status();
};

#endif // __STATUS_H