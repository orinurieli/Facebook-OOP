# C++ Facebook Project

## Getting Started

1. Clone the repository using `git clone https://github.com/[username]/cpp-facebook.git`
2. Navigate to the project directory using `cd cpp-facebook`
3. Compile the program using `g++ main.cpp -o facebook`
4. Run the program 

## OOP Usage

This project emphasizes the usage of OOP programming, building classes, and adhering to the 4 OOP principles: 
- Encapsulation
- Inheritance
- Polymorphism
- Abstraction

## Realization Of Principles

- Working with an Abstract class called `Status` is used as a base class for creating different types of status updates. Three classes, `TextStatus`, `ImageStatus`, and `VideoStatus`, inherit from it.
- We utilized a parent class called Entity for the User and Page classes, which inherit from it and utilize polymorphism for additional functions.

## Options Menu
The program will start with a main menu where you can select various options:

1. Add new user
2. Add new page
3. Create a new status
4. Display all statuses
5. Display all 10 recent statuses of all your friends
6. Add a new friend
7. Unfriend
8. Like a page
9. Unlike a page
10. Display all entities of Facebook
11. Display all friends of a friend or page
12. Exit

Please note that text DB file will start empty. 
You can add users with the features we've built and then press 12 to save data.
The file will be created automatically in your project file.

## Working with Files

The program uses a file to store the data of users, pages, and status updates. 
The data is saved to the file when the user chooses option 12 from the main menu 
and read from the file when the program starts. 

The following function is used to store the data to the file:
```C++
void Operation::storeObjects(const string& filename)
{
	ofstream out(filename, ios::trunc); // open file for writing

	writeAllUsersAndPagesToFile(out); // write all names of the entities (users and pages)
	writeEachUsersDetails(out); // for each user write its details
	writeEachPagesDetails(out); // for each page write its details

	out.close();
}
```

## Error handling
The program uses C++ exceptions to handle errors. 
Exceptions are thrown using the throw keyword and can be caught using the 'catch' keyword. 
The try and catch block is used to handle the exception. 
Here's an example of how we used it:

```C++
try
{
	userChoice = displayMenu();

	if (userChoice == Exit)
	{
		system.storeObjects(FILE_NAME);
		cout << "Saving data to DB." << endl;
		cout << "Goodbye.";
		break;
	}

	system.handleMenu(userChoice);
}
catch (const char* err)
{
	cout << endl << "Error thrown: " << err << endl << endl;
}
catch (std::invalid_argument& err)
{
	cout << endl << "Invalid Argument: " << err.what() << endl << endl;
}
catch (std::exception& err)
{
	cout << endl << "General Error: " << err.what() << endl << endl;
}
```

## User Class Instance
- The class is a representation of a user object in our Facebook project:

```C++
class User {
private:
    string _name;
    vector<User*> _friends;
    vector<Page*> _likedPages;
    vector<Status*> _statuses;
    Clock _birthday;
public:
    void addFriend(Operation& system) throw (const char*);
    void cancelFriendship(Operation& system) throw (const char*);
    void likePage(Operation& system) throw (const char*);
    void dislikePage(Operation& system) throw (const char*);
    void createNewStatus(Operation& system);
};
```
  
- The addFriend function connects two users by taking a username and checking if the friend is already on the list or if the user is adding themselves, then throws an exception.
- The cancelFriendship function cancels friendship between two users by taking a username and checking if the friend is on the list, then throws an exception if the friend is not found.
- The likePage function adds a page to the user's liked pages by taking a page's name and checking if the user already liked this page, then throws an exception if the user already liked the page.
- The dislikePage function removes a page from the user's liked pages by taking a page's name and checking if the page exists, then throws an exception if the page is not found.
  
 ## Contributing

We welcome contributions to the project, whether it's fixing a bug, adding a new feature, or improving the documentation. Here's how you can help:

1. Fork the repository and clone it to your local machine.
2. Create a new branch for your changes.
3. Make your changes and test them thoroughly.
4. Commit your changes and push them to your fork.
5. Submit a pull request and describe the changes you made.

Please ensure that all new code adheres to the 4 OOP principles: Encapsulation, Inheritance, Polymorphism, and Abstraction.


## Author

##### Made by [Ori Nurieli](https://github.com/orinurieli)  

