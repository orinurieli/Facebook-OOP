#ifndef __ENTITY_H
#define __ENTITY_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class User;
class Status;

enum StatusType { textStatus = 1, imageStatus, videoStatus };
#define NOT_FOUND -1
#define USER 1
#define PAGE 0

class Entity
{
protected:
	string _name;
	vector<User*> _friends;
	vector<Status*> _statuses;
public:
	Entity() = delete; // don't want to create entity without information
	Entity(const string& name) : _name(name) {}
	Entity(const Entity& other) = delete; // don't want to clone an entity

	const string& getName() const { return _name; }
	const vector<User*>& getFriendsList() const { return _friends; }
	const vector<Status*>& getStatusesList() const { return _statuses; }
	void pushToFriendsList(User& newFriend) { _friends.push_back(&newFriend); }
	void pushToStatusesList(Status* newStatus) { _statuses.push_back(newStatus); }
	int searchMemberInFriendList(const User& friendToSearch);
	void createStatus();
	void displayAllStatuses() const;
	void displayAllFriendsOrFans(int userOrPage) const;

	virtual ~Entity() {}
};

#endif
