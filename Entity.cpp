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

	Status* newStatus;

	switch (status_type_choice)
	{
	case textStatus:
	{
		newStatus = new TextStatus();
		dynamic_cast<TextStatus*>(newStatus)->insertStatus();
		//_statuses.push_back(newStatus);
		break;
	}
	case imageStatus:
	{
		newStatus = new ImageStatus();
		dynamic_cast<ImageStatus*>(newStatus)->insertStatus();
		//_statuses.push_back(newStatus);
		break;
	}
	case videoStatus:
	{
		newStatus = new VideoStatus();
		dynamic_cast<VideoStatus*>(newStatus)->insertStatus();
		//_statuses.push_back(newStatus);
		break;
	}
	default:
		break;
	}

	_statuses.push_back(newStatus);
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
