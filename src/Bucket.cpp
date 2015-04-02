/*
 * Bucket.cpp
 *
 *  Created on: Nov 11, 2014
 *      Author: athan
 */

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "Bucket.h"

using namespace std;

Bucket::Bucket(int cellNo) {
	this->size = 0;
	this->cellNo = cellNo;
	this->bucketArray = new BucketItem*[cellNo];
	if (!this->bucketArray) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}

	for (int i = 0; i < cellNo; i++)
		this->bucketArray[i] = NULL;
}

int Bucket::getSize() {
	return this->size;
}

Bucket::~Bucket() {
//	cout << "   Deleting Bucket" << endl;
	for (int i = 0; i < this->size; i++) {
		delete this->bucketArray[i];
	}
	delete[] this->bucketArray;
//	cout << "   Deleted Bucket" << endl;
}

/**
 * Inserts BucketItem in the correct position according to our ascending order.
 * Returns an overflown BucketItem, if any.
 */
BucketItem* Bucket::insertBucketItem(BucketItem *bucketItemToBeInserted) {
	int curIndex = 0;

	while (curIndex < this->size) {
		if (this->bucketArray[curIndex]->getNode()->getId() > bucketItemToBeInserted->getNode()->getId()) {
			BucketItem *overflownBucketItem = this->insertAtIndex(bucketItemToBeInserted, curIndex);
			if (overflownBucketItem != NULL)
				return overflownBucketItem;
			else {
				this->size++;
				return NULL;
			}

		}
		curIndex++;
	}

	assert(curIndex < this->cellNo);

	// Insert at the last empty position.
	this->bucketArray[curIndex] = bucketItemToBeInserted;
	this->size++;
	return NULL;
}

void Bucket::print() {
	cout << "________________________________________" << endl;
	cout << "Printing Bucket" << endl;
	cout << "    Size : " << this->size << endl;
	for (int i = 0; i < this->size; i++)
		this->bucketArray[i]->print();

}

/**
 * Looks up the bucket to find the given id.
 * Returns the pointer to the BucketItem searched or Null, if none is found.
 */
BucketItem* Bucket::lookupBucketItem(int id) {
	// Perform binary search in current sorted Bucket.
	int indexFound = this->binarySearch(id, 0, this->size - 1);
	if (indexFound != -1)
		return this->bucketArray[indexFound];
	else
		return NULL;
}

/**
 * Inserts at a certain place at index and pushes all other BucketItems forward. It returns the only BucketItem that overflows if any
 */
BucketItem* Bucket::insertAtIndex(BucketItem *bucketItemToBeInserted, int index) {
	BucketItem *temp1, *temp2;
	temp1 = this->bucketArray[index];

	// Called outside the class. Must increase size.
	if (temp1 == NULL) {
		this->bucketArray[index] = bucketItemToBeInserted;
		this->size++;
		return NULL;
	}

	this->bucketArray[index] = bucketItemToBeInserted;
	index++;
	while (index < this->cellNo) {

		if (this->bucketArray[index] == NULL) {
			this->bucketArray[index] = temp1;
			return NULL;
		}

		temp2 = this->bucketArray[index];
		this->bucketArray[index] = temp1;
		temp1 = temp2;
		index++;
	}

	return temp1;
}

/**
 * Returns the index of the bucketArray containing the BucketItem requested.
 * Returns -1 if it is not found.
 */
int Bucket::getRemoveBucketIndex(BucketItem* bucketItemToBeRemoved) {
	int retIndex = 0;
	while (retIndex < this->size) {
		if (this->bucketArray[retIndex] == bucketItemToBeRemoved)
			return retIndex;
		retIndex++;
	}
	return -1;
}

/**
 * Removes the BucketItem in the requested index and pushes all following BucketItems backwards.
 * Returns a pointer to the BucketItem or NULL, if it is not found.
 */
BucketItem* Bucket::removeBucketItemWithIndex(int index) {
	if (index >= this->size)
		return NULL;

	BucketItem *ret = this->bucketArray[index];

	this->bucketArray[index] = NULL;

	while (index < this->cellNo - 1) {
		if (this->bucketArray[index + 1] == NULL)
			break;
		this->bucketArray[index] = this->bucketArray[index + 1];
		this->bucketArray[index + 1] = NULL;
		index++;
	}

	this->size--;
	return ret;
}

/**
 * Removes BucketItem with given index and push back all the following BucketItems inside the current Bucket.
 * It is certain that an empty position will exist after the last BucketItem in the Bucket.
 */
BucketItem* Bucket::removeBucketItem(BucketItem* bucketItemToBeRemoved, int index) {
	BucketItem *ret = this->bucketArray[index];
	assert(ret->getNode()->getId() == bucketItemToBeRemoved->getNode()->getId());

	this->bucketArray[index] = NULL;

	while (index < this->cellNo - 1) {
		if (this->bucketArray[index + 1] == NULL)
			break;
		this->bucketArray[index] = this->bucketArray[index + 1];
		this->bucketArray[index + 1] = NULL;
		index++;
	}

	this->size--;
	return ret;
}

void Bucket::printNodeIds() {
	cout << "      Bucket size: " << this->size << endl;
	cout << "          ";
	for (int i = 0; i < this->size; i++)
		cout << this->bucketArray[i]->getNode()->getId() << ", ";
	cout << endl;
}

BucketItem** Bucket::getBucketItemArray() {
	return this->bucketArray;
}

/**
 * Only call if there is at least one BucketItem.
 */
int Bucket::getLastItemID() {
	assert(this->size > 0);

	return this->bucketArray[this->getSize() - 1]->getNode()->getId();
}

bool Bucket::isEmpty() {
	return (this->size == 0);
}

BucketItem* Bucket::getBucketItemByIndex(int index) {
	if (index >= this->size)
		return NULL;
	else
		return this->bucketArray[index];
}

int Bucket::binarySearch(int id, int minIndex, int maxIndex) {
// test if array is empty
	if (maxIndex < minIndex)
		// set is empty, so return value showing not found
		return -1;
	else {
		// calculate midpoint to cut set in half
		int middleIndex = floor((minIndex + maxIndex) / 2);

		// three-way comparison
		if (this->bucketArray[middleIndex]->getNode()->getId() > id)
			// id is in lower subset
			return this->binarySearch(id, minIndex, middleIndex - 1);
		else if (this->bucketArray[middleIndex]->getNode()->getId() < id)
			// id is in upper subset
			return this->binarySearch(id, middleIndex + 1, maxIndex);
		else
			// id has been found
			return middleIndex;
	}
}
