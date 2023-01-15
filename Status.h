#ifndef __STATUS_H
#define __STATUS_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <string>
#include <vector>
#include "Clock.h"

#include <iostream>
using namespace std;

class Status
{
protected:
	string _text;
	Clock _time;
	Status() : _text("") {}
	Status(const string& text, Clock& time) : _text(text), _time(time) {}

	// todo: move Ctors to private - Abstract Class 
public:
	//Status() : _text("") {}
	//Status(const string& text, Clock& time) : _text(text), _time(time) {}

	const string& getText() const { return _text; }
	const Clock& getStatusTime() { return _time; }
	void setText(string& newText) { _text = newText; }

	// when an entity wants to insert a status
	virtual void insertStatus(Status& newStatus)
	{
		// todo -> find out what to do in here


		/*string text;
		cout << "Please insert your status: ";
		cin.ignore();
		getline(cin, text);
		newStatus._text = text;
		cout << "Status uploaded!" << endl;*/
	}

	virtual void display();

	bool operator==(const Status& other) const;
	bool operator!=(const Status& other) const;

	virtual ~Status() {};
};

#endif