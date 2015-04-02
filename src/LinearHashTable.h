/*
 * LinearHashTable.cpp
 *
 *  Created on: 8/11/2014
 *      Author: Thanos Soulis
 */

#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Node.h"
#include "BucketList.h"
#include <assert.h>
#include "project_main/defines.h"
#include "Edge.h"
#include "list/EdgeListItem.h"
#include <cmath>

class LinearHashTable {
private:
	int initialBucketNo;  //The original number of buckets
	int currentBucketNo;  //The number of buckets this moment
	int stepBucketNo;    //The bucket that is about to get split
	int splitRound;		  //The split round
	int cellSize;		  //The size of the bucket cells
	BucketList** table;   //The hashtable

public:
	LinearHashTable(int, int);
	virtual ~LinearHashTable();

	int HashFunction(int);
	int HashFunctionI(int);
	int Insert(Node *);				// 0 in success , 1 in failure
	int Insert(BucketItem* bucketItem);	// 0 in success , 1 in failure
	BucketItem* Lookup(int id);
	int split(void);					// 0 in success , 1 in failure
	int InsertEdge(int startNodeId, Edge* element);					// 0 in success , 1 in failure

	int getCellSize();
	void setCellSize(int cellSize);
	int getCurrentBucketNo();
	void setCurrentBucketNo(int currentBucketNo);
	int getInitialBucketNo();
	void setInitialBucketNo(int initialBucketNo);
	int getSplitRound();
	void setSplitRound(int splitRound);
	int getStepBucketNo();
	void setStepBucketNo(int stepBucketNo);
	BucketList** getTable();
	void setTable(BucketList** table);

	int getBucketItemNo();

	void print();
};
