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
public:
	User() = delete; // we don't want to create a new user without a name
	User(const string& name, Clock& birthday, int numFriends, int numPages);
	User(const User&) = delete; // we delete the copy c'tor because we dont want to duplicate a user

	const int getNumOfStatuses() const { return _numOfStatuses; }
	const int getNumOfFriends() const { return _numOfFriends; }
	const int getNumOfPages() const { return _numOfPages; }
	const string& getUserName() const { return _name; }
	const Clock getBirthday() const { return _birthday; }
	vector<User*> getFriendsList() const { return _friendsList; }
	vector<Page*> getLikedPagesList() { return _likedPages; }
	vector<Status*> getAllStatuses() const { return _statuses; }

	void setUserName(string& username) { _name = username; };
	void setBirthday(Clock& birthday) { _birthday = birthday; }
	void pushToFriendsList(User& newFriend) { _friendsList.push_back(&newFriend); }
	void createStatus(Status* status);  // it's a pointer because it can also be null (from initiation)
	void addFriend(Operation& system);
	void cancelFriendship(Operation& system);
	void removeFriendFromFriendList(int indexToRemove);
	void likePage(Operation& system);
	void dislikePage(Operation& system);
	void displayRecentStatusesOfaFriend(Operation& system) const; // 10 most recent statuses of all his friends
	void displayAllStatuses() const;
	void displayAllFriends() const;

	User& operator+=(User& other);
	User& operator+=(Page& fanPage);

	bool operator<(const User& other) const;
	bool operator>(const User& other) const;
	bool operator<(const Page& fanPage) const;
	bool operator>(const Page& fanPage) const;
	bool PageExistInLikedPages(const string& pageName);
	int searchFriendInFriendList(User& other);

	~User();
};

#endif // __USER_H
