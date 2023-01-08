#ifndef __ENTITY_H
#define __ENTITY_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "Status.h"
class User;
//class Status;

class Entity
{
protected:
	string _name;
	vector<User*> _friends;
	vector<Status*> _statuses;
	int _numOfFriends;
	int _numOfStatuses;
public:
	Entity() = delete; // don't want to create entity without information
	Entity(const string& name) : _name(name), _numOfFriends(0), _numOfStatuses(0) {}
	Entity(const Entity& other) = delete; // don't want to clone an entity

	const int getNumOfFriends() const { return _friends.size(); } // todo - do we even need this counter? we have vector
	const int getNumOfStatuses() const { return _statuses.size(); } // todo - same
	const string& getName() const { return _name; }
	vector<User*> getFriendsList() const { return _friends; }
	vector<Status*> getStatusesList() const { return _statuses; }

	void pushToFriendsList(User& newFriend) { _friends.push_back(&newFriend); }
	void pushToStatusesList(Status& newStatus) { _statuses.push_back(&newStatus); }

	void createStatus();
	void displayAllStatuses() const;
	//void displayAllFriends() const;


	//~Entity();
};

#endif
