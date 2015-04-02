/*
 * ExtendedQueueItem.h
 *
 *  Created on: 18 …·Ì 2015
 *      Author: Orestis Melkonian
 */

#pragma once
#include "ListItem.h"
#include "../BucketItem.h"

class ExtendedQueueItem: public ListItem {
	BucketItem *node;
	List *path;
public:
	ExtendedQueueItem(BucketItem *node, List *path);
	virtual ~ExtendedQueueItem();

	ExtendedQueueItem* getNext();
	ExtendedQueueItem* getPrevious();

	int getDepth();
	BucketItem* getNode();
	List* getPath();

	void print();
};
