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
	Page() = delete; // don't want to create a page without data
	Page(const Page& page) = delete; // prevent duplicate
	Page(const string& name) : Entity(name) {}

	Page& operator+=(User& currentUser);
	bool operator<(const Page& other) { return (_friends.size() < other._friends.size()); } // compare number of fans between two pages
	bool operator>(const Page& other) {return (_friends.size() > other._friends.size()); } // compare number of fans between two pages
	bool operator<(const User& currentUser) { return (_friends.size() < currentUser.getFriendsList().size()); } // compare the page's number of fans to a user's number of friends
	bool operator>(const User& currentUser) { return (_friends.size() > currentUser.getFriendsList().size()); } // compare the page's number of fans to a user's number of friends
	ostream& operator<<(ostream& out);
	istream& operator>>(istream& in);

	Page* askForPageName(Operation& system); // *returns a pointer because NULL can be returned*
	void removeFan(const User& removeUser);

	~Page() {};
};

#endif