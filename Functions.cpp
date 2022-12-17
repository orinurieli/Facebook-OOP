#include <iostream>
#include "Functions.h"
using namespace std;

#define NOT_FOUND -1

// fills allUsers array with members
User** initiateUsers()
{
	User** initUsers = new User * [5];

	User* user1 = new User("Keren Kalif", Clock(15, 4, 1990), 2, 2, 2, 1);
	initUsers[0] = user1;
	User* user2 = new User("Steve Jobs", Clock(24, 2, 1955), 2, 2, 2, 1);
	initUsers[1] = user2;
	User* user3 = new User("Mark Zuckerberg", Clock(14, 5, 1984), 4, 3, 2, 2);
	initUsers[2] = user3;
	User* user4 = new User("Ori Nurieli", Clock(1, 7, 1997), 2, 1, 4, 3);
	initUsers[3] = user4;
	User* user5 = new User("Gon Etgar", Clock(21, 10, 1996), 2, 2, 4, 3);
	initUsers[4] = user5;

	initiateFriendships(initUsers);
	return initUsers;
}

// fills list of friends for some members to initiate the program
void initiateFriendships(User** allUsers)
{
	allUsers[0]->getFriendsList()[0] = allUsers[1];
	allUsers[1]->getFriendsList()[0] = allUsers[0];

	allUsers[0]->getFriendsList()[1] = allUsers[2];
	allUsers[2]->getFriendsList()[0] = allUsers[0];

	allUsers[1]->getFriendsList()[1] = allUsers[2];
	allUsers[2]->getFriendsList()[1] = allUsers[1];

	allUsers[4]->getFriendsList()[0] = allUsers[3];
	allUsers[3]->getFriendsList()[0] = allUsers[4];

	allUsers[4]->getFriendsList()[1] = allUsers[2];
	allUsers[2]->getFriendsList()[2] = allUsers[4];
}

// fills the pages array with pages
Page** initiatePages(Operation* system, User** allUsers)
{
	Page** initPages = new Page * [5];

	Page* maccabi_haifa = new Page("Maccabi Haifa");
	initPages[0] = maccabi_haifa;
	Page* harry_potter = new Page("Harry Potter");
	initPages[1] = harry_potter;
	Page* pink_floyd = new Page("Pink Floyd");
	initPages[2] = pink_floyd;
	Page* led_zeppelin = new Page("Led Zeppelin");
	initPages[3] = led_zeppelin;
	Page* cakes = new Page("Cakes");
	initPages[4] = cakes;

	initiatePageLikes(system, allUsers, initPages);

	return initPages;
}

// initiate likes on pages from users
void initiatePageLikes(Operation* system, User** allUsers, Page** pages)
{
	pages[0]->addFanToPage(system, allUsers[3]);
	pages[1]->addFanToPage(system, allUsers[4]);
	pages[3]->addFanToPage(system, allUsers[1]);
	pages[4]->addFanToPage(system, allUsers[0]);
	pages[4]->addFanToPage(system, allUsers[3]);
	pages[4]->addFanToPage(system, allUsers[4]);
}

// initiate status for each user
void initiateStatuses(Operation* system)
{
	User** allUsers = system->getAllUsers();

	for (int i = 0; i < system->getNumOfUsers(); i++)
	{
		Clock date;
		Status* newStatus = new Status("Hello world", date.getDate());
		allUsers[i]->createStatus(newStatus);
	}
}

int displayMenu()
{
	int choice;

	cout << "Please choose an action:\n";
	cout << "1. Add new user\n";
	cout << "2. Add new page\n";
	cout << "3. Create a new status\n";
	cout << "4. Display all statuses\n";
	cout << "5. Display all 10 recent statuses of all your friends\n";
	cout << "6. Add a new friend\n";
	cout << "7. Unfriend\n";
	cout << "8. Like a page\n";
	cout << "9. Unlike a page\n";
	cout << "10. Display all entities of Facebook\n";
	cout << "11. Display all friends of a friend or page\n";
	cout << "12. Exit\n";

	cin >> choice;

	if (choice > 0 && choice << 13)
		return choice;
	else
		return 12;
}

// returns the user's index in allUsers array, and -1 if not found.
int doesUserExist(const char* name, Operation* system)
{
	int index;
	User** allUsers = system->getAllUsers();

	for (index = 0; index < system->getNumOfUsers(); index++)
	{
		if (strcmp(allUsers[index]->getName(), name) == 0)
			return index;
	}

	return NOT_FOUND;
}

