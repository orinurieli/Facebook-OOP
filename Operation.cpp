#include <iostream>
using namespace std;
#include "Operation.h"

// c'tor
Operation::Operation()
{
	const string& FILE_NAME = "Facebook_DataBase.txt";
	readObjects(FILE_NAME); // read from file all data and inititate the operation
}

// insert a new user to the allUsers vector
void Operation::addUserToOperation(User& userToAdd)
{
	_allUsers.push_back(&userToAdd);
	cout << endl << "Hey, " << userToAdd.getName() << " Welcome to Facebook :) " << endl << endl;
}

// insert a new page to the allPages vector
void Operation::addPageToOperation(Page& pageToAdd)
{
	_allPages.push_back(&pageToAdd);
	cout << "Congrats! Your page: " << pageToAdd.getName() << " is Live on Facebook." << endl << endl;
}

// prints out all the entities on facebook, the users and pages
void Operation::displayAllEntities() const noexcept(false)
{
	cout << endl << "all entites: " << endl;
	if (_allUsers.size() == 0 || _allPages.size() == 0) {
		throw invalid_argument("No entities on FB yet..");
	}
	cout << endl << "Users: " << endl << "------" << endl;
	for (int i = 0; i < _allUsers.size(); i++)
	{
		cout << _allUsers[i]->getName() << endl << "Birthday: ";
		Clock b = _allUsers[i]->getBirthday();
		b.displayDate();
		cout << endl << endl;
	}

	cout << "Pages: " << endl << "------" << endl;
	for (int i = 0; i < _allPages.size(); i++)
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

// searches for a user and returns its pointer, or null if not found
User* Operation::searchUserInOperation(const string& name)// *can return null!*
{
	vector<User*>::iterator itr = _allUsers.begin();
	vector<User*>::iterator itrEnd = _allUsers.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getName() == name)
			return *itr;
	}

	return nullptr;
}

// search for a page in operation by name, return it's pointer or null if not found
Page* Operation::searchPageInOperation(const string& name)// *can return null!*
{
	vector<Page*>::iterator itr = _allPages.begin();
	vector<Page*>::iterator itrEnd = _allPages.end();

	for (; itr != itrEnd; ++itr)
	{
		if ((*itr)->getName() == name)
			return *itr;
	}

	return nullptr;
}

// ############# writing to file functions ################## //

// this function writes the facebook's data into the file
void Operation::storeObjects(const string& filename)
{
	ofstream out(filename, ios::trunc); // open file for writing

	writeAllUsersAndPagesToFile(out); // write all names of the entities (users and pages)
	writeEachUsersDetails(out); // for each user write its details
	writeEachPagesDetails(out); // for each page write its details

	out.close();
}

// writes all the entities on facebook: users (namd and birthday) and pages (names)
void Operation::writeAllUsersAndPagesToFile(ostream& out)
{
	int numUsers = _allUsers.size(); // write all users to the file
	out << numUsers;
	for (User* user : _allUsers)
		out << *user;
	out << endl;

	int numPages = _allPages.size(); // write all pages to the file
	out << numPages;
	for (Page* page : _allPages)
		out << *page;
}

// for each user write: friends, liked pages and statuses
void Operation::writeEachUsersDetails(ostream& out)
{
	vector<User*>::iterator itrUsers = _allUsers.begin();
	vector<User*>::iterator itrUsersEnd = _allUsers.end();

	for (; itrUsers != itrUsersEnd; ++itrUsers)
	{
		writeFriendsOrFansToFile(out, **itrUsers);
		writePagesToFile(out, **itrUsers);
		writeStatusesToFile(out, **itrUsers);
	}
}

// for each page write: fans and statuses
void Operation::writeEachPagesDetails(ostream& out)
{
	vector<Page*>::iterator itrPages = _allPages.begin();
	vector<Page*>::iterator itrPagesEnd = _allPages.end();

	for (; itrPages != itrPagesEnd; ++itrPages)
	{
		writeFriendsOrFansToFile(out, **itrPages);
		writeStatusesToFile(out, **itrPages);
	}
}

