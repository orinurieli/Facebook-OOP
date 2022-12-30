#include <iostream>
using namespace std;

#include "Page.h"
//class User;
//class Status;

//Page::Page(const char* name)
//{
	//_name = new char[MAX_CHARACTERS];
	//_name = _strdup(name);

	//_fansList.resize(1);
	//_statuses = new Status * [1];
//}

// creates a status for a page
void Page::createStatus()
{
	/*if (_maxStatuses == _numOfStatuses)
	{
		_maxStatuses *= 2;
		Status
			newStatuses = new Status * [_maxStatuses];
		for (int i = 0; i < _numOfStatuses; i++)
			newStatuses[i] = _statuses[i];

		delete[] _statuses;
		_statuses = newStatuses;
	}*/

	Status* newStatus = new Status();
	newStatus->getStatusInfo(*newStatus);
	_statuses.push_back(newStatus);
	cout << "Status Uploaded!" << endl << endl;
	_numOfStatuses++;
}

void Page::displayAllStatuses() throw (const char*)
{
	cout << endl << _name << " Statuses: " << endl;
	if (_numOfStatuses == 0) throw "Oops, no statuses to display. \n";
	for (int i = 0; i < _numOfStatuses; i++)
	{
		cout << "-----------------------------------" << endl;
		cout << "Status #" << i + 1 << ":\n";
		cout << "Text: " << _statuses[i]->getText() << endl;
		cout << "Uploaded on: ";
		//_statuses[i]->getDateAndHour().displayDate();
		// _statuses[i]->getStatusTime().displayDate();
		const Clock& tmp = _statuses[i]->getStatusTime();
		tmp.displayDate();
		cout << " | ";
		//_statuses[i]->getDateAndHour().displayHour();
		//_statuses[i]->getStatusTime().displayHour();
		const Clock& tmp2 = _statuses[i]->getStatusTime();
		tmp2.displayHour();
		cout << endl << "-----------------------------------" << endl << endl;
	}
	cout << endl;
}

void Page::displayAllFans() throw (const char*)
{
	cout << endl << _name << " Fans:\n";

	if (_numOfFans == 0)
		throw "oops, no fans to display. \n";
	else {
		for (int i = 0; i < _numOfFans; i++)
			cout << _fansList[i]->getUserName() << endl;
	}

	cout << endl;
}

// ################## like page ############## //
// receives fan and adds him to the page's fan list
void Page::addFanToPage(Operation& system, User& currentUser)
{
	*this += currentUser;
}

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

// ################## unlike page ############## //
// this function receives pointer to a user and removes it from array of fans.
void Page::removeFan(User* removeUser) throw (const char*)
{
	for (int i = 0; i < _numOfFans; i++)
	{
		if (removeUser == _fansList[i]) // user is a fan
		{
			// page is the only one on the array, or it is the last one on the array
			if (i == _numOfFans - 1)
				_fansList[i] = nullptr;
			else
			{
				_fansList[i] = _fansList[_numOfFans - 1];
				_fansList[_numOfFans - 1] = nullptr;
			}
			_numOfFans--;
		}
		else throw "wait.. the user is not a fan so we can not remove him. \n";
	}
}

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

Page::~Page()
{
	//delete[] _name;

	/*for (int i = 0; i < _numOfStatuses; i++)
	{
		delete[] _statuses[i];
	}
	delete[] _statuses;*/

	/*for (int i = 0; i < _numOfFans; i++)
	{
		delete[] _fansList[i];
	}
	delete[] _fansList;*/
}