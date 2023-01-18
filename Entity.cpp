#include "Entity.h"
#include <iostream>
using namespace std;
#include "User.h"
#include "Status.h"
#include "TextStatus.h"
#include "ImageStatus.h"
#include "VideoStatus.h"

// searches in friends list (of either a user or a pgae) for a certain user. returns the friend's index, or -1 
int Entity::searchMemberInFriendList(const User& friendToSearch)
{
	int friend_to_delete_index = NOT_FOUND;
	int num_of_friends = _friends.size();

	if (num_of_friends > 0) // if user has friends 
	{
		for (int i = 0; i < num_of_friends && friend_to_delete_index == NOT_FOUND; i++)
		{
			if (_friends[i]->_name.compare(friendToSearch._name) == 0)
				friend_to_delete_index = i;
		}
	}
	return friend_to_delete_index;
}

// this function creates a new status to a user or a page
void Entity::createStatus() throw (const char*)
{
	int status_type_choice;
	cout << "Please choose what kind of status to upload:" << endl;
	cout << textStatus << " - Text Status" << endl << imageStatus << " - Image Status" << endl << videoStatus << " - Video Status" << endl;
	cin >> status_type_choice;

	if (status_type_choice < textStatus || status_type_choice > videoStatus)
		throw "Invalid Choice!\n";

	Status* newStatus;

	switch (status_type_choice)
	{
	case textStatus:
	{
		newStatus = new TextStatus();
		dynamic_cast<TextStatus*>(newStatus)->insertStatus();
		break;
	}
	case imageStatus:
	{
		newStatus = new ImageStatus();
		dynamic_cast<ImageStatus*>(newStatus)->insertStatus();
		break;
	}
	case videoStatus:
	{
		newStatus = new VideoStatus();
		dynamic_cast<VideoStatus*>(newStatus)->insertStatus();
		break;
	}
	default:
		break;
	}

	_statuses.push_back(newStatus);
}

// this function displays all statuses of a certain member (a page or a user)
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

// this function displays all friends of a certain member (a page or a user)
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
			cout << "Name: " << _friends[i]->_name << endl;
			cout << "Birthday: ";
			_friends[i]->getBirthday().displayDate();
			cout << endl << endl;
		}
	}
}
