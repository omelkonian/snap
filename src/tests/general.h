/*
 * general.h
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../Node.h"
#include "../Edge.h"
#include "../BucketItem.h"
#include "../Bucket.h"
#include "../BucketList.h"
#include "../list/EdgeListItem.h"
#include "../list/BucketListItem.h"
#include "../list/BucketItemListItem.h"
#include "../Graph.h"
#include "../LinearHashTable.h"

Graph* createGraph1(int m, int c);
BucketList* createBucketList(int nodeNo, int cellNo);
BucketListItem* createBucketListItem(int cellNo, int offsetID);
Bucket* createBucket(int cellNo, int offsetID);
BucketItem* createBucketItem(int id);
List* createEdgeList(int id);
EdgeListItem* createEdgeListItem(int startID, int endID);
Edge* createEdge(int startID, int endID);
Node* createNode(int id);
