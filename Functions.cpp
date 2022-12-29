#include <iostream>
#include "Functions.h"
using namespace std;

#define NOT_FOUND -1
#define USER 0 // for the askForUsername func. todo- can be done with enum (not necessary)
#define FRIEND 1

// fills allUsers array with members
vector<User*> initiateUsers()
{
	vector<User*> initUsers;
	User* user1 = new User("Keren Kalif", Clock(15, 4, 1990), 2, 2, 2, 1);
	initUsers.push_back(user1);
	User* user2 = new User("Steve Jobs", Clock(24, 2, 1955), 2, 2, 2, 1);
	initUsers.push_back(user2);
	User* user3 = new User("Mark Zuckerberg", Clock(14, 5, 1984), 4, 3, 2, 2);
	initUsers.push_back(user3);
	User* user4 = new User("Ori Nurieli", Clock(1, 7, 1997), 2, 1, 4, 3);
	initUsers.push_back(user4);
	User* user5 = new User("Gon Etgar", Clock(21, 10, 1996), 2, 2, 4, 3);
	initUsers.push_back(user5);

	initiateFriendships(initUsers);
	return initUsers;
}

// fills list of friends for some members to initiate the program
void initiateFriendships(vector<User*> allUsers)
{
	allUsers[0]->pushToFriendsList(allUsers[1]);
	allUsers[1]->pushToFriendsList(allUsers[0]);

	allUsers[0]->pushToFriendsList(allUsers[2]);
	allUsers[2]->pushToFriendsList(allUsers[0]);

	allUsers[1]->pushToFriendsList(allUsers[2]);
	allUsers[2]->pushToFriendsList(allUsers[1]);

	allUsers[4]->pushToFriendsList(allUsers[3]);
	allUsers[3]->pushToFriendsList(allUsers[4]);

	allUsers[4]->pushToFriendsList(allUsers[2]);
	allUsers[2]->pushToFriendsList(allUsers[4]);
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
	pages[0]->addFanToPage(system, *allUsers[3]);
	pages[1]->addFanToPage(system, *allUsers[4]);
	pages[3]->addFanToPage(system, *allUsers[1]);
	pages[2]->addFanToPage(system, *allUsers[0]);
	pages[4]->addFanToPage(system, *allUsers[3]);
	pages[4]->addFanToPage(system, *allUsers[4]);
}

// initiate status for each user
void initiateStatuses(Operation* system)
{
	vector<User*> allUsers = system->getAllUsers();

	for (int i = 0; i < system->getNumOfUsers(); i++)
	{
		Clock date;
		Status* newStatus = new Status("Hello world", date.getDate());
		allUsers[i]->createStatus(newStatus);
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

	cin >> choice;

	if (choice > 0 && choice << 13)
		return choice;
	else
	{
		throw "Invalid Choice!";
		return 12; // maybe causing an error
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

		//const char* cUser_name = allUsers[index]->getUserName().c_str;
		/*const char* cName_to_check = name.c_str();

		if (strcmp(allUsers[index]->getUserName(), cName_to_check) == 0)
			return index;*/
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

		/*const char* cPage_name = allPages[index]->getName().c_str();
		const char* cName_to_check = name.c_str();

		if (strcmp(cPage_name, cName_to_check) == 0)
			return index;*/
	}

	return NOT_FOUND;
}

// in order to enter a new user to the system
void getUserInput(Operation& system) throw (const char*)
{
	//char* username = new char[MAX_CHARACTERS];
	string username;

	cout << "Please enter your username: ";
	cin.ignore();
	getline(cin, username);
	//cin.getline(username, MAX_CHARACTERS);

	// validate username
	if (doesUserExist(username, system) >= 0)
	{
		//cout << "username is already taken" << endl << endl;
		throw "username is already taken";
		//delete[] username;
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
	
	//const char* TEMPUSERNAME = username.c_str(); // TODO GON change to string
	User* userToAdd = new User(username, birthday, 1, 0, 1, 0);
	system.addUserToOperation(userToAdd);
}


void addPageToSystem(Operation& system) noexcept(false)
{
	//char* pageName = new char[MAX_CHARACTERS];
	string pageName;

	cout << "Please enter page name: ";
	cin.ignore();
	getline(cin, pageName);
	//cin.getline(pageName, MAX_CHARACTERS);

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
			cin.ignore();
			getline(cin, pageName);
			//cin.getline(pageName, MAX_CHARACTERS);
		}
	}

	Page* pageToAdd = new Page(pageName);
	system.addPageToOperation(pageToAdd);
}

