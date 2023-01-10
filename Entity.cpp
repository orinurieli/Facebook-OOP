#include "Entity.h"
#include <iostream>
using namespace std;
#include "User.h"
#include "Status.h"

void Entity::createStatus()
{
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

	Status* newStatus = new Status();
	newStatus->getStatusInfo(*newStatus);
	_statuses.push_back(newStatus);
	cout << "Status Uploaded!" << endl << endl;
	_numOfStatuses++;
}

void Entity::displayAllStatuses() const
{
	int num_of_statuses = getNumOfStatuses();

	cout << endl << _name << "'s Statuses:\n";
	if (num_of_statuses == 0)
		cout << "None." << endl << endl;
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
