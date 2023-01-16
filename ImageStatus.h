#ifndef __IMAGESTATUS_H
#define __IMAGESTATUS_H

#include <vector>
#include <string>
using namespace std;

#include "Status.h"

class ImageStatus : public Status
{
private:
	string _imageUrl;

public:
	ImageStatus() : Status() {}
	ImageStatus(const string& text, Clock& time, const string& imageUrl) : Status(text, time), _imageUrl(imageUrl) {}

	const string& getImageUrl() const { return _imageUrl; }
	virtual void insertStatus() override;
	virtual void display() override;

	bool operator==(const ImageStatus& other) const { return(_text == other._text && _imageUrl == other._imageUrl); } // checks if 2 statuses are identical
	bool operator!=(const ImageStatus& other) const { return(_text != other._text || _imageUrl == other._imageUrl); } // checks if 2 statuses are not identical
};

#endif