/*
 * CommunityListItem.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: athan
 */
#include "CommunityListItem.h"
#include <iostream>

using namespace std;

CommunityListItem::CommunityListItem(Community* community) {
	this->community = community;
}

CommunityListItem::~CommunityListItem() {
	//cout<<"Deleting CommunityListItem"<<endl;
	delete this->community;
}

CommunityListItem* CommunityListItem::getNext() {
	return ((CommunityListItem*) this->next);
}

Community* CommunityListItem::getCommunity() {
	return this->community;
}

void CommunityListItem::print() {
	this->community->print();
}

