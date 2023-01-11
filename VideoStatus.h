#pragma once
#include "Status.h"

#include <iostream>
using namespace std;
#include <string>

class VideoStatus : public Status
{
private:
	string _videoUrl;
public:
	VideoStatus() : Status() {}
	VideoStatus(const string& text, Clock& time, const string& videoUrl): Status(text, time), _videoUrl(videoUrl) {}

	const string& getVideoUrl() const;
	virtual void insertStatus();
	virtual void display();
};