#include "Entity.h"
#include <iostream>
using namespace std;
#include "User.h"
#include "Status.h"


#include "TextStatus.h"
#include "ImageStatus.h"
#include "VideoStatus.h"


void Entity::createStatus() throw (const char*)
{
	int status_type_choice;
	cout << "Please choose what kind of status to upload:" << endl;
	cout << "1 - Text Status" << endl << "2 - Image Status" << endl << "3 - Video Status" << endl;
	cin >> status_type_choice;

	if (status_type_choice < 1 || status_type_choice > 3)
		throw "Invalid Choice!\n";

	switch (status_type_choice)
	{
	case textStatus:
	{
		Status* newStatus = new TextStatus();
		dynamic_cast<TextStatus*>(newStatus)->insertStatus();
		_statuses.push_back(newStatus);
		break;
	}
	case imageStatus:
	{
		Status* newStatus = new ImageStatus();
		dynamic_cast<ImageStatus*>(newStatus)->insertStatus();
		_statuses.push_back(newStatus);
		break;
	}
	case videoStatus:
	{
		Status* newStatus = new VideoStatus();
		dynamic_cast<VideoStatus*>(newStatus)->insertStatus();
		_statuses.push_back(newStatus);
		break;
	}
	default:
		break;
	}

	/*Status* newStatus = new Status();
	newStatus->getStatusInfo(*newStatus);
	_statuses.push_back(newStatus);
	cout << "Status Uploaded!" << endl << endl;*/

	// todo: let the user choose between:
	// 1 - text status
	// 2 - image status
	// 3 - video status

	/*
	* Example
	* user chose: 3
	* Status* newStatus = new VideoStatus();
	* newStatus->getStatusInfo(*newStatus); // using Polymorphizem
	* _statuses.push_back(newStatus);
	*/

	// new Status appears in initiate statuses

	
}

void Entity::displayAllStatuses() const throw (const char*)
{
	int num_of_statuses = _statuses.size();

	cout << endl << _name << "'s Statuses:\n";
	if (num_of_statuses == 0)
		throw "No statuses to display :(";
	else
	{
		for (int i = 0; i < num_of_statuses; i++)
		{
			cout << "Status #" << i + 1 << endl;
			_statuses[i]->display();
		}
	}
	cout << endl;
}

void Entity::displayAllFriendsOrFans(int userOrPage) const throw (const char*)
{
	cout << endl << _name << "'s friends:" << endl;
	int _numOfFriends = _friends.size();

	if (_numOfFriends == 0)
		throw "No friends to display :(";
	else
	{
		cout << endl;
		for (int i = 0; i < _numOfFriends; i++)
		{
			(userOrPage == USER) ? (cout << "Friend #") : (cout << "Fan #");
			cout << i + 1 << ":" << endl;
			cout << "Name: " << _friends[i]->getUserName() << endl;
			cout << "Birthday: ";
			_friends[i]->getBirthday().displayDate();
			cout << endl << endl;
		}
	}
}
