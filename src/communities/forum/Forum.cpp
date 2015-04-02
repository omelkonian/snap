/*
 * Forum.cpp
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#include "Forum.h"
#include <iostream>
using namespace std;

Forum::Forum(int forumID, int memberNo) {
	this->forumID = forumID;
	this->memberNo = memberNo;
}

Forum::~Forum() {
}

int Forum::getForumID() {
	return this->forumID;
}

int Forum::getMemberNo() {
	return this->memberNo;
}

void Forum::print() {
	cout << "ForumID: " << this->forumID << endl;
	cout << "#members: " << this->memberNo << endl;
}
