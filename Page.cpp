#include <iostream>
using namespace std;

#include "Page.h"
#include "Operation.h"


// ask from user name of a page and checks if the page exists in the system
Page* Page::askForPageName(Operation& system) // *returns a pointer because NULL can be returned*
{
	vector<Page*> allPages = system.getAllPages();
	string page_name;

	cout << "Enter page name: ";
	cin.ignore();
	getline(cin, page_name);

	Page* page = searchPageByName(page_name, system);
	return page;
}

// adds user to fan list
Page& Page::operator+=(User& currentUser)
{
	_friends.push_back(&currentUser);
	return *this;
}

// this function receives pointer to a user and removes it from array of fans.
void Page::removeFan(const User& removeUser) throw (const char*)
{
	int num_of_fans = _friends.size();
	bool found = false;

	for (int i = 0; i < num_of_fans && !found; i++)
	{
		if (&removeUser == _friends[i]) // user is a fan
		{
			if (i != num_of_fans - 1) // if it's not the last - put it last
			{
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