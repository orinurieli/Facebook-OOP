#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include <fstream>
#include <vector>
#include <string>
class User;
class Page;
class Operation;

#include "Operation.h"
#include "User.h"
#include "Page.h"
#include "Clock.h"

#define CLEAR_BUFFER -1
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
// void askForEntityUserOrPage(User* current_user, Page* current_page, Operation& system); // return pointer because null can be returned

void getUserOrPageInput(int userChoice, Operation& system);
Page* getPageDetails(Operation& system, int clearBuffer);
User* askForUsername(Operation& system, int flag);

// Files Functions
void storeObjects(const string& filename, vector<User*> users, vector<Page*> pages);
void readObjects(const string& filename, vector<User*>& users, vector<Page*>& pages);


void newTerminate();


#endif