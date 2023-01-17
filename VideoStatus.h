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

	const string& getVideoUrl() const { return _videoUrl; }
	virtual void insertStatus() override;
	virtual void display() override;

	bool operator==(const VideoStatus& other) const { return(_text == other._text && _videoUrl == other._videoUrl); } // checks if 2 statuses are identical
	bool operator!=(const VideoStatus& other) const { return(_text != other._text || _videoUrl == other._videoUrl); } // checks if 2 statuses are not identical

};