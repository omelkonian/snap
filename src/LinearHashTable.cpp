/*
 * LinearHashTable.cpp
 *
 *  Created on: 8/11/2014
 *      Author: Thanos Soulis
 */

#include "LinearHashTable.h"

using namespace std;

LinearHashTable::LinearHashTable(int m, int c) {

	this->initialBucketNo = m;		// increment the initialBucketNo += m at the end of each splitting round
	this->currentBucketNo = m;		// increment the currentBucketNo by 1 at the end of each split
	this->stepBucketNo = 0;			// increment the stepBucketNo at the end of each split
	this->splitRound = 0;			// increment the splitRound at the end of each splitting round
	this->cellSize = c;

	this->table = (BucketList **) malloc((this->initialBucketNo) * sizeof(BucketList*));  //usage of malloc in order to use realloc for resizing
	if (!this->table) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}

	for (int i = 0; i < this->initialBucketNo; i++) {
		BucketList *bl = new BucketList(this->cellSize);
		if (!bl) {
			cout << "ERROR: Unable to allocate memory." << endl;
			free(this->table);
			return;
		}
		this->table[i] = bl;  // ! Create the new BucketList
	}
}

LinearHashTable::~LinearHashTable() {
//	cout << " Deleting LinearHashTable" << endl;
	for (int i = 0; i < this->currentBucketNo; i++)
		delete this->table[i];
	free(table);
//	cout << " Deleted LinearHashTable" << endl;
}

int LinearHashTable::HashFunction(int key) {
	int hash_value = 0;

	hash_value = key % (this->initialBucketNo * ((int) pow(2, (this->splitRound))));

	return hash_value;
}
int LinearHashTable::HashFunctionI(int key) {
	int hash_value = 0;

	hash_value = key % (this->initialBucketNo * ((int) pow(2, (this->splitRound + 1))));

	return hash_value;
}

int LinearHashTable::Insert(Node * record) {
	int recordid = record->getId();
	int hash_value = this->HashFunction(recordid);
	BucketList ** table = this->table;

	if (hash_value >= this->stepBucketNo)  //if the record to be inserted is hashed after the split bucket or into the split bucket use the original HashFunction
			{
		assert(table[hash_value]!=NULL);
		if (table[hash_value]->insert(record) == true) //Checks if the Bucketlist gets overflown
			this->split();
	} else		//if the record to be inserted is hashed before the split bucket use the i+1 HashFunction
	{
		hash_value = this->HashFunctionI(recordid);
		assert(table[hash_value]!=NULL);
		if (table[hash_value]->insert(record) == true) //Checks if the Bucketlist gets overflown
			this->split();
	}
	return SUCCESS;
}

int LinearHashTable::Insert(BucketItem* bucketItem) {

	int recordid = bucketItem->getNodeID();
	int hash_value = this->HashFunction(recordid);
	BucketList ** table = this->table;

	if (hash_value >= this->stepBucketNo) {
		if (table[hash_value]->insert(bucketItem) == true) //Checks if the Bucketlist gets overflown
			this->split();
	} else {
		hash_value = this->HashFunctionI(recordid);

		if (table[hash_value]->insert(bucketItem) == true) //Checks if the Bucketlist gets overflown
			this->split();
	}
	return SUCCESS;
}

int LinearHashTable::InsertEdge(int startNodeId, Edge* element) {

	BucketItem* record = this->Lookup(startNodeId);
	EdgeListItem *newEdgeListItem = new EdgeListItem(element);
	if (!newEdgeListItem) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return -1;
	}
	record->getEdgeList()->insertItem(newEdgeListItem);

	return SUCCESS;
}

