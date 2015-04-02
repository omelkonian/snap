/*
 * BucketList.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: athan
 */

#include <assert.h>
#include <iostream>

#include "BucketList.h"
#include "Bucket.h"
#include "list/BucketListItem.h"
#include "list/EdgeListItem.h"

#include <typeinfo>

using namespace std;

BucketList::BucketList(int cellNo) {
	this->bucketItemNo = 0;
	this->cellNo = cellNo;
}

BucketList::~BucketList() {
//	cout << "  Deleting BucketList" << endl;

	BucketListItem *cur = (BucketListItem*) this->head;
	while (cur != NULL) {
		BucketListItem *temp = cur;
		cur = cur->getNext();
		delete temp;
		this->size--;
	}
//	cout << "  Deleted BucketList" << endl;
}

bool BucketList::insert(Node* nodeToBeInserted) {
	return (this->insert(createBucketItem(nodeToBeInserted)));
}

/**
 * Inserts BucketItem in the proper position of the sorted Bucket List.
 * Returns True if there's been an overflow.
 */
bool BucketList::insert(BucketItem* bucketItemToBeInserted) {
	bool ret = false;

	//#1: Empty BucketList
	if (this->isEmpty()) {
		Bucket *newBucket = new Bucket(this->cellNo);
		if (!newBucket) {
			cout << "ERROR: Unable to allocate memory." << endl;
			return false;
		}
		newBucket->insertBucketItem(bucketItemToBeInserted);
		BucketListItem *newListItem = new BucketListItem(newBucket);
		this->insertItem(newListItem);
	}
	//#2: Tail has room for more.
	else if (((BucketListItem*) this->getTail())->getElement()->getSize() < this->cellNo) {
		this->findBucketAndInsert(bucketItemToBeInserted);
	}
	//#3: Tail is full. Must create a new Bucket.
	else {
		Bucket *newBucket = new Bucket(this->cellNo);
		if (!newBucket) {
			cout << "ERROR: Unable to allocate memory." << endl;
			return false;
		}
		BucketListItem *newBucketListItem = new BucketListItem(newBucket);
		if (!newBucketListItem) {
			cout << "ERROR: Unable to allocate memory." << endl;
			delete newBucket;
			return false;
		}
		this->insertItem(newBucketListItem);
		this->findBucketAndInsert(bucketItemToBeInserted);
		ret = true;
	}
	this->bucketItemNo++;
	return ret;
}

int BucketList::getBucketItemNo() {
	return this->bucketItemNo;
}

int BucketList::getCellNo() {
	return this->cellNo;
}

BucketItem* BucketList::createBucketItem(Node* node) {
	BucketItem *bi = new BucketItem(node, new List());
	if (!bi) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	return bi;
}

/**
 * Finds the Bucket containing a BucketItem with the given id, if any.
 * Returns a pointer to the BucketItem or NULL.
 */
BucketItem* BucketList::lookup(int id) {
	if (this->isEmpty())
		return NULL;

	BucketListItem *cur = (BucketListItem*) this->getHead();
	Bucket *checkBucket = cur->getElement();
	Bucket *lookupBucket;

	// Find the only bucket that is possible to find the given id.
	while (checkBucket->getLastItemID() < id) {
		cur = (BucketListItem*) cur->getNext();
		if (cur == NULL)
			return NULL;
		assert(cur != NULL);
		checkBucket = cur->getElement();

		if (cur->getElement()->isEmpty())
			return NULL;
	}

	lookupBucket = cur->getElement();
	return lookupBucket->lookupBucketItem(id);
}

/**
 * Removes the BucketItem requested and pushes all following BucketItems backwards.
 * Returns a pointer to the BucketItem removed.
 */
BucketItem* BucketList::remove(BucketItem* bucketToBeRemoved) {
	// Find Bucket containing requested BucketItem.
	BucketListItem* bucketToCheck = this->findBucket(bucketToBeRemoved);
	BucketItem *ret = NULL;

	// Get index containing the BucketItem requested.
	int indexFound = bucketToCheck->getElement()->getRemoveBucketIndex(bucketToBeRemoved);
	if (indexFound == -1)
		return NULL;
	else {
		ret = bucketToCheck->getElement()->getBucketItemByIndex(indexFound);
		// Remove BucketItem from Bucket.
		bucketToCheck->getElement()->removeBucketItem(bucketToBeRemoved, indexFound);

		// Now push all following items from other Buckets backwards.
		while (bucketToCheck->getNext() != NULL) {
			BucketItem* toBeReinserted = bucketToCheck->getNext()->getElement()->removeBucketItemWithIndex(0);

			if (toBeReinserted != NULL) {
				assert(bucketToCheck->getElement()->insertAtIndex(toBeReinserted, this->cellNo - 1) == NULL);
			}
			bucketToCheck = bucketToCheck->getNext();
		}
	}
	if (ret)
		this->bucketItemNo--;

	// Check if tail bucket needs to be destroyed.
	if (this->bucketItemNo == (this->size - 1) * this->cellNo) // there is an empty tail bucket.
		this->deleteItem(this->tail);

	return ret;
}

/**
 * Finds the correct Bucket for the BucketItem to be inserted and pushes all following BucketItems forward.
 */
void BucketList::findBucketAndInsert(BucketItem* bucketItemToBeInserted) {
	assert(this->getHead() != NULL);

	BucketListItem *cur = this->findBucket(bucketItemToBeInserted);

	/**
	 * Transfer all the following bucketItems one position to the right.
	 */
	BucketItem *overflownBucketItem = cur->getElement()->insertBucketItem(bucketItemToBeInserted);
	while (overflownBucketItem != NULL) {
		cur = (BucketListItem*) cur->getNext();
		assert(cur != NULL);
		overflownBucketItem = cur->getElement()->insertBucketItem(overflownBucketItem);
	}
}

bool BucketList::isEmpty() {
	return (this->bucketItemNo == 0);
}

void BucketList::print() {
	cout << "Printing BucketList" << endl;
	cout << "    Size: " << this->size << endl;
	cout << "    CellNo: " << this->cellNo << endl;
	cout << "    BucketItemNo: " << this->bucketItemNo << endl;

	BucketListItem *cur = (BucketListItem*) this->getHead();
	while (cur != NULL) {
		cur->print();
		cur = cur->getNext();
	}
}

void BucketList::printIDs() {
	cout << "    BucketList Size: " << this->size << endl;

	BucketListItem *cur = (BucketListItem*) this->getHead();
	while (cur != NULL) {
		cur->printIDs();
		cur = cur->getNext();
	}
}

/**
 * Returns a pointer to the Bucket that may contain the given BucketItem.
 */
BucketListItem* BucketList::findBucket(BucketItem* bucketItemToBeSearched) {
	assert(this->getHead() != NULL);
	BucketListItem *cur = (BucketListItem*) this->getHead();
	Bucket *checkBucket = cur->getElement();

	/**
	 * Checks which is the Bucket that may contain the requested Bucket.
	 */
	while (checkBucket->getLastItemID() < bucketItemToBeSearched->getNode()->getId()) {
		if (cur->getNext() == NULL)
			break;
		cur = (BucketListItem*) cur->getNext();
		checkBucket = cur->getElement();

		if (cur->getElement()->isEmpty()) // just insert it there (it's the newly added bucket)
			break;
	}
	return cur;
}
