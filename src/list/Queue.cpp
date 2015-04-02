/*
 * Queue.cpp
 *
 *  Created on: 5 Dec 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include <assert.h>
#include "Queue.h"

using namespace std;

Queue::Queue() {
	assert(this->size == 0);
	assert(this->head == NULL);
	assert(this->tail == NULL);
}

Queue::~Queue() {
//	cout << "Deleting Queue" << endl;
	ListItem *head = this->head;
	while ((head != NULL) && (!this->isEmpty())) {
		if (dynamic_cast<IntegerListItem*>(this->head) != 0) {
			this->dequeueAsInt();
		} else if (dynamic_cast<BucketItemListItem*>(this->head) != 0) {
			this->dequeueAsItem();
		} else if (dynamic_cast<ListListItem*>(this->head) != 0) {
			delete (ListListItem*) this->dequeue();
		} else if (dynamic_cast<ExtendedQueueItem*>(this->head) != 0) {
			delete (ExtendedQueueItem*) this->dequeue();
		} else {
			cout << "ERROR: Queue contains something other than Int, BucketItem, List." << endl;
		}
	}
	assert(this->size == 0);
}

bool Queue::enqueue(ListItem* item) {
	return List::insertItem(item);
}

ListItem* Queue::dequeue() {
	if (!this->isEmpty()) {
		ListItem *ret = this->head;
		if (this->size == 1) {
			this->head = NULL;
			this->tail = NULL;
		} else {
			this->head->getNext()->setPrevious(NULL);
			this->head = this->head->getNext();
		}
		this->size--;
		return ret;
	} else
		return NULL;
}

void Queue::print() {
	cout << "________________________________________" << endl;
	cout << "Printing Queue" << endl;
	this->List::print();
}

bool Queue::enqueueAsInt(int i) {
	IntegerListItem *ili = new IntegerListItem(i);
	if (!ili) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return false;
	}
	return this->enqueue(ili);
}

int Queue::dequeueAsInt() {
	int ret = -1;
	IntegerListItem *wrapper = (IntegerListItem*) this->dequeue();
	if (wrapper)
		ret = wrapper->getInt();
	delete wrapper;
	return ret;
}

bool Queue::enqueueAsItem(BucketItem* item) {
	BucketItemListItem *t = new BucketItemListItem(item);
	if (!t) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return false;
	}
	return this->enqueue(t);
}

BucketItem* Queue::dequeueAsItem() {
	BucketItem *ret = NULL;
	BucketItemListItem *wrapper = (BucketItemListItem*) this->dequeue();
	if (wrapper != NULL) {
		ret = wrapper->getElement();
		wrapper->setElement(NULL);
	}
	delete wrapper;
	return ret;
}

void Queue::printElements() {
	cout << "________________________________________" << endl;
	cout << "Printing Queue Elements" << endl;
	this->List::printElements();
}
