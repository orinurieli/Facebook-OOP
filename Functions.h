#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "Operation.h"
#include "Page.h"
#include "Status.h"

class User;

int displayMenu();
int doesUserExist(const char* name, Operation* system);
int doesPageExist(const char* name, Operation* system);

User** initiateUsers();
void initiateFriendships(User** allUsers);
Page** initiatePages(Operation* system, User** allUsers);
void initiatePageLikes(Operation* system, User** allUsers, Page** pages);
void initiateStatuses(Operation* system);

void getUserInput(Operation* system);
void addPageToSystem(Operation* system);
void getUserOrPageInput(int userChoice, Operation* system);
Page* getPageDetails(Operation* system);
User* askForUsername(Operation* system, int flag);

#endif // __FUNCTIONS_H