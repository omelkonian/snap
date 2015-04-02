/*
 * BFS.h
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../Graph.h"
#include "../Pair.h"
#include "../BucketList.h"
#include "../BucketItem.h"
#include "../list/Queue.h"
#include "../list/List.h"
#include "../list/EdgeListItem.h"
#include "../list/BucketItemListItem.h"

class BFS {
	// Initial data.
	Graph *graph;
	int startID;

	// Array holding visited nodeIDs and their distance from the startNode so far.
	Pair **visitedNodePairs;

	int nodeNo; // Total number of nodes in bucketList.
	int currentVisitedNodeNo; // Total number of nodes visited so far.

	// Queues for implementing BFS.
	Queue *nodeQueue;
	Queue *depthQueue;

	// Node currently being examined.
	BucketItem *currentNode;

	// Last added neighbors counter.
	int lastAddedNodesNo;

	// Pair currently being examined.
	Pair *currentPair;

public:
	BFS(Graph *graph, int startID);
	virtual ~BFS();

	Pair* getCurrentPair();

	int getVisitedNodeNo();
	Pair** getVisitedPairs();
	int getLastAddedNodesNo();

	bool step();

	void printAlreadyVisited();
};
