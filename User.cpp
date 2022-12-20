#include <iostream>
using namespace std;
#include "User.h"
#include "Functions.h"

#define NOT_FOUND -1

class Page;

// ################## c'tor ############## //

User::User(const char* name, Clock birthday, int maxNumFriends, int numFriends, int maxPages, int numPages)
{
	_name = new char[MAX_CHARACTERS];
	_name = _strdup(name);
	_birthday = birthday;

	_maxNumOfFriends = maxNumFriends;
	_numOfFriends = numFriends;

	_maxNumOfPages = maxPages;
	_numOfPages = numPages;

	_statuses = new Status * [_maxNumOfStatuses];
	//_likedPages = new Page * [_maxNumOfPages];
	//_friendsList.resize(1);
}

// ################## create status ############## //

void User::createStatus(Status* initStatus)
{
	this->reallocStatuses();

	if (initStatus != nullptr) _statuses[_numOfStatuses] = initStatus;

	else {
		Status* newStatus = new Status();
		newStatus->getStatusInfo(newStatus);
		cout << "Status Uploaded!" << endl << endl;
		_statuses[_numOfStatuses] = newStatus;
	}
	_numOfStatuses++;
}

// ################## add friend ############## //

// this function connects 2 users to be friends
void User::addFriend(Operation* system)
{
	User* friendToAdd = askForUsername(system, 1);

	if (friendToAdd == nullptr)
		return;

	/*this->reallocFriendList();
	friendToAdd->reallocFriendList();*/

	*this += friendToAdd;
	cout << "\n" << _name << ", you have added " << friendToAdd->_name << " to your friend list." << endl << endl;
}

// after we checked for place in both arrays, we add both users to eachothers friend list.
User* User::operator+=(User* other)
{
	_friendsList.push_back(other);
	_numOfFriends++;

	other->_friendsList.push_back(this);
	other->_numOfFriends++;

	return this;
}

// ################## unfriend ############## //

// this function cancel friendship between 2 users
void User::cancelFriendship(Operation& system)
{
	User* friend_to_delete = askForUsername(&system, 1);
	if (friend_to_delete == nullptr)
		return;

	int friend_index = this->searchFriendInFriendList(*friend_to_delete);
	if (friend_index == NOT_FOUND)
		return;

	int user_index = friend_to_delete->searchFriendInFriendList(*this);

	this->removeFriendFromFriendList(friend_index);
	friend_to_delete->removeFriendFromFriendList(user_index);

	cout << "\n" << _name << ", you have removed " << friend_to_delete->_name << " from your friend list." << endl << endl;
}

// searches a friend in the user's friend list
int User::searchFriendInFriendList(User& other)
{
	int friend_to_delete_index = NOT_FOUND;

	for (int i = 0; i < _numOfFriends && friend_to_delete_index == NOT_FOUND; i++)
	{
		if (strcmp(_friendsList[i]->_name, other._name) == 0)
			friend_to_delete_index = i;
	}

	if (friend_to_delete_index == NOT_FOUND)
		cout << "The friend was not found on your friend list!\n\n";

	return friend_to_delete_index;
}

// removes "friendToRemove" from friend list, if he's not in the end of the array, switch between the last friend to him. 
void User::removeFriendFromFriendList(int indexToRemove)
{
	_friendsList[indexToRemove] = nullptr; // point the friend's place in the array on null

	if (_numOfFriends > 1 && indexToRemove != _numOfFriends - 1)
	{// if friend is not last, and there is more than 1 friend on the array, switch between the last one on the array to the one we deleted
		_friendsList[indexToRemove] = _friendsList[_numOfFriends - 1];
		_friendsList[_numOfFriends - 1] = nullptr;
	}
	_numOfFriends--; // update number of friends
}

// ################## like page ############## //

void User::likePage(Operation& system)
{
	Page* new_page = getPageDetails(&system);
	if (new_page == nullptr)
	{
		cout << "Page doesn't exist.\n";
		return;
	}

	//this->reallocPagesList(); // check if user has enough space for the page, and realloc if needed
	*this += new_page; // add page to the user's likedPages list
	new_page->addFanToPage(&system, this); // add user to the page's fansList

	cout << _name << " liked " << new_page->getName() << endl << endl;
}

User* User::operator+=(Page* fanPage) // add page to user's liked pages array
{
	_likedPages.push_back(fanPage);
	_numOfPages++;
	return this;
}

// ################## dislike page ############## //

void User::dislikePage(Operation* system)
{
	Page* page_to_dislike = getPageDetails(system);
	bool found = false;

	if (page_to_dislike == nullptr)
	{
		cout << "Page was not found." << endl;
		return;
	}

	for (int i = 0; i < _numOfPages && !found; i++)
	{
		// Error: _likedPages is empty
		// we didnt do for both sides!
		if (page_to_dislike == _likedPages[i]) // page is in likedPages
		{
			// there is only one page in the array, or the page to dislike is the last one
			if (i == _numOfPages - 1)
				_likedPages[i] = nullptr;

			else // in the "middle"
			{ // swap the one we dislike, with the last one
				_likedPages[i] = _likedPages[_numOfPages - 1];
				_likedPages[_numOfPages - 1] = nullptr;
			}
			_numOfPages--;
			page_to_dislike->removeFan(this);
			found = true;
		}
	}

	if (!found)
		cout << "Page was not found on your Liked Pages list." << endl << endl;
	else
		cout << endl << this->getName() << " disliked " << page_to_dislike->getName() << endl << endl;
}