// write entity's friends/fans to file
void Operation::writeFriendsOrFansToFile(ostream& out, Entity& entity)
{
	vector<User*> friends = entity.getFriendsList();
	vector<User*>::iterator itrFriends = friends.begin();
	vector<User*>::iterator itrFriendsEnd = friends.end();

	int numFriends = friends.size();
	out << numFriends; // write number of friends/fans
	if (numFriends == 0)
		out << endl;

	for (; itrFriends != itrFriendsEnd; ++itrFriends)
		out << **itrFriends; // write name and birthday
	out << endl;
}

// write the user's liked pages to the file
void Operation::writePagesToFile(ostream& out, User& user)
{
	vector<Page*> pages = user.getLikedPagesList();
	vector<Page*>::iterator itrPages = pages.begin();
	vector<Page*>::iterator itrPagesEnd = pages.end();
	int numPages = pages.size(); // write number of pages
	out << numPages;
	if (numPages == 0)
		out << endl;

	for (; itrPages != itrPagesEnd; ++itrPages)
		out << **itrPages; // write page name
}

// write the entity's statuses to the file
void Operation::writeStatusesToFile(ostream& out, Entity& entity)
{
	vector<Status*> statuses = entity.getStatusesList();
	vector<Status*>::iterator itrStatuses = statuses.begin();
	vector<Status*>::iterator itrStatusesEnd = statuses.end();
	int numStatuses = statuses.size();
	out << numStatuses; // write number of statuses
	if (numStatuses == 0)
		out << endl;

	for (; itrStatuses != itrStatusesEnd; ++itrStatuses)
		out << **itrStatuses; // write status' details
}

// writes to file only name and date of birth
ostream& operator<<(ostream& out, const User& user)
{
	out << user.getName() << endl;
	out << user.getBirthday();
	return out;
}

// writes date to files
ostream& operator<<(ostream& out, const Clock& date)
{
	out << date._day << " " << date._month << " " << date._year << " " << date._hours << " " << date._minutes << " " << date._seconds;
	return out;
}

// writes page name to file
ostream& operator<<(ostream& out, const Page& page)
{
	out << page._name << endl;
	return out;
}

// writes status's type, text and date to file
ostream& operator<<(ostream& out, Status& status)
{
	string type;

	if (dynamic_cast<TextStatus*>(&status)) // get the status' type (text, image or video)
	{
		type = "TextStatus";
		out << "TextStatus" << endl;
	}
	else if (dynamic_cast<ImageStatus*>(&status))
	{
		type = "ImageStatus";
		out << "ImageStatus" << endl;
	}
	else
	{
		type = "VideoStatus";
		out << "VideoStatus" << endl;
	}

	out << (&status)->getStatusTime(); // write the date and hour
	out << (&status)->getText() << endl; // write status' text

	// write url if it's image/video:
	if (type == "ImageStatus")
		out << dynamic_cast<ImageStatus*>(&status)->getImageUrl() << endl;
	else if (type == "VideoStatus")
		out << dynamic_cast<VideoStatus*>(&status)->getVideoUrl() << endl;

	return out;
}

// ##################### read from file functions ###################### //

// this function reads the facebook's data from the file
void Operation::readObjects(const string& filename)
{
	ifstream in(filename); // open file for reading

	readAllUsersAndPagesFromFile(in);
	readEachUsersDetails(in);
	readEachPagesDetails(in);

	in.close();
}

