#ifndef __PAGE_H
#define __PAGE_H

//class User;
//class Status;
#include <vector>
#include <string>
using namespace std;

#include "Status.h"
#include "User.h"

class Page
{
private:
	string _name;
	vector<User*> _fansList;
	vector<Status*>_statuses;
	int _numOfFans = 0;
	int _maxFans = 2;
	int _numOfStatuses = 0;
	int _maxStatuses = 1;

public:
	Page() = delete; // we don't want to create a new page without a page name
	//Page(string& name) : _name(name) {} // TODO gon check if this ctor works
	Page(const string name)
	{
		this->_name = name;
	}
	Page(const Page* page) = delete; // prevent duplicate

	//const char* getName() const { return _name; };
	const string& getName() const { return _name; };
	const int getNumOfFans() const { return _numOfFans; };
	const int getMaxNumOfFans() const { return _numOfFans; };
	vector<User*> getFanList() const { return _fansList; } // todo change to ref
	bool setPageName(const string& name) { _name = name; };
	bool setNumOfFans(int newNumOfFans) { _numOfFans = newNumOfFans; };

	void addFanToPage(Operation& system, User& currentUser);
	Page& operator+=(User& currentUser);
	bool operator<(Page& other);
	bool operator>(Page& other);
	bool operator<(User& currentUser);
	bool operator>(User& currentUser);

	//void reallocFanList();

	void removeFan(User* removeUser);
	void createStatus();
	void displayAllStatuses();
	void displayAllFans();

	~Page();
};

#endif