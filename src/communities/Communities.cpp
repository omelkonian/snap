/*
 * Communities.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: athan
 */
#include "Communities.h"
#include "../list/CommunityListItem.h"
#include "../list/IntegerListItem.h"
#include <iostream>

using namespace std;
Communities::Communities(List* communitiesList) {
	this->communitiesList = communitiesList;
}

Communities::~Communities() {
//	cout<<"Deleting Communities"<<endl;
	delete this->communitiesList;
}

void Communities::setCommunitiesList(List* communitiesList) {
	this->communitiesList = communitiesList;
}

List* Communities::getCommunitiesList() {
	return this->communitiesList;
}

int Communities::getCommunity(int nodeID) {
	CommunityListItem *cli = (CommunityListItem*) this->communitiesList->getHead();
	while (cli) {
		Community *com = cli->getCommunity();
		IntegerListItem *ili = (IntegerListItem*) com->getCommunityMembers()->getHead();
		while (ili) {
			if (ili->getInt() == nodeID)
				return com->getCommunityId();
			ili = ili->getNext();
		}
		cli = cli->getNext();
	}
	return -1;
}

void Communities::print() {
	cout << "Printing Communities" << endl;
	CommunityListItem *cli = (CommunityListItem*) this->communitiesList->getHead();
	while (cli) {
		cli->getCommunity()->print();
		cli = cli->getNext();
	}
}
