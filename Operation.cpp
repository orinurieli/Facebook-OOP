#include <iostream>
using namespace std;
#include "Operation.h"

// c'tor
Operation::Operation()
{
	initiateData(_allUsers, _allPages);
}

// initiate the program with users and pages
void Operation::initiateData(vector<User*>& initUsers, vector<Page*>& initPages)
{
	const string& FILE_NAME = "Facebook_DataBase.txt";
	readObjects(FILE_NAME);

	/*_allUsers = initiateUsers();
	_allPages = initiatePages(*this, _allUsers);
	initiateStatuses(*this);*/

}



// insert a new user to the allUsers vector
void Operation::addUserToOperation(User& userToAdd)
{
	_allUsers.push_back(&userToAdd);
	//_numOfUsers++;
	cout << endl << "Hey, " << userToAdd.getName() << " Welcome to Facebook :) " << endl << endl;
}

// insert a new page to the allPages vector
void Operation::addPageToOperation(Page& pageToAdd)
{
	_allPages.push_back(&pageToAdd);
	//_numOfPages++;
	cout << "Congrats! Your page: " << pageToAdd.getName() << " is Live on Facebook." << endl << endl;
}

// prints out all the entities on facebook, the users and pages
void Operation::displayAllEntities() const noexcept(false)
{

	cout << endl << "ALL ENTITIES: " << endl;
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

	cout << endl << "Pages: " << endl << "------" << endl;
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

// searches for a user and returns its pointer, or null if doesn;t exist
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

Page* Operation::searchPageInOperation(const string& name)
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

// ############# writing functions ################## //

// writes to file only name and date of birth
ostream& operator<<(ostream& out, const User& user)
{
	out << user.getName();
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

// writes status's text and date to file
ostream& operator<<(ostream& out, const Status& status)
{
	string classType = typeid(status).name() + 6;
	out << classType << "\n";
	out << status._text << endl;
	out << status._time.getDay() << "." << status._time.getMonth() << "." << status._time.getYear() << endl;
	out << status._time.getHours() << ":" << status._time.getMinutes() << ":" << status._time.getSeconds() << endl;

	if (classType == "VideoStatus")
		out << "video url" << endl; // TODO
		//out << dynamic_cast<VideoStatus*>(_statuses[i])->getVideoUrl();
	else if (classType == "ImageStatus")
		out << "image url" << endl; // TODO
		//out << dynamic_cast<ImageStatus*>(_statuses[i])->getImageUrl();

	return out;
}

// this function writes the facebook's data into the file
void Operation::storeObjects(const string& filename)
{
	ofstream out(filename, ios::trunc); // open file for writing

	int numUsers = _allUsers.size();
	out << numUsers; // write number of users 

	// write all users to the file
	for (User* user : _allUsers)
	{
		// write all users
		out << user->getName() << endl;
		out << user->getBirthday();
	}
	out << endl; // to seprate the birthday of the last user from the number of pages

	int numPages = _allPages.size();
	out << numPages; // write number of pages 

	//write all pages to the file
	for (Page* page : _allPages)
	{
		// write all users
		out << page->getName() << endl;
	}

	// go over all users

	vector<User*>::iterator itrUsers = _allUsers.begin();
	vector<User*>::iterator itrUsersEnd = _allUsers.end();

	for (; itrUsers != itrUsersEnd; ++itrUsers)
	{
		// write friends
		vector<User*> friends = (*itrUsers)->getFriendsList();
		vector<User*>::iterator itrFriends = friends.begin();
		vector<User*>::iterator itrFriendsEnd = friends.end();
		int numFriends = friends.size();
		out << numFriends; // write number of friends
		if (numFriends == 0)
			out << endl;
		
		for (; itrFriends != itrFriendsEnd; ++itrFriends)
		{
			out << (*itrFriends)->getName() << endl; // write friend's name
		}

		// write pages
		vector<Page*> pages = (*itrUsers)->getLikedPagesList();
		vector<Page*>::iterator itrPages = pages.begin();
		vector<Page*>::iterator itrPagesEnd = pages.end();
		int numPages = pages.size();
		out << numPages;
		if (numPages == 0)
			out << endl;

		for (; itrPages != itrPagesEnd; ++itrPages)
		{
			out << (*itrPages)->getName() << endl; // write pages's name
		}

		// write statuses
		vector<Status*> statuses = (*itrUsers)->getStatusesList();
		vector<Status*>::iterator itrStatuses = statuses.begin();
		vector<Status*>::iterator itrStatusesEnd = statuses.end();
		int numStatuses = statuses.size();
		out << numStatuses;
		if (numStatuses == 0)
			out << endl;

		for (; itrStatuses != itrStatusesEnd; ++itrStatuses)
		{
			string type;

			if (dynamic_cast<TextStatus*>(*itrStatuses)) // get the status' type (text, image or video)
			{
				type = "TextStatus";
				out << "TextStatus" << endl;
			}
			else if (dynamic_cast<ImageStatus*>(*itrStatuses))
			{
				type = "ImageStatus";
				out << "ImageStatus" << endl;
			}
			else
			{
				type = "VideoStatus";
				out << "VideoStatus" << endl;
			}
			
			out << (*itrStatuses)->getStatusTime(); // write the date and hour
			out << (*itrStatuses)->getText() << endl; // write status' text
		
			// write url:
			if (dynamic_cast<ImageStatus*>(*itrStatuses)) // get the status' type (text, image or video)
			{
				out << dynamic_cast<ImageStatus*>(*itrStatuses)->getImageUrl() << endl;
			}
			else if (dynamic_cast<VideoStatus*>(*itrStatuses))
			{
				out << dynamic_cast<VideoStatus*>(*itrStatuses)->getVideoUrl() << endl;
			}
		}
	}

	// go over all pages

	vector<Page*>::iterator itrPages = _allPages.begin();
	vector<Page*>::iterator itrPagesEnd = _allPages.end();

	for (; itrPages != itrPagesEnd; ++itrPages)
	{
		// write fans
		vector<User*> fans = (*itrPages)->getFriendsList();
		vector<User*>::iterator itrFans = fans.begin();
		vector<User*>::iterator itrFansEnd = fans.end();
		int numFans = fans.size();
		out << numFans; // write number of friends
		if (numFans == 0)
			out << endl;

		for (; itrFans != itrFansEnd; ++itrFans)
		{
			out << (*itrFans)->getName() << endl; // write fans's name
		}

		// write statuses
		vector<Status*> statuses = (*itrPages)->getStatusesList();
		vector<Status*>::iterator itrStatuses = statuses.begin();
		vector<Status*>::iterator itrStatusesEnd = statuses.end();
		int numStatuses = statuses.size();
		out << numStatuses;
		if (numStatuses == 0)
			out << endl;

		for (; itrStatuses != itrStatusesEnd; ++itrStatuses)
		{
			if (dynamic_cast<TextStatus*>(*itrStatuses)) // get the status' type (text, image or video)
				out << "TextStatus" << endl;
			else if (dynamic_cast<ImageStatus*>(*itrStatuses))
				out << "ImageStatus" << endl;
			else
				out << "VideoStatus" << endl;
			//out << typeid(*itrStatuses).name() << endl; // get the status' type (text, image or video)

			out << (*itrStatuses)->getStatusTime(); // write the date and hour
			out << (*itrStatuses)->getText() << endl; // write status' text

			// write url:
			if (dynamic_cast<ImageStatus*>(*itrStatuses)) // get the status' type (text, image or video)
			{
				out << dynamic_cast<ImageStatus*>(*itrStatuses)->getImageUrl() << endl;
			}
			else if (dynamic_cast<VideoStatus*>(*itrStatuses))
			{
				out << dynamic_cast<VideoStatus*>(*itrStatuses)->getVideoUrl() << endl;
			}
		}
	}

	out.close();
}

// ########### read functions ############# //

// this function reads the facebook's data from the file
void Operation::readObjects(const string& filename)
{
	ifstream in(filename); // open file for reading
	int numUsers;
	in >> numUsers;

	// read all users from the file and add them to operation
	for (int i = 0; i < numUsers; i++)
	{
		string username;
		getline(in, username);
		Clock birthday;
		in >> birthday;

		User* user = new User(username, birthday);
		_allUsers.push_back(user);
	}

	int numPages;
	in >> numPages;

	//read all pages from the file and add them to operation
	for (int i = 0; i < numPages; i++)
	{
		// read all pages
		string pageName;
		getline(in, pageName);

		Page* fanPage = new Page(pageName);
		_allPages.push_back(fanPage);
	}

	// go over all users, and get the details about each one

	vector<User*>::iterator itrUsers = _allUsers.begin();
	vector<User*>::iterator itrUsersEnd = _allUsers.end();

	for (; itrUsers != itrUsersEnd; ++itrUsers)
	{
		// read friends
		int numFriends;
		in >> numFriends; // read number of friends

		for (int i = 0 ; i < numFriends; i++) // go over friends list
		{
			string friendsName;
			getline(in, friendsName);

			User* Friend = searchUserInOperation(friendsName);
			if (Friend)
				(*itrUsers)->pushToFriendsList(*Friend); // add this friend to the user's friends list
		}

		// read pages
		int numPages;
		in >> numPages;

		for (int i = 0; i < numPages; i++) // go over pages list
		{
			string pageName;
			getline(in, pageName);

			Page* page = searchPageInOperation(pageName);
			if (page)
				(*itrUsers)->pushToPagesList(*page); // add this pages to the user's liked pages
		}

		// read statuses
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

			if (type == "TextStatus")// TODO - problem with the type
			{
				newStatus = new TextStatus(text, date);
			}
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
			
			(*itrUsers)->pushToStatusesList(newStatus); // add this status to the user's statuses
		}
	}

	// go over all pages and get the details about each one
	vector<Page*>::iterator itrPages = _allPages.begin();
	vector<Page*>::iterator itrPagesEnd = _allPages.end();

	for (; itrPages != itrPagesEnd; ++itrPages)
	{
		// read fans
		int numFans;
		in >> numFans;
		vector<User*> fans = (*itrPages)->getFriendsList();

		for (int i = 0 ; i < numFans; i++)
		{
			string fansName;
			getline(in, fansName);

			User* newFan = searchUserInOperation(fansName);
			if (newFan)
				(*itrPages)->pushToFriendsList(*newFan); // add this fan to the page's fans list
		}

		// read statuses
		vector<Status*> statuses = (*itrPages)->getStatusesList();

		int numStatuses;
		in >> numStatuses;

		for (int i = 0; i < numStatuses; i++)
		{
			string type, text, url;
			Clock date;

			getline(in, type);
			in >> date;
			getline(in, text);
			Status* newStatus;

			if (type == "TextStatus")// TODO - problem with the type
			{
				newStatus = new TextStatus(text, date);
			}
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
			(*itrPages)->pushToStatusesList(newStatus); // add this status to the page's statuses
		}
	}

	in.close();
}


// read date from file
istream& operator>>(istream& in, Clock& date)
{
	in >> date._day;
	in >> date._month;
	in >> date._year;
	in >> date._hours;
	in >> date._minutes;
	in >> date._seconds;
	return in;
}

Operation::~Operation()
{
	int num_of_users = _allUsers.size();
	int num_of_pages = _allPages.size();

	for (int i = 0; i < num_of_users; i++)
		delete _allUsers[i];

	for (int i = 0; i < num_of_pages; i++)
		delete _allPages[i];
}