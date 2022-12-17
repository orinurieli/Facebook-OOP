// Gon Etgar 316354653
// Ori Nurieli 208952341
#include <iostream>
using namespace std;

#include "User.h"
#include "Operation.h"
#include "Status.h"
#include "Page.h"
#include "Functions.h"

int main()
{
	Operation system;
	User** initUsers = new User * [5]; // todo -> free??
	Page** initPages = new Page * [3];
	int userChoice = 0;

	// ################################ initiate data ################################

	initUsers = initiateUsers();
	initPages = initiatePages(&system, initUsers);
	system.initiateData(initUsers, initPages);

	cout << "Hello, Welcome To Facebook :)" << endl << endl;

	//// ################################ Menu ################################ 

	do {
		userChoice = displayMenu();
		system.handleMenu(userChoice);
	} while (userChoice > 0 || userChoice < 13);

	return 0;
}