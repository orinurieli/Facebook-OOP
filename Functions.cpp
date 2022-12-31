#include "Functions.h"
#include <iostream>
using namespace std;

// fills allUsers array with members
vector<User*> initiateUsers()
{
	vector<User*> initUsers;

	Clock birthday1(15, 4, 1990);
	Clock birthday2(24, 1, 1995);
	Clock birthday3(14, 5, 1984);
	Clock birthday4(1, 7, 1997);
	Clock birthday5(21, 10, 1996);

	User* user1 = new User("Keren Kalif", birthday1, 2, 1);
	User* user2 = new User("Steve Jobs", birthday2, 2, 1);
	User* user3 = new User("Mark Zuckerberg", birthday3, 3, 2);
	User* user4 = new User("Ori Nurieli", birthday4, 1, 3);
	User* user5 = new User("Gon Etgar", birthday5, 2, 3);

	initUsers.push_back(user1);
	initUsers.push_back(user2);
	initUsers.push_back(user3);
	initUsers.push_back(user4);
	initUsers.push_back(user5);

	initiateFriendships(initUsers);
	return initUsers;
}

// fills list of friends for some members to initiate the program
void initiateFriendships(vector<User*> allUsers)
{
	allUsers[0]->pushToFriendsList(*allUsers[1]);
	allUsers[1]->pushToFriendsList(*allUsers[0]);

	allUsers[0]->pushToFriendsList(*allUsers[2]);
	allUsers[2]->pushToFriendsList(*allUsers[0]);

	allUsers[1]->pushToFriendsList(*allUsers[2]);
	allUsers[2]->pushToFriendsList(*allUsers[1]);

	allUsers[4]->pushToFriendsList(*allUsers[3]);
	allUsers[3]->pushToFriendsList(*allUsers[4]);

	allUsers[4]->pushToFriendsList(*allUsers[2]);
	allUsers[2]->pushToFriendsList(*allUsers[4]);
}

// fills the pages array with pages
vector<Page*> initiatePages(Operation& system, vector<User*> allUsers)
{
	vector<Page*> initPages;

	Page* page1 = new Page((string)"Maccabi Haifa");
	Page* page2 = new Page((string)"Harry Potter");
	Page* page3 = new Page((string)"Pink Floyd");
	Page* page4 = new Page((string)"Led Zeppelin");
	Page* page5 = new Page((string)"Cakes");

	initPages.push_back(page1);
	initPages.push_back(page2);
	initPages.push_back(page3);
	initPages.push_back(page4);
	initPages.push_back(page5);

	initiatePageLikes(system, allUsers, initPages);
	return initPages;
}

// initiate likes on pages from users
void initiatePageLikes(Operation& system, vector<User*> allUsers, vector<Page*> pages)
{
	*pages[0] += *allUsers[3];
	*allUsers[3] += *pages[0];

	*pages[1] += *allUsers[4];
	*allUsers[4] += *pages[1];

	*pages[3] += *allUsers[1];
	*allUsers[1] += *pages[3];

	*pages[2] += *allUsers[0];
	*allUsers[0] += *pages[2];

	*pages[4] += *allUsers[3];
	*allUsers[3] += *pages[4];

	*pages[4] += *allUsers[4];
	*allUsers[4] += *pages[4];
}

// initiate status for each user
void initiateStatuses(Operation& system)
{
	vector<User*> all_users = system.getAllUsers();
	vector<Page*> all_pages = system.getAllPages();
	int num_of_users = system.getNumOfUsers();
	int num_of_pages = system.getNumOfPages();

	for (int i = 0; i < num_of_users; i++)
	{
		Clock date;
		Status* newStatus = new Status("Hello world", date.getDate());
		all_users[i]->createStatus(newStatus);
	}

	for (int i = 0; i < num_of_pages; i++)
	{
		Clock date;
		Status* newStatus = new Status("Hello world", date.getDate());
		all_pages[i]->createStatus(newStatus);
	}
}

int displayMenu() throw (const char*)
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

	if (cin >> choice) {


		if (choice > 0 && choice < 13)
			return choice;
		else
		{
			throw "Invalid Choice!";
			return 12; // maybe causing an error
		}
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		throw "You can't enter a string. Please choose between 1-12.";
	}
}

// returns the user's index in allUsers array, and -1 if not found.
int doesUserExist(string& name, Operation& system)
{
	int index, num_of_users = system.getNumOfUsers();
	vector<User*> allUsers = system.getAllUsers();

	for (index = 0; index < num_of_users; index++)
	{
		if (allUsers[index]->getUserName().compare(name) == 0)
			return index;
	}

	return NOT_FOUND;
}

