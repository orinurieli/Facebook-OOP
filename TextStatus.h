#ifndef __TEXTSTATUS_H
#define __TEXTSTATUS_H

#include <vector>
#include <string>
using namespace std;

#include "Status.h"

class TextStatus : public Status
{
public:
	TextStatus() : Status()	{}
	TextStatus(const string& text, Clock& time)	: Status(text, time) {}

	virtual void insertStatus() override;
	virtual void display() override;

	bool operator==(const TextStatus& other) const { return(_text == other._text); } // checks if 2 statuses are identical
	bool operator!=(const TextStatus& other) const { return(_text != other._text); } // checks if 2 statuses are not identical

};

#endif