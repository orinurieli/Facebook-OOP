#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include <fstream>
#include <vector>
#include <string>
#include "Operation.h"
#include "User.h"
#include "Page.h"
#include "Clock.h"
class User;
class Page;
class Operation;

#define CLEAR_BUFFER -1
#define NOT_FOUND -1
#define PAGE 0
#define USER 1
#define FRIEND 2

int displayMenu();
User* searchUserByName(string& name, Operation& system); // *can return null!*
Page* searchPageByName(string& name, Operation& system); // *can return null!*
int doesPageExist(string& name, Operation& system);
void getUserInput(Operation& system);
void addPageToSystem(Operation& system);
int askUserOrPage();
void getUserOrPageInput(int userChoice, Operation& system);
Page* getPageDetails(Operation& system, int clearBuffer); // *can return null!*
User* askForUsername(Operation& system, int flag); // *can return null!*
void newTerminate();


#endif