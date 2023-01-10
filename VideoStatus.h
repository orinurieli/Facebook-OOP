#pragma once

#include <vector>
#include <string>
using namespace std;

#include "Status.h"


class VideoStatus : public Status {
private:
	string _videoUrl;

public:
	VideoStatus(const string& text, Clock& time, const string& videoUrl)
		: Status(text, time), _videoUrl(videoUrl) {}

	const string& getVideoUrl() const { return _videoUrl; }
};


