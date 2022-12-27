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
	cout << endl << "Hey, " << userToAdd->getName() << " Welcome to Facebook :) " << endl << endl;
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
		cout << _allUsers[i]->getName() << endl;

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
		case 1: // Add new user
			getUserInput(this);
			break;
		case 2: // Add new page
			addPageToSystem(this);
			break;
		case 3: // Create a new status
			getUserOrPageInput(3, this);
			break;
		case 4: // Display all statuses
			getUserOrPageInput(4, this);
			break;
		case 5: // Display all 10 recent statuses of all your friends
			cout << endl;
			current_user = askForUsername(this, 0);
			cout << endl;
			if (current_user)
				current_user->displayRecentStatusesOfaFriend(this);
			break;
		case 6: // Add a new friend
			cout << endl;
			current_user = askForUsername(this, 0);
			if (current_user)
				current_user->addFriend(this);

			//todo-> delete later. only for debugging
			/*cout << "\nChecking < operator:\n\n";
			current_user->compareNumOfFriends(*this);*/

			break;
		case 7: // Unfriend
			current_user = askForUsername(this, 0);
			if (current_user)
				current_user->cancelFriendship(*this);
			break;
		case 8: // Like a page
			current_user = askForUsername(this, 0);
			if (current_user)
				current_user->likePage(*this);
			break;
		case 9: // Unlike a page
			current_user = askForUsername(this, 0);
			if (current_user)
				current_user->dislikePage(this);
			break;
		case 10: // Display all entities of Facebook
			displayAllEntities();
			break;
		case 11: // Display all friends of a friend or page
			getUserOrPageInput(11, this);
			break;
		case 12: // Exit
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

	/*for (int i = 0; i < _numOfPages; i++)
	{
		delete[] _allPages[i];
	}
	delete[] _allPages;*/
}