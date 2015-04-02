/*
 * ListItem.h
 *
 *  Created on: 3 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../Node.h"

/**
 * The item that a List can hold.
 * May be Edge or Bucket or BucketItem.
 */
class ListItem {
protected:
	ListItem *next;
	ListItem *previous;
public:
	ListItem();
	ListItem(ListItem& other);
	virtual ~ListItem();

	ListItem* getNext();
	void setNext(ListItem *next);
	ListItem* getPrevious();
	void setPrevious(ListItem* previous);

	ListItem* getListItem();

	void printType();

	virtual void print();
};