// returns the page's index in the allPages array, or -1 if is not found
int doesPageExist(const char* name, Operation* system)
{
	int index;
	Page** allPages = system->getAllPages();

	for (index = 0; index < system->getNumOfPages(); index++)
	{
		if (strcmp(allPages[index]->getName(), name) == 0)
			return index;
	}

	return NOT_FOUND;
}

// to enter a new user to the system
void getUserInput(Operation* system)
{
	char* username = new char[MAX_CHARACTERS];

	cout << "Please enter your username: ";
	cin.ignore();
	cin.getline(username, MAX_CHARACTERS);

	// validate username
	if (doesUserExist(username, system) >= 0)
	{
		cout << "username is already taken" << endl << endl;
		delete[] username;
		return;
	}

	Clock birthday = birthday.getBirthdayInput();
	User* userToAdd = new User(username, birthday, 1, 0, 1, 0);
	system->addUserToOperation(userToAdd);
}

void addPageToSystem(Operation* system)
{
	char* pageName = new char[MAX_CHARACTERS];

	cout << "Please enter page name: ";
	cin.ignore();
	cin.getline(pageName, MAX_CHARACTERS);

	// validate username
	if (doesPageExist(pageName, system) >= 0) {
		cout << "Page name is already taken." << endl << endl;
		return;
	}

	Page* pageToAdd = new Page(pageName);

	system->addPageToOperation(pageToAdd);
}

void getUserOrPageInput(int userChoice, Operation* system)
{
	// userChoice is according to handleMenu()
	char* username = new char[MAX_CHARACTERS];
	char* pageName = new char[MAX_CHARACTERS];

	User** allUsers = system->getAllUsers();
	Page** allPages = system->getAllPages();

	bool isUserToDisplay = 0;

	cout << "Choose: " << endl;
	cout << "0 - Page" << endl << "1 - User" << endl;
	cin >> isUserToDisplay;

	if (isUserToDisplay) { // the choice was User
		cout << "Please enter username: ";
		cin.ignore();
		cin.getline(username, MAX_CHARACTERS);

		int friendIndex = doesUserExist(username, system);

		if (friendIndex >= 0) {
			switch (userChoice)
			{
			case 3:
				allUsers[friendIndex]->createStatus(nullptr);
				break;
			case 4:
				allUsers[friendIndex]->displayAllStatuses();
				break;
			case 11:
				allUsers[friendIndex]->displayAllFriends();
				break;
			default:
				break;
			}
		}
		else cout << "user was not found" << endl;
	}
	else  // choice was Page
	{
		cout << "Please enter page name: ";
		cin.ignore();
		cin.getline(pageName, MAX_CHARACTERS);

		int pageIndex = doesPageExist(pageName, system);

		if (pageIndex >= 0) {
			switch (userChoice)
			{
			case 3:
				allPages[pageIndex]->createStatus();
				break;
			case 4:
				allPages[pageIndex]->displayAllStatuses();
				break;
			case 11:
				allPages[pageIndex]->displayAllFans();
				break;
			default:
				break;
			}
		}
		else cout << "page was not found" << endl;
	}

	delete[]username;
	delete[]pageName;
}

// asks for a page name and search it in the system.
// returns pointer to the page, and null if not found
Page* getPageDetails(Operation* system)
{
	Page** allPages = system->getAllPages();
	char pageName[MAX_CHARACTERS];
	int index = 0;

	cout << "Enter page name: ";
	//cin.ignore();
	cin.getline(pageName, MAX_CHARACTERS);

	index = doesPageExist(pageName, system);

	if (index >= 0)
		return allPages[index];
	else
		return nullptr;
}

// ask for name and search it on allUsers array, returns the user's pointer, or nullptr if not found
// if flag is 0 we request the user's name, and 1 to ask another user name (friend).
User* askForUsername(Operation* system, int flag)
{
	User* user = nullptr;
	char* username = new char[MAX_CHARACTERS];
	int userIndex;

	cout << "Please enter ";
	flag == 0 ? cout << "your username: " : cout << "friend's name: ";
	if(flag == 0)
		cin.ignore();
	cin.getline(username, MAX_CHARACTERS);
	userIndex = doesUserExist(username, system);
	if (userIndex == NOT_FOUND)
		flag == 0 ? cout << "User not found!\n\n" : cout << "Friend not found!\n\n";
	else
		user = system->getAllUsers()[userIndex];

	delete[] username;
	return user;
}