// read all the users and pages from file
void Operation::readAllUsersAndPagesFromFile(istream& in)
{
	int numUsers;
	in >> numUsers;

	for (int i = 0; i < numUsers; i++) // read all users from the file and add them to operation
	{
		User* user = new User(); // allocate temporary user
		in >> *user; // read user's name and birthday
		_allUsers.push_back(user); // add to all users vector
	}

	int numPages;
	in >> numPages;

	for (int i = 0; i < numPages; i++) //read all pages from the file and add them to operation
	{
		Page* fanPage = new Page(); // allocate temporary page
		in >> *fanPage; // read page name
		_allPages.push_back(fanPage); // add to all pages vector
	}
}

// for each user read: friends, liked pages and statuses
void Operation::readEachUsersDetails(istream& in)
{
	vector<User*>::iterator itrUsers = _allUsers.begin();
	vector<User*>::iterator itrUsersEnd = _allUsers.end();

	for (; itrUsers != itrUsersEnd; ++itrUsers)
	{
		readFriendsOrFansFromFile(in, **itrUsers);
		readPagesFromFile(in, **itrUsers);
		readStatusesFromFile(in, **itrUsers);
	}
}

// for each page read: fans and statuses
void Operation::readEachPagesDetails(istream& in)
{
	vector<Page*>::iterator itrPages = _allPages.begin();
	vector<Page*>::iterator itrPagesEnd = _allPages.end();

	for (; itrPages != itrPagesEnd; ++itrPages)
	{
		readFriendsOrFansFromFile(in, **itrPages);
		readStatusesFromFile(in, **itrPages);
	}
}

// read all friends/fans of the entity from file
void Operation::readFriendsOrFansFromFile(istream& in, Entity& entity)
{
	int numFriends;
	in >> numFriends; // read number of friends

	for (int i = 0; i < numFriends; i++) // go over friends list
	{
		User tmpFriend; // temp user that dies in the end of the iteration
		in >> tmpFriend; // read name and birthday

		User* newFriend = searchUserInOperation(tmpFriend.getName());
		if (newFriend)
			entity.pushToFriendsList(*newFriend); // add this friend to the user's friends list
	}
}

// read all liked pages of user from file
void Operation::readPagesFromFile(istream& in, User& user)
{
	int numPages;
	in >> numPages;

	for (int i = 0; i < numPages; i++) // go over pages list
	{
		Page tmpPage;
		in >> tmpPage;

		Page* newPage = searchPageInOperation(tmpPage.getName());
		if (newPage)
			user.pushToPagesList(*newPage); // add this pages to the user's liked pages
	}
}

// read all the statuses of the entity from file
void Operation::readStatusesFromFile(istream& in, Entity& entity)
{
	int numStatuses;
	in >> numStatuses;

	for (int i = 0; i < numStatuses; i++) // go over statuses list
	{
		string type, text, url;
		Clock date;
		getline(in, type); // read status' type (text, image or video)
		in >> date; // read the status' date and hour
		getline(in, text); // read status' text
		Status* newStatus;

		if (type == "TextStatus")
			newStatus = new TextStatus(text, date);
		else if (type == "ImageStatus")
		{
			getline(in, url);
			newStatus = new ImageStatus(text, date, url);
		}
		else //(type == "VideoStatus")
		{
			getline(in, url);
			newStatus = new VideoStatus(text, date, url);
		}
		entity.pushToStatusesList(newStatus); // add this status to the user's statuses
	}
}

// read user from file
istream& operator>>(istream& in, User& user)
{
	getline(in, user._name);
	in >> user._birthday;
	return in;
}

// read date from file
istream& operator>>(istream& in, Clock& date)
{
	in >> date._day >> date._month >> date._year >> date._hours >> date._minutes >> date._seconds;
	return in;
}

// read page from file
istream& operator>>(istream& in, Page& page)
{
	getline(in, page._name);
	return in;
}

// d'tor
Operation::~Operation()
{
	int num_of_users = _allUsers.size();
	int num_of_pages = _allPages.size();

	for (int i = 0; i < num_of_users; i++)
		delete _allUsers[i];

	for (int i = 0; i < num_of_pages; i++)
		delete _allPages[i];
}