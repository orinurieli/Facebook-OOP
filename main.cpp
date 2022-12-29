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

// general TODO //
// 1. change all the getters to const ref
// 2. in general change objects in funcs to ref or const
// 3. change to string
// 4. in page ctor check if there is memory leak
// 5. delete all the things we put in HEARA
// 6. initUser and initPages -> move to Operaton c'tor?

int main()
{
	Operation system;
	vector<User*> initUsers; // todo -> free??
	vector<Page*> initPages;
	int userChoice = 0;

	// ################################ Initiate data ################################
	initUsers = initiateUsers();
	initPages = initiatePages(system, initUsers);
	system.initiateData(initUsers, initPages);

	//set_terminate(newTerminate);

	// ################################ Menu ################################ 
	cout << "Hello, Welcome To Facebook :)" << endl << endl;
	do {
		try
		{
			userChoice = displayMenu();
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
	} while (userChoice > 0 || userChoice < 13);

	return 0;
}