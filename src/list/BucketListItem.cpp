/*
 * BucketListItem.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include "BucketListItem.h"

using namespace std;

BucketListItem::BucketListItem(Bucket *bucketItem) {
	this->bucket = bucketItem;
}

BucketListItem::~BucketListItem() {
//	cout << "   Deleting bucketListItem" << endl;
	delete this->bucket;
//	cout << "   Deleted bucketListItem" << endl;
}

void BucketListItem::print() {
	this->bucket->print();
}

BucketListItem* BucketListItem::getNext() {
	return ((BucketListItem*) this->next);
}

BucketListItem* BucketListItem::getPrevious() {
	return ((BucketListItem*) this->previous);
}

void BucketListItem::printIDs() {
	this->bucket->printNodeIds();
}

BucketListItem* BucketListItem::getListItem() {
	return this;
}

Bucket* BucketListItem::getElement() {
	return this->bucket;
}
