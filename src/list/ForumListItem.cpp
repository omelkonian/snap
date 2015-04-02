/*
 * ForumListItem.cpp
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#include "ForumListItem.h"
#include <iostream>

using namespace std;

ForumListItem::ForumListItem(Forum *forum) {
	this->forum = forum;
}

ForumListItem::~ForumListItem() {
	delete this->forum;
}

ForumListItem* ForumListItem::getNext() {
	return ((ForumListItem*) this->next);
}

Forum* ForumListItem::getForum() {
	return this->forum;
}

void ForumListItem::print() {
	cout << "  forumID: " << this->forum->getForumID() << endl;
	cout << "  memberNo: " << this->forum->getMemberNo() << endl;
}
