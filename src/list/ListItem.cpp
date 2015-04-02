/*
 * ListItem.cpp
 *
 *  Created on: 3 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <stdlib.h>
#include <iostream>
#include "ListItem.h"
#include "EdgeListItem.h"
#include "BucketListItem.h"
#include "BucketItemListItem.h"
#include "IntegerListItem.h"
#include "ListListItem.h"
#include "GraphListItem.h"
#include "ExtendedQueueItem.h"
#include "../queries/StalkerListItem.h"
#include "../queries/TrendListItem.h"

using namespace std;

ListItem::ListItem() {
	this->next = NULL;
	this->previous = NULL;
}

ListItem::~ListItem() {
//	cout << "Deleting ListItem" << endl;
}

ListItem* ListItem::getNext() {
	return next;
}

ListItem* ListItem::getPrevious() {
	return previous;
}

void ListItem::setNext(ListItem* next) {
	this->next = next;
}

void ListItem::setPrevious(ListItem* previous) {
	this->previous = previous;
}

void ListItem::print() {
	cout << "________________________________________" << endl;
	cout << "Printing ListItem:" << endl;
	if (dynamic_cast<EdgeListItem*>(this))
		((EdgeListItem*) this)->print();
	else if (dynamic_cast<BucketListItem*>(this))
		((BucketListItem*) this)->print();
	else if (dynamic_cast<BucketItemListItem*>(this))
		((BucketItemListItem*) this)->print();
	else if (dynamic_cast<IntegerListItem*>(this))
		((IntegerListItem*) this)->print();
	else if (dynamic_cast<GraphListItem*>(this))
		((GraphListItem*) this)->print();
	else if (dynamic_cast<ListListItem*>(this))
		((ListListItem*) this)->print();
	else if (dynamic_cast<TrendListItem*>(this))
		((TrendListItem*) this)->print();
	else if (dynamic_cast<StalkerListItem*>(this))
		((StalkerListItem*) this)->print();
	else if (dynamic_cast<ExtendedQueueItem*>(this))
		((ExtendedQueueItem*) this)->print();
	else if (this == NULL)
		cout << "NULL list" << endl;
	else
		cout << "ERROR: Unprintable ListItem type \n" << endl;
}

ListItem* ListItem::getListItem() {
	return NULL;
}

void ListItem::printType() {
	cout << "Type: " << endl;
	if (dynamic_cast<IntegerListItem*>(this) != 0)
		cout << "Integer" << endl;
	if (dynamic_cast<EdgeListItem*>(this) != 0)
		cout << "Edge" << endl;
	if (dynamic_cast<BucketListItem*>(this) != 0)
		cout << "Bucket" << endl;
	if (dynamic_cast<BucketItemListItem*>(this) != 0)
		cout << "BucketItem" << endl;
	if (dynamic_cast<ListListItem*>(this) != 0)
		cout << "List" << endl;
	if (dynamic_cast<TrendListItem*>(this) != 0)
		cout << "TrendListItem" << endl;
}
