#ifndef __USER_H
#define __USER_H
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
using namespace std;
#include "Status.h"
#include "Clock.h"

#define NOT_FOUND -1
#define USER 1
#define FRIEND 2

class Page;
class Operation;
//class Entity;
#include "Entity.h"

class User : public Entity
{
private:
	Clock _birthday;
	vector<Page*> _likedPages;
	//int _numOfPages;
	/*string _name;
	vector <User*> _friendsList;
	vector<Status*> _statuses;
	int _numOfFriends = 0;
	int _numOfStatuses = 0;*/

public:
	User() = delete;
	//User(const string& name, Clock& birthday, int numFriends, int numPages);
	User(const string& name, Clock& birthday) : Entity(name), _birthday(birthday) {}
	User(const User&) = delete; // we delete the copy c'tor because we dont want to duplicate a user

	const string& getUserName() const { return _name; }
	const Clock getBirthday() const { return _birthday; }
	//vector<User*> getFriendsList() const { return _friendsList; }
	vector<User*> getFriendsList() const { return _friends; }
	vector<Page*> getLikedPagesList() { return _likedPages; }
	vector<Status*> getAllStatuses() const { return _statuses; }

	void setUserName(string& username) { _name = username; };
	void setBirthday(Clock& birthday) { _birthday = birthday; }
	void pushToFriendsListInUser(User& newFriend) { _friends.push_back(&newFriend); } // todo delete this?
	void pushToStatusesList(Status& newStatus) { _statuses.push_back(&newStatus); }
	
	void createStatusForUser(Status* status);  // it's a pointer because it can also be null (from initiation)
	void addFriend(Operation& system);
	void cancelFriendship(Operation& system);
	void removeFriendFromFriendList(int indexToRemove);
	void likePage(Operation& system);
	void dislikePage(Operation& system);
	void displayRecentStatusesOfaFriend(Operation& system) const; // 10 most recent statuses of all his friends

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
