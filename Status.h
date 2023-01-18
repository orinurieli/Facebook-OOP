#ifndef __STATUS_H
#define __STATUS_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <string>
#include <vector>
#include "Clock.h"

#include <iostream>
using namespace std;

// this class is an abstract class of status. cannot make objects type of status, needs to be specific: text, image or video.
class Status
{
protected:
	string _text; // all types of statuses can have text
	Clock _time;
	Status() : _text("") {}
	Status(const string& text, Clock& time) : _text(text), _time(time) {}

public:
	const string& getText() const { return _text; }
	const Clock& getStatusTime() { return _time; }
	void setText(string& newText) { _text = newText; }

	virtual void insertStatus() = 0; // when an entity wants to insert a status
	virtual void display() = 0; // this function prints a status

	friend ostream& operator<<(ostream& out, const Status& status);

	virtual ~Status() {};
};

#endif