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
	ImageStatus(const string& text, Clock& time, const string& imageUrl)
		: Status(text, time), _imageUrl(imageUrl) {}

	const string& getImageUrl() const { return _imageUrl; }

	// when an entity wants to insert a status
	virtual void insertStatus()
	{
		cout << "Please insert your status: ";
		cin.ignore();
		getline(cin, _text);

		cout << "\nPlease enter image's url: ";
		cin >> _imageUrl;
		// todo - add throw catch

		cout << "Image Status uploaded!" << endl;
	}
};

#endif