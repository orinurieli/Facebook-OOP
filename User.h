#ifndef __USER_H
#define __USER_H
#define _CRT_SECURE_NO_WARNINGS


#include <vector>
using namespace std;
#include <string.h>
#include "Status.h"
#include "Clock.h"

class Page;
class Operation;

class User
{
	char* _name;
	Clock _birthday;
	vector <User*> _friendsList;
	vector<Status*> _statuses;
	vector<Page*> _likedPages;

	int _numOfFriends = 0;
	int _maxNumOfFriends = 1;
	int _numOfStatuses = 0;
	int _maxNumOfStatuses = 1;
	int _numOfPages = 0;
	int _maxNumOfPages = 1;
public:
	User() = delete; // we don't want to create a new user without a name
	User(const char* name, Clock birthday, int maxNumFriends, int numFriends, int maxPages, int numPages);
	User(const User&) = delete; // we delete the copy c'tor because we dont want to duplicate a user

	const char* getName() const { return _name; }
	vector<User*> getFriendsList() { return _friendsList; }
	void pushToFriendsList(User* newFriend) { _friendsList.push_back(newFriend); }
	vector<Page*> getLikedPagesList() { return _likedPages; }
	const int getNumOfStatuses() const { return _numOfStatuses; }
	const int getNumOfFriends() const { return _numOfFriends; }
	const int getNumOfPages() const { return _numOfPages; }
	vector<Status*> getAllStatuses() { return _statuses; }
	const Clock getBirthday() const { return _birthday; }
	void setName(char* username) { _name = username; };
	void setBirthday(Clock birthday) { _birthday = birthday; }

	void createStatus(Status* status);

	void addFriend(Operation* system);
	User* operator+=(User* other);

	void cancelFriendship(Operation& system);
	int searchFriendInFriendList(User& other);
	void removeFriendFromFriendList(int indexToRemove);

	void likePage(Operation& system);
	User* operator+=(Page* fanPage);

	void dislikePage(Operation* system);

	void displayRecentStatusesOfaFriend(Operation* system); // 10 most recent statuses of all his friends
	void displayAllStatuses();
	void displayAllFriends();

	/*void reallocStatuses();
	void reallocFriendList();
	void reallocPagesList();*/

	~User();


	// todo - check if we need these funcs
	int askForName(Operation* system, int flag);
	void likePageTemp(Page* pageToLike, Operation* system);
	void addPageToLikedPagesList(Operation* system, Page* pageToLike);
};

#endif // __USER_H
