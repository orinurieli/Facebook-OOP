#include <iostream>
using namespace std;
#include "User.h"
#include "Functions.h"

class Page;

// ################## c'tor ############## //

User::User(const string& name, Clock birthday, int maxNumFriends, int numFriends, int maxPages, int numPages)
{
	_name = name;
	_birthday = birthday;
	_maxNumOfFriends = maxNumFriends;
	_numOfFriends = numFriends;
	_maxNumOfPages = maxPages;
	_numOfPages = numPages;

	//_name = new char[MAX_CHARACTERS];
	//_name = _strdup(name);
	//_statuses = new Status * [_maxNumOfStatuses];
	//_likedPages = new Page * [_maxNumOfPages];
	//_friendsList.resize(1);
}



// ################## create status ############## //
void User::createStatus(Status* initStatus) // it's a pointer because it can also be null (from initiation)
{
	if (initStatus != nullptr) _statuses.push_back(initStatus);
	else
	{
		Status* newStatus = new Status();
		newStatus->getStatusInfo(newStatus);
		cout << "Status Uploaded!" << endl << endl;
		_statuses.push_back(newStatus);
	}
	_numOfStatuses++;
}

// ################## add friend ############## //

// this function connects 2 users to be friends
void User::addFriend(Operation& system) throw (const char*)
{
	User* friendToAdd = askForUsername(system, FRIEND);

	if (friendToAdd == nullptr)
	{
		throw "Didn't find user name.";
		return;
	}
	else if (friendToAdd == this)
	{
		throw "You can't add yourself as a friend.";
		return;
	}
	else if (searchFriendInFriendList(*friendToAdd) != NOT_FOUND)
	{
		throw "Friend is already on your friend list.";
		return;
	}

	*this += friendToAdd;
	cout << endl << _name << ", you have added " << friendToAdd->_name << " to your friend list." << endl << endl;
}

// adds 2 users to eachothers friend lists.
User* User::operator+=(User* other)
{
	_friendsList.push_back(other);
	_numOfFriends++;

	other->_friendsList.push_back(this);
	other->_numOfFriends++;

	return this;
}

// compare number of friends between 2 users
bool User::operator<(User& other)
{
	return (_numOfFriends < other._numOfFriends);
}

// compare number of friends between 2 users
bool User::operator>(User& other)
{
	return (_numOfFriends > other._numOfFriends);
}

// compare the user's number of friends to a page's number of fans
bool User::operator<(Page& fanPage)
{
	return (_numOfFriends < fanPage.getNumOfFans());
}

// compare the user's number of friends to a page's number of fans
bool User::operator>(Page& fanPage)
{
	return (_numOfFriends > fanPage.getNumOfFans());
}

// ################## unfriend ############## //

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

	this->removeFriendFromFriendList(friend_index);
	friend_to_delete->removeFriendFromFriendList(user_index);

	cout << endl << _name << ", you have removed " << friend_to_delete->_name << " from your friend list." << endl << endl;
}

// searches a friend in the user's friend list, returns the friend index in the vector, or -1 if not found
int User::searchFriendInFriendList(User& other) throw (const char*)
{
	int friend_to_delete_index = NOT_FOUND;

	if (_friendsList.size() > 0) // if user has friends 
	{
		for (int i = 0; i < _numOfFriends && friend_to_delete_index == NOT_FOUND; i++)
		{
			if (_friendsList[i]->_name.compare(other._name) == 0)
				friend_to_delete_index = i;
		}

		if (friend_to_delete_index == NOT_FOUND)
			throw "The friend was not found on your friend list!\n";
	}
	return friend_to_delete_index;
}

// removes "friendToRemove" from friend list, if he's not in the end of the array, switch between the last friend to him. 
void User::removeFriendFromFriendList(int indexToRemove)
{
	_friendsList[indexToRemove] = nullptr;

	if (_numOfFriends > 1 && indexToRemove != _numOfFriends - 1)
	{
		// if friend is not last, and there is more than 1 friend on the array - swap them
		_friendsList[indexToRemove] = _friendsList[_numOfFriends - 1];
		_friendsList[_numOfFriends - 1] = nullptr;
	}

	_numOfFriends--;
}

// ################## like page ############## //
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

	*this += fan_page; // add page to the user's likedPages list
	fan_page->addFanToPage(system, *this); // add user to the page's fansList
	cout << _name << " liked " << fan_page->getName() << endl << endl;
}

