#ifndef __STATUS_H
#define __STATUS_H

#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <ctime>  
#include <string.h>
const int MAX_CHARACTERS = 256;
#include "Clock.h"

class Status
{
	char* _text;
	Clock _time;

public:
	Status();
	Status(const char* text, Clock time);

	char* getText() { return _text; }
	Clock getDateAndHour() { return _time; }
	Clock getStatusTime();
	void getStatusInfo(Status* newStatus);

	~Status();
};

#endif // __STATUS_H