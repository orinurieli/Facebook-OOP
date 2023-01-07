#include "Entity.h"
#include <iostream>
using namespace std;

void Entity::createStatus()
{
	Status* newStatus = new Status();
	newStatus->getStatusInfo(*newStatus);
	cout << "Status Uploaded!" << endl << endl;
	_statuses.push_back(newStatus);
	_numOfStatuses++;
}

