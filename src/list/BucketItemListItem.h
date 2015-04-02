/*
 * BucketItemListItem.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "ListItem.h"
#include "../BucketItem.h"

/**
 * A bucketItem that is an item of list.
 */
class BucketItemListItem: public ListItem {
	BucketItem *bucketItem;
public:
	BucketItemListItem(BucketItem *bucket);
	virtual ~BucketItemListItem();

	BucketItemListItem* getNext();
	BucketItemListItem* getPrevious();
	BucketItem* getElement();
	void setElement(BucketItem *item);

	void print();
	void printID();
};
