/*
 * ExtendedBFS2.cpp
 *
 *  Created on: 10 Jan 2015
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include <assert.h>

#include "ExtendedBFS2.h"

using namespace std;

ExtendedBFS2::ExtendedBFS2(Graph *graph, int startID, int endID) {
	this->graph = graph;

	this->startID = startID;
	this->endID = endID;

	this->graph->getBucketItemNo();

	this->nodeNo = this->graph->getBucketItemNo();

	this->queue = new Queue();
	if (!this->queue) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}

	this->currentNode = this->graph->lookupItem(startID);

	this->visitedIDs = new LinearHashTable(1, 1);
	if (!this->visitedIDs) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->queue;
		return;
	}

	// Enqueue first node.
	ExtendedQueueItem *eqi = new ExtendedQueueItem(this->currentNode, new List());
	if (!eqi) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->queue;
		delete this->visitedIDs;
		return;
	}
	this->queue->enqueue(eqi);

	this->shortestPathNo = 0;
	this->shortestPaths = new List();
	if (!shortestPaths) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->queue;
		delete this->visitedIDs;
		return;
	}
}

ExtendedBFS2::~ExtendedBFS2() {
//	cout << "Deleting Extended BFS2" << endl;
	delete this->queue;
	delete this->visitedIDs;
	delete this->shortestPaths;
}

void ExtendedBFS2::run() {
	ExtendedQueueItem *eqi = (ExtendedQueueItem*) this->queue->dequeue();
	BucketItem *cur = eqi->getNode();
	int currentDepth = eqi->getDepth();
	List *path = eqi->getPath();

	bool depthLimitSet = false;
	int depthLimit = -1;

	while (cur) {
		if (depthLimitSet && depthLimit < currentDepth) {
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

			// Update shortest paths.
			List *newPath = new List();
			if (!newPath) {
				cout << "ERROR: Unable to allocate memory." << endl;
				return;
			}
			EdgeListItem *eli = (EdgeListItem*) path->getHead();
			while (eli) {
				Edge *e = eli->getElement();
				newPath->insertItem(new EdgeListItem(new Edge(e->getStartNodeId(), e->getEndNodeId(), NULL)));
				eli = eli->getNext();
			}
			ListListItem *lli = new ListListItem(newPath);
			if (!lli) {
				cout << "ERROR: Unable to allocate memory." << endl;
				delete newPath;
				return;
			}
			this->shortestPaths->insertItem(lli);
		}

		if (this->visitedIDs->Lookup(cur->getNodeID())) {
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

		this->visitedIDs->Insert(new Node(cur->getNodeID(), NULL));

		// Do not add children if we are at maximum depth of search.(depthLimit is set) or we already have added them
		if ((depthLimitSet) && (currentDepth >= depthLimit)) {
			continue;
		}

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
			if (!(visitedIDs->Lookup(lookupItem->getNodeID()))) {
				List *newPath = new List();
				if (!newPath) {
					cout << "ERROR: Unable to allocate memory." << endl;
					return;
				}
				EdgeListItem *head = (EdgeListItem*) path->getHead();
				while (head) {
					Edge *e = head->getElement();
					EdgeListItem *newItem = new EdgeListItem(new Edge(e->getStartNodeId(), e->getEndNodeId(), NULL));
					newPath->insertItem(newItem);
					head = head->getNext();
				}
				EdgeListItem *eli = new EdgeListItem(new Edge(cur->getNodeID(), curEdge->getEndNodeId(), NULL));
				if (!eli) {
					cout << "ERROR: Unable to allocate memory." << endl;
					delete newPath;
					return;
				}
				newPath->insertItem(eli);

				ExtendedQueueItem *newItem = new ExtendedQueueItem(lookupItem, newPath);
				this->queue->enqueue(newItem);
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

int ExtendedBFS2::getShortestPathNo() {
	return this->shortestPathNo;
}

List* ExtendedBFS2::getShortestPaths() {
	return this->shortestPaths;
}
