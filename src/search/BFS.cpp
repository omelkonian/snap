/*
 * BFS.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include <assert.h>

#include "BFS.h"

using namespace std;

BFS::BFS(Graph *graph, int startID) {
	this->graph = graph;
	this->startID = startID;

	this->visitedNodePairs = new Pair*[this->graph->getBucketItemNo()];
	if (!visitedNodePairs) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	this->nodeNo = this->graph->getBucketItemNo();

	this->currentVisitedNodeNo = 0;

	this->lastAddedNodesNo = 0;

	this->nodeQueue = new Queue();
	this->depthQueue = new Queue();
	if (!nodeQueue || !depthQueue) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->visitedNodePairs;
		return;
	}

	this->currentNode = this->graph->lookupItem(startID);
	this->currentPair = NULL;

	// Enqueue first node.
	this->nodeQueue->enqueueAsItem(this->currentNode);
	this->depthQueue->enqueueAsInt(0);

	// Update visited node.
	this->visitedNodePairs[this->currentVisitedNodeNo] = new Pair(this->currentNode->getNodeID(), 0);
	this->currentVisitedNodeNo++;
}

BFS::~BFS() {
//	cout << "Deleting BFS" << endl;

	// Delete Pairs.
	for (int i = 0; i < this->currentVisitedNodeNo; i++)
		delete this->visitedNodePairs[i];

	delete[] this->visitedNodePairs;
	// Delete Queues.
	delete this->nodeQueue;
	delete this->depthQueue;
	// Delete currentPair.
	delete this->currentPair;

}

/**
 * Performs one step of the one-direction BFS.
 * Updated visitedNodePairs and currentVisitedNodeNo.
 * Returns true if all nodes have already been visited.
 */
bool BFS::step() {
	if (this->nodeQueue->isEmpty())
		return true;
	BucketItem *cur = nodeQueue->dequeueAsItem();
	int currentDepth = depthQueue->dequeueAsInt();

	assert(currentDepth >= 0);

	if (this->currentPair)
		delete this->currentPair;
	this->currentPair = new Pair(cur->getNodeID(), currentDepth);
	if (!this->currentPair) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return false;
	}

	if (cur != NULL) {
		// Enqueue node's neighbors
		List *neighbors = cur->getEdgeList();

		EdgeListItem *eli = (EdgeListItem*) neighbors->getHead();
		this->lastAddedNodesNo = 0;

		while (eli != NULL) {
			Edge *curEdge = eli->getElement();
			BucketItem *lookupItem;
			if (curEdge->getStartNodeId() == cur->getNodeID())
				lookupItem = this->graph->lookupItem(curEdge->getEndNodeId());
			else
				lookupItem = this->graph->lookupItem(curEdge->getStartNodeId());
//			assert(lookupItem);

			if (lookupItem == NULL) {  	//if the edge is on the air ignore it
				eli = eli->getNext();
				continue;
			}

			// Check if already visited.
			bool alreadyVisited = false;
			for (int i = 0; i < this->currentVisitedNodeNo; i++) {
				if (this->visitedNodePairs[i]->getNodeId() == lookupItem->getNodeID())
					alreadyVisited = true;
			}

			// If it is the first time visiting, enqueue.
			if (!alreadyVisited) {
				// Update visited nodes.
				this->visitedNodePairs[this->currentVisitedNodeNo] = new Pair(lookupItem->getNodeID(), currentDepth + 1);
				if (!this->visitedNodePairs[this->currentVisitedNodeNo]) {
					cout << "ERROR: Unable to allocate memory." << endl;
					return false;
				}
				this->currentVisitedNodeNo++;

				depthQueue->enqueueAsInt(currentDepth + 1);
				nodeQueue->enqueueAsItem(lookupItem);

				this->lastAddedNodesNo++;
			}
			eli = eli->getNext();
		}
		return false;
	} else
		return true;
}

void BFS::printAlreadyVisited() {
	cout << "_________________________________________" << endl;
	cout << "Printing already visited Nodes Pairs" << endl;
	for (int i = 0; i < this->currentVisitedNodeNo; i++)
		this->visitedNodePairs[i]->print();

}

int BFS::getVisitedNodeNo() {
	return this->currentVisitedNodeNo;
}

Pair** BFS::getVisitedPairs() {
	return this->visitedNodePairs;
}

int BFS::getLastAddedNodesNo() {
	return this->lastAddedNodesNo;
}

Pair* BFS::getCurrentPair() {
	return this->currentPair;
}
