/*
 * ForumList.h
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../../list/List.h"
#include "Forum.h"

// List containing Forums and sorted by forum's memberNo.
class ForumList: public List {
	int limit; // used to minimize memory usage
public:
	ForumList(int limit);
	virtual ~ForumList();

	void insertForum(Forum *forum);

	Forum* removeHead();

	void update();
	void print();
};
