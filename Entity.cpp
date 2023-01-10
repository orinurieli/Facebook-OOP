#include "Entity.h"
#include <iostream>
using namespace std;
#include "User.h"
#include "Status.h"

void Entity::createStatus()
{
	Status* newStatus = new Status();
	newStatus->getStatusInfo(*newStatus);
	cout << "Status Uploaded!" << endl << endl;
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
