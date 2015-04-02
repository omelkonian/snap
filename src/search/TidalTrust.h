/*
 * TidalTrust.h
 *
 *  Created on: Jan 9, 2015
 *      Author: athan
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
#include "../TrustNode.h"

class TidalTrust {
	Graph* graph;

	TrustNode* startNode;
	TrustNode* endNode;

	BucketItem *currentNode;

	// Queues for implementing BFS.
	Queue *nodeQueue;
	Queue *depthQueue;

public:
	TidalTrust(Graph* graph, Node* startNode, Node* endNode);
	virtual ~TidalTrust();

	double estimateTrust();
};
