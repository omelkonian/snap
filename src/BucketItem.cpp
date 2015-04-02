/*
 * BucketItem.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include "BucketItem.h"
#include "TrustNode.h"
#include "list/EdgeListItem.h"

using namespace std;

BucketItem::BucketItem(Node *node, List *edgeList) {
	this->node = node;
	this->edgeList = edgeList;
}

BucketItem::~BucketItem() {
//	cout << "    Deleting BucketItem" << endl;
	delete this->node;
	delete this->edgeList;
//	cout << "    Deleted BucketItem" << endl;
}

Node* BucketItem::getNode() {
	return this->node;
}

List* BucketItem::getEdgeList() {
	return this->edgeList;
}

void BucketItem::print() {
	cout << "________________________________________" << endl;
	cout << "Printing BucketItem" << endl;
	if (dynamic_cast<TrustNode*>(this->node) != 0)
		((TrustNode*) this->node)->printPlusTrustValues();
	else
		this->node->print();
	this->edgeList->print();
}

int BucketItem::getNodeID() {
	return this->node->getId();
}

bool BucketItem::knows(int id) {
	EdgeListItem *cur = (EdgeListItem*) this->edgeList->getHead();
	while (cur) {
		if ((cur->getElement()->getEndNodeId() == id) || (cur->getElement()->getStartNodeId() == id))
			return true;
		cur = cur->getNext();
	}
	return false;
}

void BucketItem::printID() {
	cout << "ID: " << this->getNode()->getId() << endl;
}
