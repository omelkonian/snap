/*
 * ExtendedBFS.h
 *
 *  Created on: 30 Nov 2014
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
#include "../list/ListListItem.h"

class ExtendedBFS {
	// Initial data.
	Graph *graph;

	int startID;
	int endID;
	int intermediateID;

	int nodeNo; // Total number of nodes in bucketList.

	LinearHashTable *visited;

	// Queues for implementing BFS.
	Queue *queue;

	BucketItem *currentNode;

	// Return arguments.
	int shortestPathNo; // Number of shortest paths from startID to endID.
	int shortestPathViaIntermediateNo; // Number of the above shortest paths that pass through intermediateID.

public:
	ExtendedBFS(Graph *graph, int startID, int endID, int intermediateID);
	virtual ~ExtendedBFS();

	int getShortestPathNo();
	int getShortestPathViaIntermediateNo();

	void run();

private:
	bool intermediateIsInPath(List *path, int intermediateID);
	void printQueues();

};