// ################## display 10 recent statuses ############## //

// 10 most recent statuses of all his friends
void User::displayRecentStatusesOfaFriend(Operation* system)
{
	const int NUM_STATUSES_TO_DISPLAY = 10;

	if (_numOfFriends == 0)
		cout << "No friends to display." << endl << endl;
	for (int i = 0; i < _numOfFriends; i++) // go over friends list
	{
		cout << "---------------------------------" << endl;
		cout << "Friend's name: " << _friendsList[i]->getName() << endl;
		cout << _friendsList[i]->getName() << "'s 10 Most Recent Statuses Are:" << endl;
		Status** friend_status_list = _friendsList[i]->getAllStatuses();
		int num_statuses = _friendsList[i]->getNumOfStatuses();

		if (num_statuses == 0)
			cout << "No statuses to display." << endl;
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

// ################## display all statuses ############## //

// shows all statuses of a chosen user
void User::displayAllStatuses()
{
	cout << endl << _name << "'s Statuses:\n";
	if (_numOfStatuses == 0) cout << "None." << endl;
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
			cout << "---------------------------------" << endl << endl;
		}
	}
}

// ################## display all friends ############## //

// shows all friends of a user
void User::displayAllFriends()
{
	cout << "\n" << _name << "'s friends:" << endl;
	// gon i changed numOfFriends to _friendsList.size()
	if (_friendsList.size() == 0)
		cout << "None :(" << endl << endl;
	else
	{
		cout << "inside else" << endl;
		cout << endl;
		for (int i = 0; i < _friendsList.size(); i++)
		{
			cout << "friend #" << i + 1 << ":\n";
			cout << "Name: " << _friendsList[i]->getName() << endl;
			cout << "Birthday: ";
			_friendsList[i]->_birthday.displayDate();
			cout << endl << endl;
		}
	}
}

// ################## d'tor ############## //

User::~User()
{
	delete[] _name;

	for (int i = 0; i < _numOfStatuses; i++)
	{
		delete[] _statuses[i];
	}
	delete[] _statuses;

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

// checks if the array reaches its physical size, and increases it if needed.
void User::reallocStatuses()
{
	if (_maxNumOfStatuses == _numOfStatuses)
	{
		_maxNumOfStatuses *= 2;
		Status** newStatuses = new Status * [_maxNumOfStatuses];

		for (int i = 0; i < _numOfStatuses; i++)
			newStatuses[i] = _statuses[i];

		delete[] _statuses;
		_statuses = newStatuses;
	}
}

// checks if the array reaches its physical size, and increases it if needed.
//void User::reallocFriendList()
//{
//	if (_numOfFriends == _maxNumOfFriends)
//	{
//		_maxNumOfFriends *= 2;
//		vector<User*> newFriendList = new User * [_maxNumOfFriends];
//
//		for (int i = 0; i < _numOfFriends; i++)
//			newFriendList[i] = _friendsList[i];
//
//		delete[]_friendsList;
//		_friendsList = newFriendList;
//	}
//}

// checks if the pages list has enough space, and if not increases it
//void User::reallocPagesList()
//{
//	if (_numOfPages == _maxNumOfPages)
//	{
//		_maxNumOfPages *= 2;
//		vector<Page*> new_liked_pages = new Page * [_maxNumOfPages];
//
//		for (int i = 0; i < _numOfPages; i++)
//			new_liked_pages[i] = _likedPages[i];
//
//		_likedPages = new_liked_pages;
//		new_liked_pages = nullptr;
//		delete[] new_liked_pages;
//	}
//}


// TODO check if we need these funcs
void User::addPageToLikedPagesList(Operation* system, Page* pageToLike)
{
	_likedPages.push_back(pageToLike);
	/*if (_numOfPages == _maxNumOfPages)
	{
		_maxNumOfPages *= 2;
		vector<Page*> new_liked_pages = new Page * [_maxNumOfPages];

		for (int i = 0; i < _numOfPages; i++)
			new_liked_pages[i] = _likedPages[i];

		_likedPages = new_liked_pages;
		new_liked_pages = nullptr;
		delete[] new_liked_pages;
	}

	_likedPages[_numOfPages] = pageToLike;*/
	_numOfPages++;

	// here add fan to page:
	pageToLike->addFanToPage(system, this);
}

// receives pointer to a page or null
void User::likePageTemp(Page* pageToLike, Operation* system)
{
	if (pageToLike != nullptr) // we need to add this page to user
	{
		addPageToLikedPagesList(system, pageToLike);
		cout << _name << " liked " << pageToLike->getName() << endl;
	}
	else // we need to ask the user which page to add
	{
		Page* new_page = getPageDetails(system);
		if (new_page == nullptr)
		{
			cout << "Page doesn't exist.\n";
			return;
		}

		addPageToLikedPagesList(system, new_page);
		cout << endl << this->getName() << " liked " << new_page->getName() << endl << endl;
	}
}

// todo - delete this func
// ask for name and search it on allUsers array, returns the user's index, or -1 if not found
int User::askForName(Operation* system, int flag)
{
	char* username = new char[MAX_CHARACTERS];
	int userIndex;

	cout << "Please enter ";
	flag == 0 ? cout << "your username: " : cout << "friend's name: ";
	cin.getline(username, MAX_CHARACTERS);
	userIndex = doesUserExist(username, system);
	if (userIndex == NOT_FOUND)
		cout << "User not found!\n\n";

	delete[] username;
	return userIndex;
}