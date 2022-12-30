#ifndef __USER_H
#define __USER_H
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
using namespace std;
#include <string.h>
#include "Status.h"
#include "Clock.h"

#define NOT_FOUND -1
#define USER 1
#define FRIEND 2

class Page;
class Operation;

class User
{
	string _name;
	Clock _birthday;
	vector <User*> _friendsList;
	vector<Status*> _statuses;
	vector<Page*> _likedPages;

	int _numOfFriends = 0;
	int _numOfStatuses = 0;
	int _numOfPages = 0;
	//int _maxNumOfFriends = 1;
	//int _maxNumOfStatuses = 1;
	//int _maxNumOfPages = 1;
public:
	User() = delete; // we don't want to create a new user without a name
	//User(const string& name, Clock birthday, int maxNumFriends, int numFriends, int maxPages, int numPages);
	User(const string& name, Clock& birthday, int numFriends, int numPages);
	User(const User&) = delete; // we delete the copy c'tor because we dont want to duplicate a user

	const string& getUserName() const { return _name; }
	vector<User*> getFriendsList() const { return _friendsList; }
	vector<Page*> getLikedPagesList() { return _likedPages; }
	const int getNumOfStatuses() const { return _numOfStatuses; }
	const int getNumOfFriends() const { return _numOfFriends; }
	const int getNumOfPages() const { return _numOfPages; }
	vector<Status*> getAllStatuses() const { return _statuses; }
	const Clock getBirthday() const { return _birthday; }

	void setUserName(string& username) { _name = username; };
	void setBirthday(Clock& birthday) { _birthday = birthday; }

	void pushToFriendsList(User& newFriend) { _friendsList.push_back(&newFriend); }

	void createStatus(Status* status);  // it's a pointer because it can also be null (from initiation)

	void addFriend(Operation& system);
	User& operator+=(User& other);
	bool operator<(const User& other) const;
	bool operator>(const User& other) const;
	bool operator<(const Page& fanPage) const;
	bool operator>(const Page& fanPage) const;

	void cancelFriendship(Operation& system);
	int searchFriendInFriendList(User& other);
	void removeFriendFromFriendList(int indexToRemove);

	void likePage(Operation& system);
	User& operator+=(Page& fanPage);
	bool PageExistInLikedPages(const string& pageName);
	void dislikePage(Operation& system);

	void displayRecentStatusesOfaFriend(Operation& system) const; // 10 most recent statuses of all his friends
	void displayAllStatuses() const;
	void displayAllFriends() const;

	~User();
};

#endif // __USER_H
