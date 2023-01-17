#include "VideoStatus.h"

// to create a new video status
void VideoStatus::insertStatus()
{
	int videoChoice;

	cout << "Please insert text: ";
	cin.ignore();
	getline(cin, _text);

	cout << "Please insert Video path." << endl;
	//cout << "Choose between video1.mp4 - video5.mp4:  " << endl;
	cout << "Choose video (1-4): " << endl;
	cin >> videoChoice;

	// todo - throw catch

	// todo - fix later
	switch (videoChoice)
	{
	case 1:
		_videoUrl = "video1.mp4";
		break;
	case 2:
		_videoUrl = "video2.mp4";
		break;
	case 3:
		_videoUrl = "video3.mp4";
		break;
	case 4:
		_videoUrl = "video4.mp4";
		break;
	default:
		break;
	}
	cout << "Video Status Uploaded!" << endl << endl;
}

// this function displays the video status
void VideoStatus::display() throw(const char*)
{
	cout << "-----------------------------------" << endl;
	cout << "Text: " << _text << endl;
	// show video?

	string command = "start " + _videoUrl;
	int result = system(command.c_str());

	if (result != 0)
		throw "Error displaying video";

	cout << "Uploaded on: ";
	_time.displayDate();
	cout << " | ";
	_time.displayHour();
	cout << endl;
	cout << "-----------------------------------" << endl;
}