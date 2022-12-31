#include <iostream>
using namespace std;

#include "Operation.h"

// c'tor
Operation::Operation()
{
	_numOfUsers = 5;
	_numOfPages = 5;

	initiateData(_allUsers, _allPages);
}

// initiate the program with users and pages
void Operation::initiateData(vector<User*> initUsers, vector<Page*> initPages)
{
	_allUsers = initiateUsers();
	_allPages = initiatePages(*this, _allUsers);
	initiateStatuses(*this);
}

// insert a new user to the allUsers vector
void Operation::addUserToOperation(User& userToAdd)
{
	_allUsers.push_back(&userToAdd);
	_numOfUsers++;
	cout << endl << "Hey, " << userToAdd.getUserName() << " Welcome to Facebook :) " << endl << endl;
}

// insert a new page to the allPages vector
void Operation::addPageToOperation(Page& pageToAdd)
{
	_allPages.push_back(&pageToAdd);
	_numOfPages++;
	cout << "Congrats! Your page: " << pageToAdd.getName() << " is Live on Facebook." << endl << endl;
}

// prints out all the entities on facebook, the users and pages
void Operation::displayAllEntities() const
{
	cout << endl << "ALL ENTITIES: " << endl;

	cout << endl << "Users: " << endl << "------" << endl;

	for (int i = 0; i < _numOfUsers; i++)
	{
		cout << _allUsers[i]->getUserName() << endl << "Birthday: ";
		Clock b = _allUsers[i]->getBirthday();
		b.displayDate();
		cout << endl << endl;
	}

	cout << endl << "Pages: " << endl << "------" << endl;
	for (int i = 0; i < _numOfPages; i++)
		cout << _allPages[i]->getName() << endl;

	cout << endl;
}

// this function navigates the user's choice from the menu to the relevent functions
void Operation::handleMenu(int userChoice) noexcept(false)
{
	User* current_user = nullptr;

	if (userChoice > 0 && userChoice < Exit)
	{
		switch (userChoice)
		{
		case AddNewUser:
			getUserInput(*this);
			break;
		case AddNewPage:
			addPageToSystem(*this);
			break;
		case CreateNewStatus:
			getUserOrPageInput(CreateNewStatus, *this);
			break;
		case DisplayAllStatuses:
			getUserOrPageInput(DisplayAllStatuses, *this);
			break;
		case Display10RecentStatusesOfAllFriends:
			cout << endl;
			current_user = askForUsername(*this, USER);
			cout << endl;
			if (current_user)
				current_user->displayRecentStatusesOfaFriend(*this);
			break;
		case AddNewFriend:
			cout << endl;
			current_user = askForUsername(*this, USER);
			if (current_user)
				current_user->addFriend(*this);
			break;
		case Unfriend:
			current_user = askForUsername(*this, USER);
			if (current_user)
				current_user->cancelFriendship(*this);
			break;
		case LikeAPage:
			current_user = askForUsername(*this, USER);
			if (current_user)
				current_user->likePage(*this);
			break;
		case UnlikeAPage:
			current_user = askForUsername(*this, USER);
			if (current_user)
				current_user->dislikePage(*this);
			break;
		case DisplayAllEntitiesOfFacebook:
			displayAllEntities();
			break;
		case DisplayAllFriendsOfUserOrFansOfPage:
			getUserOrPageInput(11, *this);
			break;
		default:
			break;
		}
	}
	else {
		throw invalid_argument("Invalid Menu Choice! Please choose between 1-12.");
		return;
	}
}

Operation::~Operation()
{
	for (int i = 0; i < _numOfUsers; i++)
		delete _allUsers[i];

	for (int i = 0; i < _numOfPages; i++)
		delete _allPages[i];
}