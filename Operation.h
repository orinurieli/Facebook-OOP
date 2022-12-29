#ifndef __OPERATION_H
#define __OPERATION_H

#include <vector>
using namespace std;

#include "User.h"
#include "Page.h"
#include "Clock.h"

enum eUserChoice{AddNewUser=1, AddNewPage, CreateNewStatus, DisplayAllStatuses, Display10RecentStatuses, AddNewFriend, Unfriend, 
LikeAPage, UnlikeAPage, DisplayAllENtitiesOfFacebook, DisplayAllFriends, Exit};

class Operation
{
private:
	vector<User*> _allUsers;
	vector<Page*> _allPages;

	// numbers according to init data
	int _numOfUsers = 5;
	int _maxUsers = 8;
	int _numOfPages = 5;
	int _maxPages = 8;

public:
	Operation();
	void initiateData(vector<User*> users, vector<Page*> pages);
	void handleMenu(int userChoice);

	vector<User*> getAllUsers() { return _allUsers; };
	vector<Page*> getAllPages() { return _allPages; };
	const int getNumOfPages() const { return _numOfPages; };
	const int getNumOfUsers() const { return _numOfUsers; };

	void addUserToOperation(User* user);
	void addPageToOperation(Page* page);
	void displayAllEntities();

	~Operation();
};

#endif // __OPERATION_H