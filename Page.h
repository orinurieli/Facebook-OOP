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
	//Page(const string& name) : _name(name) {}

	/*const string& getName() const { return _name; };
	const int getNumOfFans() const { return _numOfFans; };
	const int getMaxNumOfFans() const { return _numOfFans; }
	vector<User*> getFanList() const { return _fansList; }
	bool setPageName(const string& name) { _name = name; };
	bool setNumOfFans(int newNumOfFans) { _numOfFans = newNumOfFans; };*/

	Page() = delete; // don't want to create a page without data
	Page(const Page* page) = delete; // prevent duplicate
	Page(const string& name) : Entity(name) {}

	Page& operator+=(User& currentUser);
	bool operator<(Page& other);
	bool operator>(Page& other);
	bool operator<(User& currentUser);
	bool operator>(User& currentUser);
	ostream& operator<<(ostream& out);
	istream& operator>>(istream& in);

	Page* askForPageName(Operation& system); // *returns a pointer because NULL can be returned*
	void addFanToPage(Operation& system, User& currentUser);
	void removeFan(User& removeUser);

	~Page() {};
};

#endif