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
			cout << "-----------------------------------" << endl;
			cout << "Status #" << i + 1 << endl;
			cout << "Text: " << _statuses[i]->getText() << endl;
			cout << "Uploaded on: ";
			_statuses[i]->getStatusTime().displayDate();
			cout << " | ";
			_statuses[i]->getStatusTime().displayHour();
			cout << endl;
			cout << "-----------------------------------" << endl;
		}
	}
	cout << endl;
}

void Entity::displayAllFriends(int userOrPage) const throw (const char*)
{
	cout << endl << _name << "'s friends:" << endl;

	if (_numOfFriends == 0)
		throw "No friends to display :(";
	else
	{
		cout << endl;
		for (int i = 0; i < _numOfFriends; i++)
		{
			cout << "Friend #" << i + 1 << ":" << endl;
			cout << "Name: " << _friends[i]->getUserName() << endl;
			cout << "Birthday: ";
			_friends[i]->getBirthday().displayDate();
			cout << endl << endl;
		}
	}
}
