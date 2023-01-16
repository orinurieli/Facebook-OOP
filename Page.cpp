#include <iostream>
using namespace std;

#include "Page.h"
#include "Operation.h"

// adds user to fan list
Page& Page::operator+=(User& currentUser)
{
	_friends.push_back(&currentUser);
	return *this;
}

// compare number of fans between two pages
bool Page::operator<(Page& other)
{
	return (_friends.size() < other._friends.size());
}

// compare number of fans between two pages
bool Page::operator>(Page& other)
{
	return (_friends.size() > other._friends.size());
}

// compare the page's number of fans to a user's number of friends
bool Page::operator<(User& currentUser)
{
	return (_friends.size() < currentUser.getFriendsList().size());
}

// compare the page's number of fans to a user's number of friends
bool Page::operator>(User& currentUser)
{
	return (_friends.size() > currentUser.getFriendsList().size());
}

ostream& Page::operator<<(ostream& out) {
	out << getName();

	out << _friends.size();
	for (int i = 0; i < _friends.size(); i++) {
		out << " ";
		out << _friends[i]->getName();
		// out << _friends[i]->getBirthday();
		out << _friends[i]->getBirthday().getDay() << " ";
		out << _friends[i]->getBirthday().getMonth() << " ";
		out << _friends[i]->getBirthday().getYear() << " ";
		out << _friends[i]->getBirthday().getHours() << " ";
		out << _friends[i]->getBirthday().getMinutes() << " ";
		out << _friends[i]->getBirthday().getSeconds() << " ";
	}

	out << _statuses.size();
	for (int i = 0; i < _statuses.size(); i++) {
		string classType = typeid(*_statuses[i]).name() + 6;

		out << " ";
		out << classType;
		out << _statuses[i]->getText();
		out << " ";
		// out << _statuses[i]->getStatusTime();
		out << _statuses[i]->getStatusTime().getDay() << " ";
		out << _statuses[i]->getStatusTime().getMonth() << " ";
		out << _statuses[i]->getStatusTime().getYear() << " ";
		out << _statuses[i]->getStatusTime().getHours() << " ";
		out << _statuses[i]->getStatusTime().getMinutes() << " ";
		out << _statuses[i]->getStatusTime().getSeconds() << " ";

		if (classType.compare("VideoStatus"))
			cout << dynamic_cast<VideoStatus*>(_statuses[i])->getVideoUrl();
		else if (classType.compare("ImageStatus"))
			cout << dynamic_cast<ImageStatus*>(_statuses[i])->getImageUrl();
	}

	return out;
}

istream& Page::operator>>(istream& in)
{
	string name;
	in >> name;
	Page* page = new Page(name);

	int numFriends;
	in >> numFriends;
	for (int i = 0; i < numFriends; i++) {
		string friendName;
		in >> friendName;
		int day, month, year;
		in >> day >> month >> year;
		Clock friendBirthday(day, month, year);

		page->getFriendsList().push_back(new User(friendName, friendBirthday));
	}

	int numStatuses;
	in >> numStatuses;
	for (int i = 0; i < numStatuses; i++) {
		string statusType;
		in >> statusType;
		string text;
		in >> text;
		int day, month, year;
		in >> day >> month >> year;
		Clock statusTime = Clock(day, month, year);

		if (statusType == "VideoStatus") {
			string videoUrl;
			in >> videoUrl;
			// create a new VideoStatus object and add it to the page's statuses
			page->getStatusesList().push_back(new VideoStatus(text, statusTime, videoUrl));
		}
		else if (statusType == "ImageStatus") {
			string imageUrl;
			in >> imageUrl;
			// create a new ImageStatus object and add it to the page's statuses
			page->getStatusesList().push_back(new ImageStatus(text, statusTime, imageUrl));
		}
		else {
			// create a new Status object and add it to the page's statuses
			page->getStatusesList().push_back(new TextStatus(text, statusTime));
		}
	}

	return in;
}



// ask from user name of a page and checks if the page exists in the system
Page* Page::askForPageName(Operation& system) // *returns a pointer because NULL can be returned*
{
	vector<Page*> allPages = system.getAllPages();
	string page_name;

	cout << "Enter page name: ";
	cin.ignore();
	getline(cin, page_name);

	int index = 0;

	index = doesPageExist(page_name, system);

	if (index >= 0)
		return allPages[index];
	else
		return nullptr;
}

// receives fan and adds him to the page's fan list
void Page::addFanToPage(Operation& system, User& currentUser)
{
	*this += currentUser;
}

// this function receives pointer to a user and removes it from array of fans.
void Page::removeFan(User& removeUser) throw (const char*)
{
	//int num_of_fans = _fansList.size();
	int num_of_fans = _friends.size();
	bool found = false;

	for (int i = 0; i < num_of_fans && !found; i++)
	{
		//if (&removeUser == _fansList[i]) // user is a fan
		if (&removeUser == _friends[i]) // user is a fan
		{
			if (i != num_of_fans - 1) // if it's not the last - put it last
			{
				//User* tmp = _fansList[i];
				//_fansList[i] = _fansList[num_of_fans - 1];
				//_fansList[num_of_fans - 1] = tmp;

				// switch between them
				User* tmp = _friends[i];
				_friends[i] = _friends[num_of_fans - 1];
				_friends[num_of_fans - 1] = tmp;
			}
			_friends.pop_back(); // delete the last one
			found = true;
		}
	}

	if (!found)
		throw "wait.. the user is not a fan so we can not remove him. \n";
}