/*
 * BucketList.h
 *
 *  Created on: Nov 12, 2014
 *      Author: athan
 */

#pragma once
#include "list/List.h"
#include "list/BucketListItem.h"
#include "BucketItem.h"

class BucketList: public List {
	int cellNo;
	int bucketItemNo;
public:
	BucketList(int cellNo);
	virtual ~BucketList();

	int getBucketItemNo();
	int getCellNo();

	bool isEmpty();

	bool insert(Node *nodeToBeInserted);
	bool insert(BucketItem *bucketItemToBeInserted);
	BucketItem* lookup(int id);
	BucketItem* remove(BucketItem *bucketToBeRemoved);

	void print();
	void printIDs();

private:
	BucketItem* createBucketItem(Node *node);
	void findBucketAndInsert(BucketItem *bucketItemToBeInserted);
	BucketListItem* findBucket(BucketItem *bucketItemToBeSearched);
};
