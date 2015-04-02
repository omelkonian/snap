/*
 * List.cpp
 *
 *  Created on: 3 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include <assert.h>
#include "List.h"
#include "Queue.h"
#include "../BucketList.h"
#include "EdgeListItem.h"
#include "IntegerListItem.h"
#include "ListListItem.h"
#include "GraphListItem.h"
#include "../queries/TrendListItem.h"
#include "../queries/StalkerListItem.h"

using namespace std;

List::List() {
	this->size = 0;
	this->head = NULL;
	this->tail = NULL;
}

int List::getSize() {
	return size;
}

List::~List() {
//	cout << "Deleting List" << endl;

	if ((this->head == NULL) || (this->tail == NULL) || (this->isEmpty()) || (dynamic_cast<BucketList*>(this) != 0) || (dynamic_cast<Queue*>(this) != 0))
		return;

	ListItem *cur = this->head;
	while (cur && (!(this->isEmpty()))) {
		ListItem *temp = cur;
		cur = cur->getNext();
		delete temp;
		this->size--;
	}
}

bool List::isEmpty() {
	return (this->size == 0);
}

bool List::insertItem(ListItem* item) {
	if (this->head == NULL) {
		assert(this->tail == NULL);
		this->head = item;
		this->tail = item;
	} else {
		assert(this->tail != NULL);
		ListItem *temp = this->tail;
		temp->setNext(item);
		item->setPrevious(temp);
		this->tail = item;
	}
	this->size++;
	return true;
}

ListItem* List::getHead() {
	return this->head;
}

ListItem* List::getTail() {
	return this->tail;
}

bool List::deleteItem(ListItem* item) {
	if (item == this->head && item == this->tail) {
		this->head = NULL;
		this->tail = NULL;
	} else if (item == this->head) {
		this->head = item->getNext();
		this->head->setPrevious(NULL);
	} else if (item == this->tail) {
		this->tail = item->getPrevious();
		item->getPrevious()->setNext(NULL);
	} else {
		item->getPrevious()->setNext(item->getNext());
		item->getNext()->setPrevious(item->getPrevious());
	}

	this->size--;
	delete item;
	return true;
}

void List::print() {
	cout << "________________________________________" << endl;
	cout << "Printing List" << endl;
	cout << "    Size: " << this->size << endl;
	cout << ((this->head) ? ("    got head") : ("    no head")) << endl;
	cout << ((this->tail) ? ("    got tail") : ("    no tail")) << endl;
}

void List::printElements() {
	cout << "Printing List Elements" << endl;
	ListItem *cur = this->head;
	while (cur != NULL) {
		cur->print();
		cur = cur->getNext();
	}
}

void List::setNull() {
	this->head = NULL;
	this->tail = NULL;
}

bool List::contains(ListItem* item) {
	ListItem *cur = this->head;
	while (cur) {
		if (cur == item)
			return true;
		cur = cur->getNext();
	}
	return false;
}
