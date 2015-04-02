/*
 * BBFS.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "BFS.h"
#include "../BucketList.h"

/**
 * Performs alternately one-direction BFS from startNode and endNode.
 * Checks each step if their paths meet and returns the sum of their distances.
 */
class BBFS {
	Graph *graph;
	int startID;
	int endID;

	// The two one-direction BFSs.(from startNode and from endNode)
	BFS *startBFS;
	BFS *endBFS;

	// The number of nodes visited by the two BFSs so far.
	int startBFSvisitedNo;
	int endBFSvisitedNo;

public:
	BBFS(Graph *graph, int startID, int endID);
	virtual ~BBFS();

	int getDistance();

private:
	int isInsideVisitedStart(int ID);
	int isInsideVisitedEnd(int ID);

};
