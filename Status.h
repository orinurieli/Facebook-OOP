#ifndef __STATUS_H
#define __STATUS_H
#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <string>
#include "Clock.h"

class Status
{
	string _text;
	Clock _time;
public:
	Status() : _text("") {}
	Status(const string& text, Clock& time) : _text(text), _time(time) {}

	const string& getText() const { return _text; }
	const Clock& getStatusTime() { return _time; }

	void getStatusInfo(Status& newStatus);

	bool operator==(const Status& other) const;
	bool operator!=(const Status& other) const;

	~Status() {};
};

#endif