// Gon Etgar 316354653 
// Ori Nurieli 208952341
// Ex3
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "User.h"
#include "Operation.h"
#include "Status.h"
#include "Page.h"
#include "Functions.h"

const string& FILE_NAME = "Facebook_DataBase.txt";

int main()
{
	Operation system;
	int userChoice = 0;

	set_terminate(newTerminate);

	// ################################ Menu ################################ 
	cout << "Hello, Welcome To Facebook :)" << endl << endl;
	do {
		try
		{
			userChoice = displayMenu();

			if (userChoice == Exit)
			{
				cout << "inserting data to file...   "
					<< system.getAllUsers().size() << " users and "
					<< system.getAllPages().size() << " pages" << endl;

				storeObjects(FILE_NAME, system.getAllUsers(), system.getAllPages());
				cout << "Goodbye.";
				// todo: delete next line- only for debug
				cin >> userChoice;
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
	} while (userChoice > 0 || userChoice < 12);

	return 0;
}