int LinearHashTable::split(void) {
	this->table = (BucketList **) realloc(this->table, (this->currentBucketNo + 1) * sizeof(BucketList*));	//allocate one more Bucket
	if (!this->table) {
		cout << "ERROR: Unable to re-allocate memory." << endl;
		return -1;
	}

	this->table[currentBucketNo] = new BucketList(this->cellSize);
	if (!this->table[currentBucketNo]) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return -1;
	}
	this->currentBucketNo = this->currentBucketNo + 1; //increment the currentbucketNo by one

	//make sure that there are data after the realloc
	assert(this->table != NULL);
	assert(this->table[0]!= NULL);
	assert(this->table[this->currentBucketNo -2]!= NULL);
	assert(this->table[this->currentBucketNo-1] != NULL);
	assert(this->table[stepBucketNo]!=NULL);

	BucketList * bucketlist = this->table[stepBucketNo];
	BucketListItem * bucketlistitem = (BucketListItem *) bucketlist->getHead();

	while (bucketlistitem != NULL)  //search the bucket and the overflown buckets
	{
		Bucket* bucket = bucketlistitem->getElement();
		int bucketsize = bucket->getSize();

		BucketItem ** bucketarray = bucket->getBucketItemArray();

		for (int i = 0; i < bucketsize; i++)	//and rehash each and every record that has hash_valueI != stepBucketNo
		{
			assert(bucketarray[i]!= NULL);
			int hash_valueI = this->HashFunctionI(bucketarray[i]->getNodeID());
			if (hash_valueI != this->stepBucketNo) {
				BucketItem* bucketItemTobeRehashed = bucketlist->remove(bucketarray[i]);	//remove from the current bucket

				i--;		//since we removed a bucketItem ,set the iterator one step backwards
				if (!bucket)
					break;
				bucketsize = bucket->getSize();
				assert(bucketItemTobeRehashed !=NULL);

				table[hash_valueI]->insert(bucketItemTobeRehashed);			//insert into the new rightful bucket
			}
		}
		if (!bucketlistitem)
			break;
		bucketlistitem = bucketlistitem->getNext();					//search next bucketItem(check for any overflow buckets)
	}

	this->stepBucketNo = this->stepBucketNo + 1;		//increment the stepBucket by one

	if (this->currentBucketNo == (this->initialBucketNo * ((int) pow(2, (this->splitRound + 1)))))	//its the end of the splitting round
	{
		this->splitRound++;			//increment the splitRound
		this->stepBucketNo = 0;			//reset the stepBucketNo
	}
	return SUCCESS;
}

BucketItem* LinearHashTable::Lookup(int id) {
	BucketList ** table = this->table;
	int hash_value = this->HashFunction(id);
	BucketItem* record = NULL;
	if (hash_value >= this->stepBucketNo)  //if the id is hashed after the split bucket or into the split bucket use the original HashFunction
			{
		record = table[hash_value]->lookup(id);

	} else		//if the record  is hashed before the split bucket use the i+1 HashFunction
	{
		hash_value = this->HashFunctionI(id);
		record = table[hash_value]->lookup(id);

	}
	return record;
}

int LinearHashTable::getCellSize() {
	return this->cellSize;
}

void LinearHashTable::setCellSize(int cellSize) {
	this->cellSize = cellSize;
}

int LinearHashTable::getCurrentBucketNo() {
	return this->currentBucketNo;
}

void LinearHashTable::setCurrentBucketNo(int currentBucketNo) {
	this->currentBucketNo = currentBucketNo;
}

int LinearHashTable::getInitialBucketNo() {
	return this->initialBucketNo;
}

void LinearHashTable::setInitialBucketNo(int initialBucketNo) {
	this->initialBucketNo = initialBucketNo;
}

int LinearHashTable::getSplitRound() {
	return this->splitRound;
}

void LinearHashTable::setSplitRound(int splitRound) {
	this->splitRound = splitRound;
}

int LinearHashTable::getStepBucketNo() {
	return this->stepBucketNo;
}

void LinearHashTable::setStepBucketNo(int stepBucketNo) {
	this->stepBucketNo = stepBucketNo;
}

BucketList**LinearHashTable::getTable() {
	return this->table;
}

void LinearHashTable::setTable(BucketList** table) {
	this->table = table;
}

int LinearHashTable::getBucketItemNo() {
	int ret = 0;
	BucketList **table = this->getTable();
	for (int i = 0; i < this->getCurrentBucketNo(); i++) {
		ret += table[i]->getBucketItemNo();
	}
	return ret;
}

void LinearHashTable::print() {
	BucketList **table = this->getTable();
	for (int i = 0; i < this->getCurrentBucketNo(); i++) {
		cout << "Bucket " << i << endl;
		table[i]->print();
	}
}
