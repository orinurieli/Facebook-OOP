#ifndef __OPERATION_H
#define __OPERATION_H
#include <string>
#include <vector>
#include <fstream>
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
public:
	Operation();

	const vector<User*>& getAllUsers() { return _allUsers; };
	const vector<Page*>& getAllPages() { return _allPages; };

	void initiateData(vector<User*>& initUsers, vector<Page*>& initPages);
	void addUserToOperation(User& userToAdd);
	void addPageToOperation(Page& pageToAdd);
	void displayAllEntities() const;
	void handleMenu(int userChoice) noexcept(false);

	User* searchUserInOperation(const string& name); // *can return null!*
	Page* searchPageInOperation(const string& name); // *can return null!*
	void storeObjects(const string& filename);
	void readObjects(const string& filename);

	void writeAllUsersAndPagesToFile(ostream& out);
	void writeEachUsersDetails(ostream& out);
	void writeEachPagesDetails(ostream& out);
	void writeFriendsOrFansToFile(ostream& out, Entity& entity);
	void writePagesToFile(ostream& out, User& user);
	void writeStatusesToFile(ostream& out, Entity& entity);


	~Operation();
};

#endif