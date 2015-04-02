/*
 * ExtendedBFS.cpp
 *
 *  Created on: 30 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include <assert.h>

#include "ExtendedBFS.h"
#include "../list/ExtendedQueueItem.h"

using namespace std;

ExtendedBFS::ExtendedBFS(Graph *graph, int startID, int endID, int intermediateID) {
	this->graph = graph;

	this->startID = startID;
	this->endID = endID;
	this->intermediateID = intermediateID;

	this->graph->getBucketItemNo();

	this->nodeNo = this->graph->getBucketItemNo();

	this->visited = new LinearHashTable(graph->getNodeNo(), 10);
	if (!this->visited) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}

	this->queue = new Queue();
	if (!this->queue) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->visited;
		return;
	}

	this->currentNode = this->graph->lookupItem(startID);

	// Enqueue first item.
	ExtendedQueueItem *first = new ExtendedQueueItem(this->currentNode, new List());
	if (!first) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->queue;
		delete this->visited;
		return;
	}
	this->queue->enqueue(first);

	this->shortestPathNo = 0;
	this->shortestPathViaIntermediateNo = 0;
}

ExtendedBFS::~ExtendedBFS() {
//	cout << "Deleting Extended BFS" << endl;

	delete this->queue;
	delete this->visited;
}

void ExtendedBFS::run() {
	ExtendedQueueItem *eqi = (ExtendedQueueItem*) queue->dequeue();
	BucketItem *cur = eqi->getNode();
	int currentDepth = eqi->getDepth();
	List *path = eqi->getPath();

	bool depthLimitSet = false;
	int depthLimit = -1;

	while (cur) {
		if (depthLimitSet && (depthLimit < currentDepth)) {
			delete eqi;
			eqi = (ExtendedQueueItem*) queue->dequeue();
			if (eqi) {
				cur = eqi->getNode();
				currentDepth = eqi->getDepth();
				path = eqi->getPath();
			} else
				cur = NULL;
			continue;
		}

		// If we reached endID, set depthLimit.
		if (cur->getNodeID() == this->endID) {
			depthLimitSet = true;
			depthLimit = currentDepth;

			this->shortestPathNo++;
			if (this->intermediateIsInPath(path, this->intermediateID))
				this->shortestPathViaIntermediateNo++;
		}

		// Do not add children if we are at maximum depth of search.(depthLimit is set) or we already have added them
		if ((depthLimitSet) && (currentDepth > depthLimit))
			break;

		if (this->visited->Lookup(cur->getNodeID())) {
			delete eqi;
			eqi = (ExtendedQueueItem*) queue->dequeue();
			if (eqi) {
				cur = eqi->getNode();
				currentDepth = eqi->getDepth();
				path = eqi->getPath();
			} else
				cur = NULL;
			continue;
		}

		this->visited->Insert(new Node(cur->getNodeID(), NULL));

		// Enqueue node's neighbors
		List *neighbors = cur->getEdgeList();
		EdgeListItem *eli = (EdgeListItem*) neighbors->getHead();
		while (eli) {
			Edge *curEdge = eli->getElement();
			BucketItem *lookupItem;
			if (curEdge->getStartNodeId() == cur->getNodeID())
				lookupItem = this->graph->lookupItem(curEdge->getEndNodeId());
			else
				lookupItem = this->graph->lookupItem(curEdge->getStartNodeId());
			assert(lookupItem);

			// Enqueue only if we haven't visited it yet.
			if (!(visited->Lookup(lookupItem->getNodeID()))) {
				List *newPath = new List();
				if (!newPath) {
					cout << "ERROR: Unable to allocate memory." << endl;
					return;
				}
				ListItem *head = path->getHead();
				while (head != NULL) {
					IntegerListItem *newItem = new IntegerListItem(((IntegerListItem*) head)->getInt());
					if (!newItem) {
						cout << "ERROR: Unable to allocate memory." << endl;
						delete newPath;
						return;
					}
					newPath->insertItem(newItem);
					head = head->getNext();
				}
				IntegerListItem *ili = new IntegerListItem(cur->getNodeID());
				if (!ili) {
					cout << "ERROR: Unable to allocate memory." << endl;
					delete newPath;
					return;
				}
				newPath->insertItem(ili);

				ExtendedQueueItem *newItem = new ExtendedQueueItem(lookupItem, newPath);
				queue->enqueue(newItem);
			}
			eli = eli->getNext();
		}

		delete eqi;
		eqi = (ExtendedQueueItem*) queue->dequeue();
		if (eqi) {
			cur = eqi->getNode();
			currentDepth = eqi->getDepth();
			path = eqi->getPath();
		} else
			cur = NULL;
	}
	return;
}

int ExtendedBFS::getShortestPathNo() {
	return this->shortestPathNo;
}

int ExtendedBFS::getShortestPathViaIntermediateNo() {
	return this->shortestPathViaIntermediateNo;
}

bool ExtendedBFS::intermediateIsInPath(List *path, int intermediateID) {
	IntegerListItem *cur = (IntegerListItem*) path->getHead();
	while (cur) {
		if (cur->getInt() == intermediateID)
			return true;
		cur = cur->getNext();
	}
	return false;
}

void ExtendedBFS::printQueues() {
	this->queue->printElements();
}
