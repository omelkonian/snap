/*
 * BBFS.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include "../project_main/defines.h"
#include "BBFS.h"

using namespace std;

BBFS::BBFS(Graph *graph, int startID, int endID) {
	this->graph = graph;
	this->startID = startID;
	this->endID = endID;

	this->startBFS = new BFS(graph, startID);
	if (!startBFS) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	this->startBFSvisitedNo = 1;
	this->endBFS = new BFS(graph, endID);
	if (!endBFS) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete startBFS;
		return;
	}
	this->endBFSvisitedNo = 1;
}

BBFS::~BBFS() {
//	cout << "Deleting BBFS" << endl;
	delete this->startBFS;
	delete this->endBFS;
}

/**
 * Performs one step of BFS alternately from startNode and endNode.
 * Returns the shortest path between them, or INFINITY_REACH_NODE if there is no path.
 */
int BBFS::getDistance() {
//	cout << "Executing BBFS" << endl;
	if (this->startID == this->endID)
		return 0;

	bool allStopFlag = false;
	bool startStopFlag = false;
	bool endStopFlag = false;

	while (!allStopFlag) {
		// Perform one step of StartBFS
		if (!startStopFlag) {
			if (this->startBFS->step())
				startStopFlag = true;

			// Check if node that was just explored, is intermediate.
			int foundIndex = this->isInsideVisitedEnd(this->startBFS->getCurrentPair()->getNodeId());
			if (foundIndex != -1) {
				int totalDistance = this->startBFS->getCurrentPair()->getDistance();
				Pair **endVisitedNodes = this->endBFS->getVisitedPairs();
				totalDistance += endVisitedNodes[foundIndex]->getDistance();
				return totalDistance;
			}

			// Check if it meets any already explored nodes of EndBFS.
			Pair **visitedNodes = this->startBFS->getVisitedPairs();
			int totalAddedNodesNo = this->startBFS->getVisitedNodeNo();
			int lastAddedNodesNo = this->startBFS->getLastAddedNodesNo();
			for (int i = totalAddedNodesNo - lastAddedNodesNo; i < totalAddedNodesNo; i++) {
				int foundIndex = this->isInsideVisitedEnd(visitedNodes[i]->getNodeId());
				if (foundIndex != -1) {
					int totalDistance = visitedNodes[i]->getDistance(); // distance from start to intermediate node.
					Pair **endVisitedNodes = this->endBFS->getVisitedPairs();
					totalDistance += endVisitedNodes[foundIndex]->getDistance(); // distance from end to intermediate node.

					return totalDistance;
				}
			}
		}

		// Perform one step of EndBFS
		if (!endStopFlag) {
			if (this->endBFS->step())
				endStopFlag = true;

			// Check if node that was just explored, is intermediate.
			int foundIndex = this->isInsideVisitedStart(this->endBFS->getCurrentPair()->getNodeId());
			if (foundIndex != -1) {
				int totalDistance = this->endBFS->getCurrentPair()->getDistance();
				Pair **startVisitedNodes = this->startBFS->getVisitedPairs();
				totalDistance += startVisitedNodes[foundIndex]->getDistance();
				return totalDistance;
			}

			// Check if it meets any already explored nodes of StartBFS.
			Pair **visitedNodes = this->endBFS->getVisitedPairs();
			int totalAddedNodesNo = this->endBFS->getVisitedNodeNo();
			int lastAddedNodesNo = this->endBFS->getLastAddedNodesNo();
			for (int i = totalAddedNodesNo - lastAddedNodesNo; i < totalAddedNodesNo; i++) {
				int foundIndex = this->isInsideVisitedStart(visitedNodes[i]->getNodeId());
				if (foundIndex != -1) {
					int totalDistance = visitedNodes[i]->getDistance(); // distance from end to intermediate node.
					Pair **endVisitedNodes = this->startBFS->getVisitedPairs();
					totalDistance += endVisitedNodes[foundIndex]->getDistance(); // distance from end to intermediate node.

					return totalDistance;
				}
			}
		}

		// If any of the searches have finished, stop the other (no point in searching more nodes).
		if (startStopFlag || endStopFlag)
			allStopFlag = true;
	}

	return INFINITY_REACH_NODE;
}

/**
 * Checks the visited nodes of startBFS to see if there is a node with {ID}.
 * Returns the index of the node, or -1 if it is not found.
 */
int BBFS::isInsideVisitedStart(int ID) {
	for (int i = 0; i < this->startBFS->getVisitedNodeNo(); i++) {
		Pair **startVisitedPairs = this->startBFS->getVisitedPairs();
		if (startVisitedPairs[i]->getNodeId() == ID)
			return i;
	}
	return -1;
}

/**
 * Checks the visited nodes of endBFS to see if there is a node with {ID}.
 * Returns the index of the node, or -1 if it is not found.
 */
int BBFS::isInsideVisitedEnd(int ID) {
	for (int i = 0; i < this->endBFS->getVisitedNodeNo(); i++) {
		Pair **endVisitedPairs = this->endBFS->getVisitedPairs();
		if (endVisitedPairs[i]->getNodeId() == ID)
			return i;
	}
	return -1;
}
