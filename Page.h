#ifndef __PAGE_H
#define __PAGE_H
#include <vector>
#include <string>
using namespace std;

#include "Status.h"
#include "User.h"
#include "Functions.h"

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
public:
	Page() = delete;
	Page(const string& name) : _name(name) {}
	Page(const Page* page) = delete; // prevent duplicate

	const string& getName() const { return _name; };
	const int getNumOfFans() const { return _numOfFans; };
	const int getMaxNumOfFans() const { return _numOfFans; }
	vector<User*> getFanList() const { return _fansList; }
	bool setPageName(const string& name) { _name = name; };
	bool setNumOfFans(int newNumOfFans) { _numOfFans = newNumOfFans; };

	Page& operator+=(User& currentUser);
	bool operator<(Page& other);
	bool operator>(Page& other);
	bool operator<(User& currentUser);
	bool operator>(User& currentUser);

	Page* askForPageName(Operation& system); // *returns a pointer because NULL can be returned*
	void createStatus(Status* initStatus); // *pointer because it can also be null*
	void addFanToPage(Operation& system, User& currentUser);
	void removeFan(User& removeUser);
	void displayAllStatuses() const;
	void displayAllFans() const;

	~Page() {};
};

#endif