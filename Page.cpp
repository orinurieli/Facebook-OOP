#include <iostream>
using namespace std;

#include "Page.h"

// adds user to fan list
Page& Page::operator+=(User& currentUser)
{
	_friends.push_back(&currentUser);
	return *this;
}

// compare number of fans between two pages
bool Page::operator<(Page& other)
{
	return (_friends.size() < other._friends.size());
}

// compare number of fans between two pages
bool Page::operator>(Page& other)
{
	return (_friends.size() > other._friends.size());
}

// compare the page's number of fans to a user's number of friends
bool Page::operator<(User& currentUser)
{
	return (_friends.size() < currentUser.getFriendsList().size());
}

// compare the page's number of fans to a user's number of friends
bool Page::operator>(User& currentUser)
{
	return (_friends.size() > currentUser.getFriendsList().size());
}

ostream& Page::operator<<(ostream& out) {
	out << getName();
	/*for (int i = 0; i < _frineds.size(); i++) {
		out << " ";
		out << _friends[i].getName();
	}*/

	return out;
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

// receives fan and adds him to the page's fan list
void Page::addFanToPage(Operation& system, User& currentUser)
{
	*this += currentUser;
}

// this function receives pointer to a user and removes it from array of fans.
void Page::removeFan(User& removeUser) throw (const char*)
{
	//int num_of_fans = _fansList.size();
	int num_of_fans = _friends.size();
	bool found = false;

	for (int i = 0; i < num_of_fans && !found; i++)
	{
		//if (&removeUser == _fansList[i]) // user is a fan
		if (&removeUser == _friends[i]) // user is a fan
		{
			if (i != num_of_fans - 1) // if it's not the last - put it last
			{
				//User* tmp = _fansList[i];
				//_fansList[i] = _fansList[num_of_fans - 1];
				//_fansList[num_of_fans - 1] = tmp;

				// switch between them
				User* tmp = _friends[i];
				_friends[i] = _friends[num_of_fans - 1];
				_friends[num_of_fans - 1] = tmp;
			}
			_friends.pop_back(); // delete the last one
			found = true;
		}
	}

	if (!found)
		throw "wait.. the user is not a fan so we can not remove him. \n";
}