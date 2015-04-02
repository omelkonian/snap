/*
 * BucketItemListItem.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Orestis Melkonian
 */

#include "BucketItemListItem.h"

BucketItemListItem::BucketItemListItem(BucketItem *bucketItem) {
	this->bucketItem = bucketItem;
}

BucketItemListItem::~BucketItemListItem() {
	delete this->bucketItem;
}

void BucketItemListItem::print() {
	this->bucketItem->print();
}

BucketItemListItem* BucketItemListItem::getNext() {
	return ((BucketItemListItem*) this->next);
}

BucketItemListItem* BucketItemListItem::getPrevious() {
	return ((BucketItemListItem*) this->previous);
}

void BucketItemListItem::printID() {
	this->bucketItem->printID();
}

BucketItem* BucketItemListItem::getElement() {
	return this->bucketItem;
}

void BucketItemListItem::setElement(BucketItem *item) {
	this->bucketItem = item;
}
