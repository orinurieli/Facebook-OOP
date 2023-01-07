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
	Entity(const string& name, int numFriends, int numStatuses) : _name(name), _numOfFriends(numFriends), _numOfStatuses(numStatuses) {}
	Entity(const Entity& other) = delete; // don't want to clone an entity

	const int getNumOfStatuses() const { return _numOfStatuses; }
	const int getNumOfFriends() const { return _numOfFriends; }
	const string& getName() const { return _name; }
	vector<User*> getFriendsList() const { return _friends; }
	vector<Status*> getStatusesList() const { return _statuses; }

	void createStatus();
	




	//displayStatuses
	//displayFriends/Fans


	//~Entity();
};

#endif
