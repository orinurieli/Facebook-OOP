// Gon Etgar 316354653
// Ori Nurieli 208952341
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "User.h"
#include "Operation.h"
#include "Status.h"
#include "Page.h"
#include "Functions.h"

int main()
{
	Operation system;
	//vector<User*> initUsers;
	//vector<Page*> initPages;
	int userChoice = 0;

	// ################################ Initiate data ################################
	//initUsers = initiateUsers();
	//initPages = initiatePages(system, initUsers);
	//system.initiateData(initUsers, initPages);
	set_terminate(newTerminate);

	// ################################ Menu ################################ 
	cout << "Hello, Welcome To Facebook :)" << endl << endl;
	do {
		try
		{
			userChoice = displayMenu();

			if (userChoice == 12)
			{
				cout << "Goodbye.";
				break;
			}

			system.handleMenu(userChoice);
		}
		catch (const char* err)
		{
			cout << endl << "error thrown: " << err << endl << endl;
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

	//deleteUsersAndPages(initUsers, initPages);
	return 0;
}