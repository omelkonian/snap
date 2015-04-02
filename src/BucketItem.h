/*
 * BucketItem.h
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "list/List.h"

/**
 * Class that holds a node and the node's relations. Search will be used on BucketItems.
 */
class BucketItem {
	Node *node;
	List *edgeList;
public:
	BucketItem(Node *node, List *edgeList);
	virtual ~BucketItem();

	Node* getNode();
	int getNodeID();
	List* getEdgeList();

	bool knows(int id);

	void print();
	void printID();
};
