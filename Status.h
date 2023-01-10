#ifndef __STATUS_H
#define __STATUS_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <string>
#include <vector>
#include "Clock.h"

class Status
{
private:
	string _text;
	Clock _time;

	// todo: move Ctors to private - Abstract Class 
public:
	Status() : _text("") {}
	Status(const string& text, Clock& time) : _text(text), _time(time) {}

	const string& getText() const { return _text; }
	const Clock& getStatusTime() { return _time; }

	virtual void getStatusInfo(Status& newStatus);
	virtual void display();

	bool operator==(const Status& other) const;
	bool operator!=(const Status& other) const;

	virtual ~Status() {};
};

#endif