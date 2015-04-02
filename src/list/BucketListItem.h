/*
 * BucketListItem.h
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "ListItem.h"
#include "../Bucket.h"

/**
 * A bucketItem that is an item of list.
 */
class BucketListItem: public ListItem {
	Bucket *bucket;
public:
	BucketListItem(Bucket *bucket);
	virtual ~BucketListItem();

	BucketListItem* getNext();
	BucketListItem* getPrevious();
	Bucket* getElement();

	BucketListItem* getListItem();

	void print();
	void printIDs();
};
