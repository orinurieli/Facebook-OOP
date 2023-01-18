#include "Functions.h"
#include <iostream>
using namespace std;

// ################ inititation ################

// fills allUsers array with members
vector<User*> initiateUsers()
{
	vector<User*> initUsers;

	Clock birthday1(15, 4, 1990);
	Clock birthday2(24, 1, 1995);
	Clock birthday3(14, 5, 1984);
	Clock birthday4(1, 7, 1997);
	Clock birthday5(21, 10, 1996);

	User* user1 = new User("Keren Kalif", birthday1);
	User* user2 = new User("Steve Jobs", birthday2);
	User* user3 = new User("Mark Zuckerberg", birthday3);
	User* user4 = new User("Ori Nurieli", birthday4);
	User* user5 = new User("Gon Etgar", birthday5);

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

	string maccabi = "Maccabi Haifa";
	string harry = "Harry Potter";
	string pink = "Pink Floyd";
	string led = "Led Zeppelin";
	string cakes = "Cakes";

	Page* page1 = new Page(maccabi);
	Page* page2 = new Page(harry);
	Page* page3 = new Page(pink);
	Page* page4 = new Page(led);
	Page* page5 = new Page(cakes);

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
		Status* newStatus = new TextStatus("Hello world", date.getDate());
		all_users[i]->pushToStatusesList(newStatus);
	}

	for (int i = 0; i < num_of_pages; i++)
	{
		Clock date;
		Status* newStatus = new TextStatus("Hello world", date.getDate());
		all_pages[i]->pushToStatusesList(newStatus);
	}
}

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

	if (cin >> choice) {


		if (choice > 0 && choice <= Exit)
			return choice;
		else
		{
			throw "Invalid Choice!";
			return Exit; // maybe causing an error // TODO?
		}
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		throw "You can't enter a string. Please choose between 1-12.";
	}
}

// ################ handle menu functions ################

