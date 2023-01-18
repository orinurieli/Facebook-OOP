#ifndef __OPERATION_H
#define __OPERATION_H
#include <string>
#include <vector>

#include "Functions.h"
#include "User.h"
#include "Page.h"
#include "Clock.h"

enum eUserChoice {
	AddNewUser = 1, AddNewPage, CreateNewStatus, DisplayAllStatuses, Display10RecentStatusesOfAllFriends, AddNewFriend, Unfriend,
	LikeAPage, UnlikeAPage, DisplayAllEntitiesOfFacebook, DisplayAllFriendsOfUserOrFansOfPage, Exit
};

class Operation
{
private:
	vector<User*> _allUsers;
	vector<Page*> _allPages;
	//int _numOfUsers;
	//int _numOfPages;

public:
	Operation();

	const vector<User*>& getAllUsers() { return _allUsers; };
	const vector<Page*>& getAllPages() { return _allPages; };

	//const int getNumOfPages() const { return _numOfPages; };
	//const int getNumOfUsers() const { return _numOfUsers; };

	void initiateData(vector<User*>& initUsers, vector<Page*>& initPages);
	void addUserToOperation(User& userToAdd);
	void addPageToOperation(Page& pageToAdd);
	void displayAllEntities() const;
	void handleMenu(int userChoice) noexcept(false);

	~Operation();
};

#endif