#pragma once

#include <iostream>
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

	virtual void getStatusInfo(Status& newStatus)
	{
		string text;
		string path;

		cout << "Please insert your status: ";
		getline(cin, text);
		//newStatus._text = text;

		cout << "Please insert Video path." << endl;
		cout << "Choose between video1.mp4 - video5.mp4:  " << endl;
		getline(cin, path);
	}

	void displayVideo() throw(const char*)
	{
		string command = "start " + _videoUrl;
		int result = system(command.c_str());

		if (result != 0)
			throw "Error displaying video";
	};

}
