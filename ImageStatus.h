#pragma once

#include <vector>
#include <string>
using namespace std;

#include "Status.h"


class ImageStatus : public Status {
private:
	string _imageUrl;

public:
	ImageStatus(const string& text, Clock& time, const string& imageUrl)
		: Status(text, time), _imageUrl(imageUrl) {}

	const string& getImageUrl() const { return _imageUrl; }
};
