#ifndef __PAGE_H
#define __PAGE_H
#include <vector>
#include <string>
using namespace std;

#include "Status.h"
#include "User.h"
#include "Functions.h"
//#include "Operation.h"

class User;
class Status;

class Page
{
private:
	string _name;
	vector<User*> _fansList;
	vector<Status*>_statuses;
	int _numOfFans = 0;
	int _numOfStatuses = 0;
	//int _maxFans = 2; // needs to be deleted?
	//int _maxStatuses = 1;

public:
	Page() = delete; // we don't want to create a new page without a page name
	Page(const string& name) { this->_name = name; } //  : _name(name)
	Page(const Page* page) = delete; // prevent duplicate

	const string& getName() const { return _name; };
	const int getNumOfFans() const { return _numOfFans; };
	const int getMaxNumOfFans() const { return _numOfFans; };
	vector<User*> getFanList() const { return _fansList; } // todo change to ref
	bool setPageName(const string& name) { _name = name; };
	bool setNumOfFans(int newNumOfFans) { _numOfFans = newNumOfFans; };

	Page& operator+=(User& currentUser);
	bool operator<(Page& other);
	bool operator>(Page& other);
	bool operator<(User& currentUser);
	bool operator>(User& currentUser);

	void addFanToPage(Operation& system, User& currentUser);
	void removeFan(User* removeUser);
	void createStatus();
	void displayAllStatuses();
	void displayAllFans();
	Page* askForPageName(Operation& system);

	~Page();
};

#endif