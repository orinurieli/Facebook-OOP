#ifndef __ENTITY_H
#define __ENTITY_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class User;
class Status;

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
	vector<User*> getFriendsList() const { return _friends; }
	vector<Status*> getStatusesList() const { return _statuses; }

	void pushToFriendsList(User& newFriend)	{_friends.push_back(&newFriend);}
	void pushToStatusesList(Status& newStatus){	_statuses.push_back(&newStatus); }

	void createStatus();
	void displayAllStatuses() const;
	void displayAllFriendsOrFans(int userOrPage) const;


	//~Entity();
};

#endif