// returns the user's index in allUsers array, and -1 if not found.
int doesUserExist(string& name, Operation& system)
{
	//int index, num_of_users = system.getNumOfUsers();
	vector<User*> allUsers = system.getAllUsers();
	int index, num_of_users = allUsers.size();

	for (index = 0; index < num_of_users; index++)
	{
		if (allUsers[index]->getName().compare(name) == 0)
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

	index = doesPageExist(page_name, system);

	if (index >= 0)
		return allPages[index];
	else
		return nullptr;
}

// ask for name and search it on allUsers array, returns the user's pointer, or nullptr if not found
// if flag is 1 we request the user's name, and 2 to ask another user name (friend).
// returns a pointer to a user if found, and null if wasn't found
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


void storeObjects(const string& filename, vector<User*> users, vector<Page*> pages)
{
	// Open file 
	ofstream out(filename, ios::trunc);

	// Write number of Users 
	int numUsers = users.size();
	out << numUsers;

	// Write Users
	for (const User* user : users) {
		if (user != nullptr)
			out << *user;
		cout << endl;
	}

	// Write number of Pages
	int numPages = pages.size();
	out << numPages;

	// Write Pages
	for (const Page* page : pages) {
		if (page != nullptr)
			out << *page;
		cout << endl;
	}

	out.close();
}

void readObjects(const string& filename, vector<User*>& users, vector<Page*>& pages)
{
	// Open file 
	cout << "Opening " << filename << endl;
	ifstream in(filename);

	// Read number of Users
	int numUsers;
	in >> numUsers;
	cout << "reading " << numUsers << " users" << endl;

	// Read Users
	for (int i = 0; i < numUsers; i++) {
		Clock bday(15, 4, 1990);
		User* user = new User("temp", bday);
		in >> *user;

		cout << "pushing user:" << user->getName() << endl << endl;
		users.push_back(user);
	}

	// Read number of Pages
	int numPages;
	in >> numPages;
	cout << "reading " << numPages << " pages" << endl;

	// Read Pages
	for (int i = 0; i < numPages; i++) {
		Page* page = new Page("temp");
		in >> *page;

		cout << "pushing page:" << page->getName() << endl;
		pages.push_back(page);
	}

	in.close();
}


// Global Operators
ostream& operator<<(ostream& out, const User& user)
{
	out << user.getName() << endl;
	cout << "- Writing " << user.getName() << " to file - " << endl;

	Clock _birthday = user.getBirthday();
	out << _birthday.getDay() << " ";
	out << _birthday.getMonth() << " ";
	out << _birthday.getYear() << endl;

	vector<User*> _friends = user.getFriendsList();
	out << _friends.size() << " ";
	for (int i = 0; i < _friends.size(); i++) {
		out << _friends[i]->getName() << endl;
		out << _friends[i]->getBirthday().getDay() << " ";
		out << _friends[i]->getBirthday().getMonth() << " ";
		out << _friends[i]->getBirthday().getYear() << " ";
	}

	cout << "friends: " << user.getFriendsList().size() << endl;


	vector<Page*> _pages = user.getLikedPagesList();
	out << _pages.size() << " ";;
	for (int i = 0; i < _pages.size(); i++) {
		out << _pages[i]->getName() << endl;
	}

	cout << "pages: " << user.getLikedPagesList().size() << endl;

	vector<Status*> _statuses = user.getStatusesList();
	out << _statuses.size() << " ";;
	for (int i = 0; i < _statuses.size(); i++) {
		string classType = typeid(*_statuses[i]).name() + 6;
		out << " ";
		out << classType;
		out << " ";
		out << _statuses[i]->getText() << endl;
		out << " ";
		out << _statuses[i]->getStatusTime().getDay() << " ";
		out << _statuses[i]->getStatusTime().getMonth() << " ";
		out << _statuses[i]->getStatusTime().getYear() << " ";

		if (classType == "VideoStatus")
			out << dynamic_cast<VideoStatus*>(_statuses[i])->getVideoUrl();
		else if (classType == "ImageStatus")
			out << dynamic_cast<ImageStatus*>(_statuses[i])->getImageUrl();
	}

	cout << "statuses: " << user.getStatusesList().size() << endl;

	cout << "Done writing " << user.getName() << endl;

	return out;
}

istream& operator>>(istream& in, User& user)
{
	int friendsSize, pagesSize, statusesSize;
	int day, month, year, friendDay, friendMonth, friendYear, statusDay, statusMonth, statusYear;
	string name, friendName, pageName, classType;
	string videoUrl, imageUrl, text;
	Clock _birthday;
	vector<User*> _friends;
	vector<Page*> _pages;
	vector<Status*> _statuses;

	getline(in, name);
	user.setName(name);

	// todo: check if need to "eat" the space after line
	cout << "- reading " << user.getName() << " from file -" << endl;

	in >> day >> month >> year;
	_birthday = Clock(day, month, year);
	user.setBirthday(_birthday);

	in >> friendsSize;
	for (int i = 0; i < friendsSize; i++) {
		getline(in, friendName);
		in >> friendDay >> friendMonth >> friendYear;
		Clock friendBday(friendDay, friendMonth, friendYear);
		User* newFriend = new User(friendName, friendBday);
		//newFriend->setBirthday(Clock(friendDay, friendMonth, friendYear));

		_friends.push_back(newFriend);
	}
	user.setFriendsList(_friends); // todo: setFriendsList needs virtual?

	in >> pagesSize;
	for (int i = 0; i < pagesSize; i++) {
		getline(in, pageName);
		Page* page = new Page(pageName);
		_pages.push_back(page);
	}
	user.setLikedPagesList(_pages);

	in >> statusesSize;
	for (int i = 0; i < statusesSize; i++) {
		in >> classType;
		getline(in, text);
		in >> statusDay >> statusMonth >> statusYear;
		Clock statusTime(statusDay, statusMonth, statusYear);

		if (classType == "VideoStatus") {
			in >> videoUrl;
			VideoStatus* status = new VideoStatus(text, statusTime, videoUrl);
			_statuses.push_back(status);
		}
		else if (classType == "ImageStatus") {
			in >> imageUrl;
			ImageStatus* status = new ImageStatus(text, statusTime, imageUrl);
			_statuses.push_back(status);
		}
		else {
			Status* status = new TextStatus(text, statusTime);
			_statuses.push_back(status);
		}
	}
	user.setStatusesList(_statuses);

	cout << "Done reading " << user.getName() << endl << endl;

	return in;
}



ostream& operator<<(ostream& out, const Page& page)
{
	out << page.getName();
	cout << "writing " << page.getName() << " to file.." << endl;

	vector<User*> _friends = page.getFriendsList();
	out << _friends.size();
	for (int i = 0; i < _friends.size(); i++) {
		out << " ";
		out << _friends[i]->getName();
		out << _friends[i]->getBirthday().getDay();
		out << _friends[i]->getBirthday().getMonth();
		out << _friends[i]->getBirthday().getYear();
	}

	vector<Status*> _statuses = page.getStatusesList();
	out << _statuses.size();
	for (int i = 0; i < _statuses.size(); i++) {
		string classType = typeid(*_statuses[i]).name() + 6;
		out << " ";
		out << classType;
		out << _statuses[i]->getText();
		out << " ";
		out << _statuses[i]->getStatusTime().getDay();
		out << _statuses[i]->getStatusTime().getMonth();
		out << _statuses[i]->getStatusTime().getYear();

		// todo: error here:
		if (classType == "VideoStatus")
			out << dynamic_cast<VideoStatus*>(_statuses[i])->getVideoUrl();
		else if (classType == "ImageStatus")
			out << dynamic_cast<ImageStatus*>(_statuses[i])->getImageUrl();
	}

	cout << "Done writing " << page.getName() << endl;

	return out;
}

istream& operator>>(istream& in, Page& page)
{
	string name, friendName, classType;
	string videoUrl, imageUrl, text;
	int statusDay, statusMonth, statusYear;
	int friendDay, friendMonth, friendYear;
	int friendsSize, statusesSize;
	Clock _birthday;
	vector<User*> _friends;
	vector<Status*> _statuses;

	cout << " inside page '>>' operator" << endl;
	in >> name;
	page.setName(name);
	cout << "reading " << page.getName() << " from file.." << endl;


	in >> friendsSize;
	for (int i = 0; i < friendsSize; i++) {
		in >> friendName >> friendDay >> friendMonth >> friendYear;
		Clock friendBday(friendDay, friendMonth, friendYear);
		User* newFriend = new User(friendName, friendBday);
		//newFriend->setBirthday(Clock(friendDay, friendMonth, friendYear));

		_friends.push_back(newFriend);
	}
	page.setFriendsList(_friends);

	in >> statusesSize;
	for (int i = 0; i < statusesSize; i++) {
		in >> classType >> text >> statusDay >> statusMonth >> statusYear;
		Clock statusTime(statusDay, statusMonth, statusYear);

		if (classType == "VideoStatus") {
			in >> videoUrl;
			VideoStatus* status = new VideoStatus(text, statusTime, videoUrl);
			_statuses.push_back(status);
		}
		else if (classType == "ImageStatus") {
			in >> imageUrl;
			ImageStatus* status = new ImageStatus(text, statusTime, imageUrl);
			_statuses.push_back(status);
		}
		else {
			Status* status = new TextStatus(text, statusTime);
			_statuses.push_back(status);
		}
	}
	page.setStatusesList(_statuses);

	cout << "Done reading " << page.getName() << endl;

	return in;
}


