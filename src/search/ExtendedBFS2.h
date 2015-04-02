/*
 * ExtendedBFS2.h
 *
 *  Created on: 10 Jan 2015
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
#include "../LinearHashTable.h"

/**
 * Returns all shortest paths between two nodes.
 * Path is represented as a list of edgeLists.
 */
class ExtendedBFS2 {
	// Initial data.
	Graph *graph;

	int startID;
	int endID;

	int nodeNo; // Total number of nodes in bucketList.

	// Queues for implementing BFS.
	Queue *queue;

	BucketItem *currentNode;

	LinearHashTable *visitedIDs;

	// Return arguments.
	int shortestPathNo; // Number of shortest paths from startID to endID.
	List *shortestPaths;

public:
	ExtendedBFS2(Graph *graph, int startID, int endID);
	virtual ~ExtendedBFS2();

	int getShortestPathNo();
	List *getShortestPaths();

	void run();
};
