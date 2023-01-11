#ifndef __TEXTSTATUS_H
#define __TEXTSTATUS_H

#include <vector>
#include <string>
using namespace std;

#include "Status.h"

class TextStatus : public Status
{

public:
	//TextStatus() : Status("init", new Clock()) {};
	TextStatus() : Status()	{}
	TextStatus(const string& text, Clock& time)	: Status(text, time) {}

	// when an entity wants to insert a status
	virtual void insertStatus()
	{
		cout << "Please insert text: ";
		cin.ignore();
		getline(cin, _text);
		cout << "Text Status Uploaded!" << endl << endl;
	}

};

#endif