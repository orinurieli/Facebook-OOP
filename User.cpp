#include <iostream>
using namespace std;
#include "User.h"
#include "Functions.h"
#include "Clock.h"

class Page;

// c'tor
//User::User(const string& name, Clock& birthday, int numFriends, int numPages) : Entity(name, 0, 0)
//{
//	//_name = name;
//	_birthday = birthday;
//	//_numOfFriends = numFriends;
//	_numOfPages = numPages;
//}

// this function connects 2 users to be friends
void User::addFriend(Operation& system) throw (const char*)
{
	User* friendToAdd = askForUsername(system, FRIEND);

	if (friendToAdd == nullptr)
	{
		throw "Didn't find user name.";
		return;
	}
	if (friendToAdd == this)
	{
		throw "You can't add yourself as a friend.";
		return;
	}
	if (searchFriendInFriendList(*friendToAdd) != NOT_FOUND)
	{
		throw "Friend is already on your friend list.";
		return;
	}

	*this += *friendToAdd;
	cout << endl << _name << ", you have added " << friendToAdd->_name << " to your friend list." << endl << endl;
}

// this function cancel friendship between 2 users
void User::cancelFriendship(Operation& system) throw (const char*)
{
	User* friend_to_delete = askForUsername(system, FRIEND);
	if (friend_to_delete == nullptr)
		return;

	int friend_index = this->searchFriendInFriendList(*friend_to_delete);
	if (friend_index == NOT_FOUND)
	{
		throw "User is not on your friend list.";
		return;
	}

	int user_index = friend_to_delete->searchFriendInFriendList(*this);
	// no need checking again beacause adding a friend is mutual. we only need the index.

	this->removeFriendFromFriendList(friend_index);
	friend_to_delete->removeFriendFromFriendList(user_index);

	cout << endl << _name << ", you have removed " << friend_to_delete->_name << " from your friend list." << endl << endl;
}

// removes "friendToRemove" from friend list, if he's not in the end of the array, switch between the last friend to him. 
void User::removeFriendFromFriendList(int indexToRemove)
{
	int num_of_friends = _friends.size();
	_friends[indexToRemove] = nullptr;

	if (num_of_friends > 1 && indexToRemove != num_of_friends - 1)
	{
		// if friend is not last, and there is more than 1 friend on the array - swap them
		//_friendsList[indexToRemove] = _friendsList[_numOfFriends - 1];
		//_friendsList[_numOfFriends - 1] = nullptr;
		_friends[indexToRemove] = _friends[num_of_friends - 1];
		_friends[num_of_friends - 1] = nullptr;
	}
}

// adds the page to the user's liked pages
void User::likePage(Operation& system) throw (const char*)
{
	Page* fan_page = getPageDetails(system, 0);
	if (fan_page == nullptr)
	{
		throw "Page doesn't exist.\n";
		return;
	}
	if (PageExistInLikedPages(fan_page->getName()))	// check if the user already liked this page
	{
		throw "You already liked this page!.\n";
		return;
	}

	*this += *fan_page; // add page to the user's likedPages list
	fan_page->addFanToPage(system, *this); // add user to the page's fansList
	cout << _name << " liked " << fan_page->getName() << endl << endl;
}

// removes the page from the user's liked pages
void User::dislikePage(Operation& system) throw (const char*)
{
	Page* page_to_dislike = getPageDetails(system, 0);
	bool found = false;

	if (page_to_dislike == nullptr)
	{
		throw "Page was not found.";
		return;
	}


	//if (_numOfPages != _likedPages.size()) throw "miscalculating the size of _likedPages array.";

	int num_of_pages = this->_likedPages.size();

	for (int i = 0; i < num_of_pages && !found; i++)
	{
		// we didnt do for both sides!
		if (page_to_dislike == _likedPages[i]) // page is in likedPages
		{
			if (i != num_of_pages - 1) // if it's not the lase one on the vector, put it last
			{
				// switch between them
				Page* tmp = _likedPages[i];
				_likedPages[i] = _likedPages[num_of_pages - 1];
				_likedPages[num_of_pages - 1] = tmp;
			}

			_likedPages.pop_back(); // delete the last one
			page_to_dislike->removeFan(*this);
			found = true;
		}
	}

	if (!found)
		throw "Page was not found on your Liked Pages list.";
	else
		cout << endl << this->getUserName() << " disliked " << page_to_dislike->getName() << endl << endl;
}

