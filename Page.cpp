#include <iostream>
using namespace std;

#include "Page.h"

// adds user to fan list
Page& Page::operator+=(User& currentUser)
{
	_fansList.push_back(&currentUser);
	_numOfFans++;
	return *this;
}

// compare number of fans between two pages
bool Page::operator<(Page& other)
{
	return (_numOfFans < other._numOfFans);
}

// compare number of fans between two pages
bool Page::operator>(Page& other)
{
	return (_numOfFans > other._numOfFans);
}

// compare the page's number of fans to a user's number of friends
bool Page::operator<(User& currentUser)
{
	return (_numOfFans < currentUser.getNumOfFriends());
}

// compare the page's number of fans to a user's number of friends
bool Page::operator>(User& currentUser)
{
	return (_numOfFans > currentUser.getNumOfFriends());
}

// ask from user name of a page and checks if the page exists in the system
Page* Page::askForPageName(Operation& system) // *returns a pointer because NULL can be returned*
{
	vector<Page*> allPages = system.getAllPages();
	string page_name;

	cout << "Enter page name: ";
	cin.ignore();
	getline(cin, page_name);

	int index = 0;

	index = doesPageExist(page_name, system);

	if (index >= 0)
		return allPages[index];
	else
		return nullptr;
}

// creates a status for a page
void Page::createStatus(Status* initStatus)
{
	if (initStatus)
		_statuses.push_back(initStatus);
	else // a user creates a new status on his own
	{
		Status* newStatus = new Status();
		newStatus->getStatusInfo(*newStatus);
		_statuses.push_back(newStatus);
		cout << "Status Uploaded!" << endl << endl;
	}
	_numOfStatuses++;
}

// receives fan and adds him to the page's fan list
void Page::addFanToPage(Operation& system, User& currentUser)
{
	*this += currentUser;
}

// this function receives pointer to a user and removes it from array of fans.
void Page::removeFan(User& removeUser) throw (const char*)
{
	int num_of_fans = _fansList.size();
	bool found = false;

	for (int i = 0; i < num_of_fans && !found; i++)
	{
		if (&removeUser == _fansList[i]) // user is a fan
		{
			if (i != num_of_fans - 1) // if it's not the last - put it last
			{
				// switch between them
				User* tmp = _fansList[i];
				_fansList[i] = _fansList[num_of_fans - 1];
				_fansList[num_of_fans - 1] = tmp;
			}

			_fansList.pop_back(); // delete the last one
			_numOfFans--;
			found = true;
		}
	}

	if (!found)
		throw "wait.. the user is not a fan so we can not remove him. \n";
}

void Page::displayAllStatuses() const throw (const char*)
{
	cout << endl << _name << " Statuses: " << endl;
	if (_numOfStatuses == 0) throw "Oops, no statuses to display. \n";
	for (int i = 0; i < _numOfStatuses; i++)
	{
		cout << "-----------------------------------" << endl;
		cout << "Status #" << i + 1 << ":\n";
		cout << "Text: " << _statuses[i]->getText() << endl;
		cout << "Uploaded on: ";
		const Clock& tmp = _statuses[i]->getStatusTime();
		tmp.displayDate();
		cout << " | ";
		const Clock& tmp2 = _statuses[i]->getStatusTime();
		tmp2.displayHour();
		cout << endl << "-----------------------------------" << endl;
	}
	cout << endl;
}

void Page::displayAllFans() const throw (const char*)
{
	cout << endl << _name << " Fans:" << endl;
	if (_numOfFans == 0)
		throw "oops, no fans to display. \n";
	else
	{
		for (int i = 0; i < _numOfFans; i++)
			cout << _fansList[i]->getUserName() << endl;
	}
	cout << endl;
}