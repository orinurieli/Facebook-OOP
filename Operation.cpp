#include <iostream>
using namespace std;
#include <string>
#include "Operation.h"
#include "Functions.h"
class User;
class Page;

Operation::Operation()
{
	//_allUsers.resize(1);
	//_allPages = nullptr;
}

void Operation::initiateData(vector<User*> initUsers, vector<Page*> initPages)
{
	_allUsers = initUsers;
	_allPages = initPages;
	initiateStatuses(this);
}

void Operation::addUserToOperation(User* userToAdd)
{
	_allUsers.push_back(userToAdd);
	/*int i = 0;

	if (_maxUsers == _numOfUsers)
	{
		_maxUsers *= 2;
		vector<User*> newUsers = new User * [_maxUsers];
		for (i = 0; i < _numOfUsers; i++)
			newUsers[i] = _allUsers[i];

		_allUsers = newUsers;
		newUsers = nullptr;
		delete[] newUsers;
	}

	_allUsers[_numOfUsers] = userToAdd;*/
	_numOfUsers++;
	cout << endl << "Hey, " << userToAdd->getUserName() << " Welcome to Facebook :) " << endl << endl;
}

void Operation::addPageToOperation(Page* pageToAdd)
{
	_allPages.push_back(pageToAdd);
	/*int i = 0;

	if (_maxPages == _numOfPages)
	{
		_maxPages *= 2;
		vector<Page*> newPages = new Page * [_maxPages];
		for (i = 0; i < _numOfPages; i++)
			newPages[i] = _allPages[i];

		_allPages = newPages;
	}

	_allPages[_numOfPages] = pageToAdd;*/
	_numOfPages++;

	cout << "Congrats! Your page: " << pageToAdd->getName() << " is Live on Facebook." << endl << endl;
}

void Operation::displayAllEntities()
{
	cout << endl << "ALL ENTITIES: " << endl;

	cout << endl << "Users: " << endl;
	for (int i = 0; i < _numOfUsers; i++)
	{
		cout << _allUsers[i]->getUserName() << endl << "Birthday: ";
		Clock d = _allUsers[i]->getBirthday();
		d.displayDate();
		cout << endl << endl;
	}

	cout << endl << "Pages: " << endl;
	for (int i = 0; i < _numOfPages; i++)
		cout << _allPages[i]->getName() << endl;

	cout << endl;
}

// this function navigates the user's choice from the menu to the relevent functions
void Operation::handleMenu(int userChoice) noexcept(false)
{
	User* current_user = nullptr;
	// todo - think about the "askForUsername" -> code duplicate

	if (userChoice > 0 && userChoice < 13)
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
			getUserOrPageInput2(CreateNewStatus, *this);
			break;
		case DisplayAllStatuses:
			getUserOrPageInput2(DisplayAllStatuses, *this);
			break;
		case Display10RecentStatuses: // Display all 10 recent statuses of all your friends
			cout << endl;
			current_user = askForUsername(*this, USER);
			cout << endl;
			if (current_user)
				current_user->displayRecentStatusesOfaFriend(this);
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
		case DisplayAllENtitiesOfFacebook: // Display all entities of Facebook
			displayAllEntities();
			break;
		case DisplayAllFriends: // Display all friends of a friend or page
			getUserOrPageInput2(11, *this);
			break;
		case Exit:
			cout << "GoodBye";
			exit(1);
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
	/*for (int i = 0; i < _numOfUsers; i++)
	{
		delete[] _allUsers[i];
	}
	delete[] _allUsers;*/

	for (int i = 0; i < _numOfPages; i++) // TODO check it. we allocated each one manually 
	{
		delete _allPages[i];
	}
}