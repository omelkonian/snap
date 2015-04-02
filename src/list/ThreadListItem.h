/*
 * ThreadListItem.h
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#pragma once
#include <pthread.h>
#include "ListItem.h"

class ThreadListItem: public ListItem {
	pthread_t *threadID;
public:
	ThreadListItem(pthread_t *threadID);
	virtual ~ThreadListItem();

	pthread_t* getThreadID();

	ThreadListItem* getNext();
};
