/*
 * ThreadListItem.cpp
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#include "ThreadListItem.h"

ThreadListItem::ThreadListItem(pthread_t *threadID) {
	this->threadID = threadID;
}

ThreadListItem::~ThreadListItem() {
}

pthread_t* ThreadListItem::getThreadID() {
	return this->threadID;
}

ThreadListItem* ThreadListItem::getNext() {
	return (ThreadListItem*) this->next;
}
