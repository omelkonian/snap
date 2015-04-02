/*
 * ListListItem.h
 *
 *  Created on: 30 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "List.h"
#include "ListItem.h"

/**
 * List Item for a List containing lists.
 */
class ListListItem: public ListItem {
	List *list;
public:
	ListListItem(List *list);
	virtual ~ListListItem();

	List* getList();

	ListListItem *getNext();

	void print();
};
