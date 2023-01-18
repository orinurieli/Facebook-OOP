#include <iostream>
using namespace std;
#include "User.h"
#include "Functions.h"
#include "Clock.h"

class Page;

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
	if (searchMemberInFriendList(*friendToAdd) != NOT_FOUND)
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

	// checks if the friend is in the friends list
	int friend_index = searchMemberInFriendList(*friend_to_delete);
	if (friend_index == NOT_FOUND)
	{
		throw "User is not on your friend list.";
		return;
	}

	int user_index = friend_to_delete->searchMemberInFriendList(*this); // no need checking again beacause adding a friend is mutual. we only need the index.

	this->_friends.erase(this->_friends.begin() + friend_index);
	friend_to_delete->_friends.erase(friend_to_delete->_friends.begin() + user_index);

	cout << endl << _name << ", you have removed " << friend_to_delete->_name << " from your friend list." << endl << endl;
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
	*fan_page += *this; // add user to the page's fansList
	//fan_page->addFanToPage(*this); // todo - delete later if it works
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
		cout << endl << this->getName() << " disliked " << page_to_dislike->getName() << endl << endl;
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
		cout << "Friend's name: " << _friends[i]->getName() << endl;
		cout << _friends[i]->getName() << "'s 10 Most Recent Statuses Are:" << endl;
		vector<Status*> friend_status_list = _friends[i]->getStatusesList();
		int num_statuses = _friends[i]->getStatusesList().size();

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

// returns the user's address, and null if not found
User* User::searchUserInAllUsers(Operation& system, const string& nameToSearch)// *returns pointer because null can be returned*
{
	vector<User*> all_users = system.getAllUsers();
	int num_of_users = all_users.size();

	for (int i = 0; i < num_of_users; i++)
	{
		if (all_users[i]->getName().compare(nameToSearch) == 0)
			return all_users[i];
	}

	return nullptr;
}

// d'tor
User::~User()
{
	for (int i = 0; i < _statuses.size(); i++)
		delete _statuses[i];
}

