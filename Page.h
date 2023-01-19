#ifndef __PAGE_H
#define __PAGE_H

#include <vector>
#include <string>
using namespace std;
#include "User.h"
#include "Entity.h"
class Operation;

class Page : public Entity
{
public:
	Page() : Entity(" ") {}; // in order to read pages from the file
	Page(const Page& page) = delete; // prevent duplicate
	Page(const string& name) : Entity(name) {}

	Page& operator+=(User& currentUser);
	bool operator<(Page& other) { return (_friends.size() < other._friends.size()); } // compare number of fans between two pages
	bool operator>(Page& other) { return (_friends.size() > other._friends.size()); } // compare number of fans between two pages
	bool operator<(User& currentUser) { return (_friends.size() < currentUser.getFriendsList().size()); } // compare the page's number of fans to a user's number of friends
	bool operator>(User& currentUser) { return (_friends.size() > currentUser.getFriendsList().size()); } // compare the page's number of fans to a user's number of friends
	friend ostream& operator<<(ostream& out, const Page& page);
	friend istream& operator>>(istream& in, Page& page);

	Page* askForPageName(Operation& system); // *returns a pointer because NULL can be returned*
	void removeFan(const User& removeUser);

	~Page() {};
};

#endif