#ifndef __USER_H
#define __USER_H
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <string>
using namespace std;

#define NOT_FOUND -1
#define USER 1
#define FRIEND 2

#include "Entity.h"
#include "TextStatus.h"
#include "ImageStatus.h"
#include "VideoStatus.h"
#include "Status.h"
class Operation;
class Page;

class User : public Entity
{
private:
	Clock _birthday;
	vector<Page*> _likedPages;

public:
	User() = delete;
	User(const string& name, Clock& birthday) : Entity(name), _birthday(birthday) {}
	User(const User&) = delete; // we delete the copy c'tor because we dont want to duplicate a user

	const Clock& getBirthday() const { return _birthday; }
	const vector<Page*>& getLikedPagesList() const { return _likedPages; }
	void setBirthday(Clock& birthday) { _birthday = birthday; }

	void addFriend(Operation& system);
	void cancelFriendship(Operation& system);


	void likePage(Operation& system);
	void dislikePage(Operation& system);
	void displayRecentStatusesOfaFriend(Operation& system) const; // 10 most recent statuses of all his friends

	User& operator+=(User& other);
	User& operator+=(Page& fanPage);
	ostream& operator<<(ostream& out);
	istream& operator>>(istream& in);

	bool operator<(const User& other) const;
	bool operator>(const User& other) const;
	bool operator<(const Page& fanPage) const;
	bool operator>(const Page& fanPage) const;
	bool PageExistInLikedPages(const string& pageName);

	~User();
};

#endif
