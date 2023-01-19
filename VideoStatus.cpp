#include "VideoStatus.h"

// to create a new video status
void VideoStatus::insertStatus() throw (const char*)
{
	int videoChoice;

	cout << "Please insert text: ";
	cin.ignore();
	getline(cin, _text);

	cout << "Please insert Video path:" << endl;
	cout << "Choose video (1-4): " << endl;
	cin >> videoChoice;

	if (videoChoice < 1 || videoChoice > 4)
		throw "you can only choose from 1-4.\n";

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
	cout << "Video: " << _videoUrl << endl;
	cout << "Uploaded on: ";
	_time.displayDate();
	cout << " | ";
	_time.displayHour();
	cout << endl;
	cout << "-----------------------------------" << endl;
}