// add page to user's liked pages vector
User* User::operator+=(Page* fanPage)
{
	_likedPages.push_back(fanPage);
	_numOfPages++;
	return this;
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

// ################## dislike page ############## //

void User::dislikePage(Operation& system) throw (const char*)
{
	Page* page_to_dislike = getPageDetails(system, -1);
	bool found = false;

	if (page_to_dislike == nullptr)
	{
		throw "Page was not found.";
		return;
	}

	if (_numOfPages != _likedPages.size()) throw "miscalculating the size of _likedPages array.";

	for (int i = 0; i < _numOfPages && !found; i++)
	{
		// we didnt do for both sides!
		if (page_to_dislike == _likedPages[i]) // page is in likedPages
		{
			// there is only one page in the array, or the page to dislike is the last one
			if (i == _numOfPages - 1)
				_likedPages[i] = nullptr;

			else // in the "middle"
			{
				_likedPages[i] = _likedPages[_numOfPages - 1];
				_likedPages[_numOfPages - 1] = nullptr;
			}
			_numOfPages--;
			page_to_dislike->removeFan(this);
			found = true;
		}
	}

	if (!found)
		throw "Page was not found on your Liked Pages list.";
	else
		cout << endl << this->getUserName() << " disliked " << page_to_dislike->getName() << endl << endl;
}

// ################## display 10 recent statuses ############## //

// 10 most recent statuses of all his friends 
void User::displayRecentStatusesOfaFriend(Operation* system) throw (const char*)
{
	const int NUM_STATUSES_TO_DISPLAY = 10;

	if (_numOfFriends == 0)
		throw "No friends to display.";

	for (int i = 0; i < _numOfFriends; i++) // go over friends list
	{
		cout << "---------------------------------" << endl;
		cout << "Friend's name: " << _friendsList[i]->getUserName() << endl;
		cout << _friendsList[i]->getUserName() << "'s 10 Most Recent Statuses Are:" << endl;
		vector<Status*> friend_status_list = _friendsList[i]->getAllStatuses();
		int num_statuses = _friendsList[i]->getNumOfStatuses();

		if (num_statuses == 0)
			throw "No statuses to display.";
		else
		{
			int stop_loop;
			(num_statuses < NUM_STATUSES_TO_DISPLAY) ? (stop_loop = 0) : (stop_loop = num_statuses - NUM_STATUSES_TO_DISPLAY);

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
		}
		cout << "---------------------------------" << endl;
	}
}


// shows all statuses of a chosen user
void User::displayAllStatuses()
{
	cout << endl << _name << "'s Statuses:\n";
	if (_numOfStatuses == 0) cout << "None." << endl << endl;
	else {
		for (int i = 0; i < _numOfStatuses; i++)
		{
			cout << "---------------------------------" << endl;
			cout << "Status #" << i + 1 << endl;
			cout << "Text: " << _statuses[i]->getText() << endl;
			cout << "Uploaded on: ";
			_statuses[i]->getStatusTime().displayDate();
			cout << " | ";
			_statuses[i]->getStatusTime().displayHour();
			cout << endl;
			cout << "---------------------------------" << endl;
		}
	}
	cout << endl;
}


// shows all friends of a user
void User::displayAllFriends() throw (const char*)
{
	cout << "\n" << _name << "'s friends:" << endl;
	int numOfFriends = this->getNumOfFriends();

	if (numOfFriends == 0)
		throw "No friends to display :(";
	else
	{
		cout << endl;
		for (int i = 0; i < numOfFriends; i++)
		{
			cout << "friend #" << i + 1 << ":\n";
			cout << "Name: " << _friendsList[i]->getUserName() << endl;
			cout << "Birthday: ";
			_friendsList[i]->_birthday.displayDate();
			cout << endl << endl;
		}
	}
}

// ################## d'tor ############## //

User::~User()
{
	//delete[] _name;

	/*for (int i = 0; i < _numOfStatuses; i++)
	{
		delete[] _statuses[i];
	}
	delete[] _statuses;*/

	/*for (int i = 0; i < _numOfPages; i++)
	{
		delete[] _likedPages[i];
	}
	delete[] _likedPages;*/

	/*for (int i = 0; i < _numOfFriends; i++)
	{
		delete[] _friendsList[i];
	}
	delete[] _friendsList;*/
}



// TODO check if we need these funcs
void User::addPageToLikedPagesList(Operation& system, Page* pageToLike)
{
	_likedPages.push_back(pageToLike);
	_numOfPages++;

	pageToLike->addFanToPage(system, *this);
}

