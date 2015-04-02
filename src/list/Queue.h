/*
 * Queue.h
 *
 *  Created on: 5 Dec 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "List.h"
#include "../BucketItem.h"
#include "BucketItemListItem.h"
#include "IntegerListItem.h"
#include "ListListItem.h"
#include "ExtendedQueueItem.h"

#include <iostream>

using namespace std;

/**
 * Queue holding BucketItems needed for BFS.
 */
class Queue: public List {
public:
	Queue();
	virtual ~Queue();

	bool enqueue(ListItem *item);
	ListItem* dequeue();

	/* When enqueueing as integer, caller must then dequeue as integer. */
	bool enqueueAsInt(int i);
	int dequeueAsInt();

	/* When enqueueing as item, caller must then dequeue as item. */
	bool enqueueAsItem(BucketItem *item);
	BucketItem* dequeueAsItem();

	void print();
	void printElements();
};
