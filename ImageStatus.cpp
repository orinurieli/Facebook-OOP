#include "ImageStatus.h"

// when an entity wants to insert a status
void ImageStatus::insertStatus()
{
	cout << "Please insert text: ";
	cin.ignore();
	getline(cin, _text);

	cout << "Please enter image's url: ";
	cin >> _imageUrl;
	// todo - add throw catch ??

	cout << "Image Status uploaded!" << endl << endl;
}

// displays the image status
void ImageStatus::display()
{
	cout << "-----------------------------------" << endl;
	cout << "Text: " << _text << endl;
	// show image? ??
	cout << "Uploaded on: ";
	_time.displayDate();
	cout << " | ";
	_time.displayHour();
	cout << endl;
	cout << "-----------------------------------" << endl;
}