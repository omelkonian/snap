/*
 * ForumListItem.h
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../communities/forum/Forum.h"
#include "ListItem.h"

class ForumListItem: public ListItem {
	Forum *forum;
public:
	ForumListItem(Forum *forum);
	virtual ~ForumListItem();

	ForumListItem* getNext();

	Forum* getForum();

	void print();
};
