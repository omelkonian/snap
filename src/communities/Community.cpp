/*
 * Community.cpp
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#include "Community.h"
#include "../list/List.h"

#include <iostream>

using namespace std;
Community::Community(int communityID, List* communityMembers) {
	this->communityID = communityID;
	this->communityMembers = communityMembers;
}

Community::~Community() {
	//cout<<"Deleting Community"<<endl;
	delete this->communityMembers;
}

int Community::getCommunityId() {
	return this->communityID;
}

List* Community::getCommunityMembers() {
	return this->communityMembers;
}

void Community::print() {
	cout << "________________________________________" << endl;
	cout << "Printing Community" << endl;
	cout << "    ID: " << this->communityID << endl;
	this->communityMembers->printElements();
	cout << "________________________________________" << endl;
}