// todo - devide to functions
void getUserOrPageInput(int userChoice, Operation& system) noexcept(false)
{
	// userChoice is according to handleMenu()
	//char* username = new char[MAX_CHARACTERS];
	//char* CHARpageName = new char[MAX_CHARACTERS];

	string user_name;
	string page_name;

	vector<User*> allUsers = system.getAllUsers();
	vector<Page*> allPages = system.getAllPages();

	int isUserToDisplay = -1;

	cout << "Choose: " << endl;
	cout << "0 - Page" << endl << "1 - User" << endl;

	while (isUserToDisplay != 0 && isUserToDisplay != 1)
	{
		try
		{
			cin >> isUserToDisplay;
			if (isUserToDisplay != 0 && isUserToDisplay != 1)
				throw invalid_argument("You can choose only 0 or 1.");
			else break;
		}
		catch (invalid_argument& err)
		{
			cout << err.what() << endl;
			cout << endl << "Choose: " << endl;
			cout << "0 - Page" << endl << "1 - User" << endl;
		}
	}

	if (isUserToDisplay) // the choice was User
	{
		cout << "Please enter username: ";
		cin.ignore();
		getline(cin, user_name);
		//cin.getline(username, MAX_CHARACTERS);

		int friendIndex = doesUserExist(user_name, system);

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
		else throw invalid_argument("user was not found.");
	}
	else  // choice was Page
	{
		cout << "Please enter page name: ";
		cin.ignore();
		getline(cin, page_name);
		//cin.getline(CHARpageName, MAX_CHARACTERS);

		int pageIndex = doesPageExist(page_name, system);

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
		else throw invalid_argument("page was not found.");
	}

	//delete[]username;
	//delete[]pageName;
}

// asks for a page name and search it in the system.
// returns pointer to the page, and null if not found
Page* getPageDetails(Operation& system) // *returns a pointer because NULL can be returned*
{
	vector<Page*> allPages = system.getAllPages();
	string page_name;
	//char pageName[MAX_CHARACTERS];
	int index = 0;

	cout << "Enter page name: ";
	getline(cin, page_name);
	//cin.ignore();
	//cin.getline(pageName, MAX_CHARACTERS);

	index = doesPageExist(page_name, system);

	if (index >= 0)
		return allPages[index];
	else
		return nullptr;
}

// ask for name and search it on allUsers array, returns the user's pointer, or nullptr if not found
// if flag is 0 we request the user's name, and 1 to ask another user name (friend).
User* askForUsername(Operation& system, int flag) throw (const char*) // *returns a pointer because NULL can be returned*
{
	//char* username = new char[MAX_CHARACTERS];
	User* user = nullptr;
	string user_name;
	int userIndex;

	cout << "Please enter ";
	flag == USER ? cout << "your username: " : cout << "friend's name: ";
	if (flag == USER)
		cin.ignore();

	getline(cin, user_name);
	//cin.getline(username, MAX_CHARACTERS);
	userIndex = doesUserExist(user_name, system);
	if (userIndex == NOT_FOUND)
		flag == USER ? throw "User not found!" : cout << "Friend not found!\n\n";
	else
		user = system.getAllUsers()[userIndex];

	//delete[] username;
	return user;
}

// todo: use this after we switch everything to string to validate and throw expections
bool isCharsOnly(const string& str)
{
	for (char c : str)
	{
		if (!isalpha(c))  // checks if its a letter
			return false;
	}
	return true;
}

void newTerminate()
{
	cout << "oops, looks like a problem occured." << endl << "Please call support and don't lower our grade :)" << endl << endl;
}