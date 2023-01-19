#include "Functions.h"
#include <iostream>
using namespace std;

// ################ menu ################

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

	if (cin >> choice)
	{
		if (choice > 0 && choice <= Exit)
			return choice;
		else
			throw "Invalid Choice!";
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		throw "You can't enter a string. Please choose between 1-12.";
	}
}

// ################ handle menu functions ################

// if user found returns its pointer, else nullptr
User* searchUserByName(string& name, Operation& system) // *can return null!*
{
	vector<User*> allUsers = system.getAllUsers();
	vector<User*>::iterator itr = allUsers.begin();
	vector<User*>::iterator itrEnd = allUsers.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((**itr).getName().compare(name) == 0)
			return *itr;
	}

	return nullptr;
}

// if page found returns its pointer, else nullptr
Page* searchPageByName(string& name, Operation& system) // *can return null!*
{
	vector<Page*> allPages = system.getAllPages();
	vector<Page*>::iterator itr = allPages.begin();
	vector<Page*>::iterator itrEnd = allPages.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((**itr).getName().compare(name) == 0)
			return *itr;
	}

	return nullptr;
}

// in order to navigate the menu to the right entity, we ask if it's a user or a page
int askUserOrPage() noexcept(false)
{
	int userOrPage = NOT_FOUND;
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

// ################ add new user ################

// in order to enter a new user to the system
void getUserInput(Operation& system) throw (const char*)
{
	string username;

	cout << "Please enter your username: ";
	cin.ignore();
	getline(cin, username);

	// validate username
	if (searchUserByName(username, system)) // name exists
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

	User* user_to_add = new User(username, birthday);
	system.addUserToOperation(*user_to_add);
}


void addPageToSystem(Operation& system) noexcept(false)
{
	string pageName;

	cout << "Please enter page name: ";
	cin.ignore();
	getline(cin, pageName);

	// validate page name
	while (true)
	{
		try
		{
			if (searchPageByName(pageName, system))
			{
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

	Page* pageToAdd = new Page(pageName);
	system.addPageToOperation(*pageToAdd);
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
				current_user->createStatus();
				break;
			case DisplayAllStatuses:
				current_user->displayAllStatuses();
				break;
			case DisplayAllFriendsOfUserOrFansOfPage:
				current_user->displayAllFriendsOrFans(USER);
				break;
			default:
				break;
			}
		}
		else throw invalid_argument("user was not found.");
	}
	else // userOrPage == PAGE
	{
		Page* fan_page = getPageDetails(system, CLEAR_BUFFER);

		if (fan_page)
		{
			switch (userChoice)
			{
			case CreateNewStatus:
				fan_page->createStatus();
				break;
			case DisplayAllStatuses:
				fan_page->displayAllStatuses();
				break;
			case DisplayAllFriendsOfUserOrFansOfPage:
				fan_page->displayAllFriendsOrFans(PAGE);
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
Page* getPageDetails(Operation& system, int clearBuffer) // returns pointer because null can be returned
{
	vector<Page*> allPages = system.getAllPages();
	string page_name;
	int index = 0;

	cout << "Enter page name: ";
	if (clearBuffer)
		cin.ignore();
	getline(cin, page_name);

	Page* page = searchPageByName(page_name, system);
	return page;
}

// ask for name and search it on allUsers array, returns the user's pointer, or nullptr if not found
// if flag is 1 we request the user's name, and 2 to ask another user name (friend).
// returns a pointer to a user if found, and null if wasn't found
User* askForUsername(Operation& system, int flag) throw (const char*) // *returns a pointer because NULL can be returned*
{
	string user_name;

	cout << "Please enter ";
	flag == USER ? cout << "your username: " : cout << "friend's name: ";
	if (flag == USER)
		cin.ignore();

	getline(cin, user_name);
	User* user = searchUserByName(user_name, system);
	if (user == nullptr)
		flag == USER ? throw "User not found!" : cout << "Friend not found!\n\n";

	return user;
}

void newTerminate()
{
	cout << "oops, looks like a problem occured." << endl << "Please call support and don't lower our grade :)" << endl << endl;
}