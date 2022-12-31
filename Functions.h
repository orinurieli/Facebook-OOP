#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "Operation.h"
#include "User.h"
#include "Page.h"

#include <vector>
#include <string>
class User;
class Page;

#define NOT_FOUND -1
#define PAGE 0
#define USER 1
#define FRIEND 2

int displayMenu();
int doesUserExist(string& name, Operation& system);
int doesPageExist(string& name, Operation& system);

vector<User*> initiateUsers();
void initiateFriendships(vector<User*> allUsers);
vector<Page*> initiatePages(Operation& system, vector<User*> allUsers);
void initiatePageLikes(Operation& system, vector<User*> allUsers, vector<Page*> pages);
void initiateStatuses(Operation& system);

void getUserInput(Operation& system);
void addPageToSystem(Operation& system);

int askUserOrPage();
//void getUserOrPageInput(int userChoice, Operation& system);
void getUserOrPageInput2(int userChoice, Operation& system);
Page* getPageDetails(Operation& system, int clearBuffer);
User* askForUsername(Operation& system, int flag);

void newTerminate();
void deleteUsersAndPages(vector<User*> initUsers, vector<Page*>initPages);


#endif