// checks if the page "name" exists in the system. returns the page's index in the allPages array, or -1 if is not found
int doesPageExist(string& name, Operation& system)
{
	int index, num_of_pages = system.getNumOfPages();
	vector<Page*> allPages = system.getAllPages();

	for (index = 0; index < num_of_pages; index++)
	{
		if (allPages[index]->getName().compare(name) == 0)
			return index;
	}

	return NOT_FOUND;
}

// in order to enter a new user to the system
void getUserInput(Operation& system) throw (const char*)
{
	string username;

	cout << "Please enter your username: ";
	cin.ignore();
	getline(cin, username);

	// validate username
	if (doesUserExist(username, system) >= 0)
	{
		throw "username is already taken";
		return;
	}

	Clock birthday;
	try
	{
		birthday = birthday.getBirthdayInput();
	}
	catch (const char* err)
	{
		cout << endl << "error while entering birhtday input: " << err << endl << endl;
		return;
	}


	User* user_to_add = new User(username, birthday, 0, 0);
	system.addUserToOperation(*user_to_add);
}


void addPageToSystem(Operation& system) noexcept(false)
{
	string pageName;

	cout << "Please enter page name: ";
	cin.ignore();
	getline(cin, pageName);

	// validate username
	while (true)
	{
		try
		{
			if (doesPageExist(pageName, system) >= 0) {
				throw "Page name is already taken.";
			}
			else break;
		}
		catch (const char* err)
		{
			cout << endl << err << endl;
			cout << "Please choose a different name: ";
			getline(cin, pageName);
		}
	}

	Page* pageToAdd = new Page(pageName); // deleted in ~Operation
	system.addPageToOperation(*pageToAdd);
}


// in order to navigate the menu to the right entity, we ask if it's a user or a page
int askUserOrPage() noexcept(false)
{
	int userOrPage = -1;
	cout << "Choose: " << endl << "0 - Page" << endl << "1 - User" << endl;

	while (userOrPage != 0 && userOrPage != 1)
	{
		try
		{
			cin >> userOrPage;
			if (userOrPage != 0 && userOrPage != 1)
				throw invalid_argument("You can choose only 0 or 1.");
			else break;
		}
		catch (invalid_argument& err)
		{
			cout << err.what() << endl;
			cout << "Choose: " << endl << "0 - Page" << endl << "1 - User" << endl;
		}
	}

	return userOrPage;
}

// if the user choose an option from the menu that can be either for a page or a user, the function navigates to the right function.
void getUserOrPageInput(int userChoice, Operation& system) noexcept(false)
{
	int userOrPage = askUserOrPage();
	cin.clear();

	if (userOrPage == USER)
	{
		User* current_user = askForUsername(system, USER);

		if (current_user != nullptr)
		{
			switch (userChoice)
			{
			case CreateNewStatus:
				current_user->createStatus(nullptr);
				break;
			case DisplayAllStatuses:
				current_user->displayAllStatuses();
				break;
			case DisplayAllFriendsOfUserOrFansOfPage:
				current_user->displayAllFriends();
				break;
			default:
				break;
			}
		}
		else throw invalid_argument("user was not found.");
	}
	else // userOrPage == PAGE
	{
		Page* fan_page = getPageDetails(system, -1);

		if (fan_page)
		{
			switch (userChoice)
			{
			case CreateNewStatus:
				fan_page->createStatus(nullptr);
				break;
			case DisplayAllStatuses:
				fan_page->displayAllStatuses();
				break;
			case DisplayAllFriendsOfUserOrFansOfPage:
				fan_page->displayAllFans();
				break;
			default:
				break;
			}
		}
		else throw invalid_argument("page was not found.");
	}
}

// asks for a page name and search it in the system.
// returns pointer to the page, and null if not found
Page* getPageDetails(Operation& system, int clearBuffer)
{
	vector<Page*> allPages = system.getAllPages();
	string page_name;
	int index = 0;

	cout << "Enter page name: ";
	if (clearBuffer)
		cin.ignore();
	getline(cin, page_name);

	index = doesPageExist(page_name, system);

	if (index >= 0)
		return allPages[index];
	else
		return nullptr;
}

// ask for name and search it on allUsers array, returns the user's pointer, or nullptr if not found
// if flag is 1 we request the user's name, and 2 to ask another user name (friend).
User* askForUsername(Operation& system, int flag) throw (const char*) // *returns a pointer because NULL can be returned*
{
	User* user = nullptr;
	string user_name;
	int userIndex;

	cout << "Please enter ";
	flag == USER ? cout << "your username: " : cout << "friend's name: ";
	if (flag == USER)
		cin.ignore();

	getline(cin, user_name);
	userIndex = doesUserExist(user_name, system);
	if (userIndex == NOT_FOUND)
		flag == USER ? throw "User not found!" : cout << "Friend not found!\n\n";
	else
		user = system.getAllUsers()[userIndex];

	return user;
}

void newTerminate()
{
	cout << "oops, looks like a problem occured." << endl << "Please call support and don't lower our grade :)" << endl << endl;
}

