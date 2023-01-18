#include "ImageStatus.h"

// when an entity wants to insert a status
void ImageStatus::insertStatus() throw (const char*)
{
	cout << "Please insert text: ";
	cin.ignore();
	getline(cin, _text);

	int imageChoice;
	cout << "Please enter image's url: ";
	cout << "Choose image (1-4): " << endl;
	cin >> imageChoice;

	if (imageChoice < 1 || imageChoice > 4)
		throw "you can only choose from 1-4.\n";

	switch (imageChoice)
	{
	case 1:
		_imageUrl = "video1.mp4";
		break;
	case 2:
		_imageUrl = "video2.mp4";
		break;
	case 3:
		_imageUrl = "video3.mp4";
		break;
	case 4:
		_imageUrl = "video4.mp4";
		break;
	default:
		break;
	}
	
	cout << "Image Status uploaded!" << endl << endl;
}

// displays the image status
void ImageStatus::display()
{
	cout << "-----------------------------------" << endl;
	cout << "Text: " << _text << endl;
	cout << "Image: " << endl;
	cout << "Uploaded on: ";
	_time.displayDate();
	cout << " | ";
	_time.displayHour();
	cout << endl;
	cout << "-----------------------------------" << endl;
}