// 10 most recent statuses of all his friends 
void User::displayRecentStatusesOfaFriend(Operation& system) const throw (const char*)
{
	const int NUM_STATUSES_TO_DISPLAY = 10;
	int num_of_friends = _friends.size();

	if (num_of_friends == 0)
		throw "No friends to display.";

	for (int i = 0; i < num_of_friends; i++) // go over friends list
	{
		//cout << "Friend's name: " << _friendsList[i]->getUserName() << endl;
		//cout << _friendsList[i]->getUserName() << "'s 10 Most Recent Statuses Are:" << endl;
		//vector<Status*> friend_status_list = _friendsList[i]->getAllStatuses();
		//int num_statuses = _friendsList[i]->getNumOfStatuses();


		cout << "Friend's name: " << _friends[i]->getUserName() << endl;
		cout << _friends[i]->getUserName() << "'s 10 Most Recent Statuses Are:" << endl;
		vector<Status*> friend_status_list = _friends[i]->getAllStatuses();
		int num_statuses = _friends[i]->getAllStatuses().size();

		if (num_statuses == 0)
			throw "No statuses to display.";
		else
		{
			int stop_loop;
			(num_statuses < NUM_STATUSES_TO_DISPLAY) ? (stop_loop = 0) : (stop_loop = num_statuses - NUM_STATUSES_TO_DISPLAY);

			cout << "----------------------------------";
			for (int j = num_statuses - 1; j >= stop_loop; j--)
			{
				cout << endl << "Status:" << endl;
				cout << "Text: " << friend_status_list[j]->getText() << endl;
				cout << "Uploaded On: ";
				friend_status_list[j]->getStatusTime().displayDate();
				cout << " | ";
				friend_status_list[j]->getStatusTime().displayHour();
				cout << endl;
			}
			cout << "----------------------------------" << endl << endl;
		}
	}
}

// adds 2 users to eachothers friend lists.
User& User::operator+=(User& other)
{
	_friends.push_back(&other);
	other._friends.push_back(this);
	return *this;
}

// add page to user's liked pages vector
User& User::operator+=(Page& fanPage)
{
	_likedPages.push_back(&fanPage);
	return *this;
}

// compare number of friends between 2 users
bool User::operator<(const User& other) const
{
	return (_friends.size() < other._friends.size());
}

// compare number of friends between 2 users
bool User::operator>(const User& other) const
{
	return (_friends.size() > other._friends.size());
}

// compare the user's number of friends to a page's number of fans
bool User::operator<(const Page& fanPage) const
{
	return (_friends.size() < fanPage.getFriendsList().size());
}

// compare the user's number of friends to a page's number of fans
bool User::operator>(const Page& fanPage) const
{
	return (_friends.size() > fanPage.getFriendsList().size());
}

ostream& User::operator<<(ostream& out) {
	// User Properties
	out << _name << " ";
	// todo: operator << Clock doesnt work
	out << _birthday.getDay() << " ";
	out << _birthday.getMonth() << " ";
	out << _birthday.getYear() << " ";
	out << _birthday.getHours() << " ";
	out << _birthday.getMinutes() << " ";
	out << _birthday.getSeconds() << " ";

	// User Pages
	out << _likedPages.size();
	for (int i = 0; i < _likedPages.size(); i++) {
		out << " ";
		out << _likedPages[i]->getName();
	}

	// User Statuses
	out << _statuses.size();
	for (int i = 0; i < _statuses.size(); i++) {
		string classType = typeid(*_statuses[i]).name() + 6;
		out << " ";
		out << classType;
		out << _statuses[i]->getText();
		out << " ";
		out << _statuses[i]->getStatusTime().getDay() << " ";
		out << _statuses[i]->getStatusTime().getMonth() << " ";
		out << _statuses[i]->getStatusTime().getYear() << " ";
		out << _statuses[i]->getStatusTime().getHours() << " ";
		out << _statuses[i]->getStatusTime().getMinutes() << " ";
		out << _statuses[i]->getStatusTime().getSeconds() << " ";

		/*if (classType.compare("VideoStatus"))
			cout << dynamic_cast<VideoStatus*>(_statuses[i])->getVideoUrl();
		else if (classType.compare("ImageStatus"))
			cout << dynamic_cast<ImageStatus*>(_statuses[i])->getImageUrl();*/

	}

	return out;
}

// check if the user liked a certain page
bool User::PageExistInLikedPages(const string& pageName)
{
	for (const Page* page : _likedPages)
	{
		if (page->getName() == pageName)
			return true;
	}
	return false;
}

// searches a friend in the user's friend list, returns the friend index in the vector, or -1 if not found
int User::searchFriendInFriendList(User& other)
{
	int friend_to_delete_index = NOT_FOUND;
	int num_of_friends = _friends.size();

	if (_friends.size() > 0) // if user has friends 
	{
		for (int i = 0; i < num_of_friends && friend_to_delete_index == NOT_FOUND; i++)
		{
			if (_friends[i]->_name.compare(other._name) == 0)
				friend_to_delete_index = i;
		}
	}
	return friend_to_delete_index;
}

// d'tor
User::~User()
{
	for (int i = 0; i < _statuses.size(); i++)
		delete _statuses[i];
}
