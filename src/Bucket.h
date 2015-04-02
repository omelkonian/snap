/*
 * Bucket.h
 *
 *  Created on: Nov 11, 2014
 *      Author: athan
 */

#pragma once
#include "BucketItem.h"

/**
 * A sorted array of pointers to BucketItems by node ID.
 */
class Bucket {
	BucketItem **bucketArray;
	int size;
	int cellNo;
public:
	Bucket(int cellNo);
	virtual ~Bucket();

	int getSize();
	BucketItem** getBucketItemArray();
	BucketItem* getBucketItemByIndex(int index);

	int getLastItemID();
	bool isEmpty();

	// Insert
	BucketItem* insertBucketItem(BucketItem *bucketItemToBeInserted);
	BucketItem* insertAtIndex(BucketItem *bucketItemToBeInserted, int index);
	// Remove
	BucketItem* removeBucketItem(BucketItem *bucketItemToBeRemoved, int index);
	BucketItem* removeBucketItemWithIndex(int index);
	int getRemoveBucketIndex(BucketItem *bucketItemToBeRemoved);
	// Lookup
	BucketItem* lookupBucketItem(int id);

	void print();
	void printNodeIds();

private:
	int binarySearch(int id, int minIndex, int maxIndex);

};
