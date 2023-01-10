#pragma once

#include <vector>
#include <string>
using namespace std;

#include "Status.h"


class TextStatus : public Status {

public:
	//TextStatus() : Status("init", new Clock()) {};
	TextStatus(const string& text, Clock& time, const string& videoUrl)
		: Status(text, time) {}

};



