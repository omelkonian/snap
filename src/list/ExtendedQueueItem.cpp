/*
 * ExtendedQueueItem.cpp
 *
 *  Created on: 18 …·Ì 2015
 *      Author: Orestis Melkonian
 */

#include "ExtendedQueueItem.h"
#include <iostream>

using namespace std;

ExtendedQueueItem::ExtendedQueueItem(BucketItem *node, List* path) {
	this->node = node;
	this->path = path;
}

ExtendedQueueItem::~ExtendedQueueItem() {
	delete this->path;
}

ExtendedQueueItem* ExtendedQueueItem::getNext() {
	return (ExtendedQueueItem*)this->next;
}

ExtendedQueueItem* ExtendedQueueItem::getPrevious() {
	return (ExtendedQueueItem*)this->previous;
}

int ExtendedQueueItem::getDepth() {
	return this->path->getSize();
}

BucketItem* ExtendedQueueItem::getNode() {
	return this->node;
}

List* ExtendedQueueItem::getPath() {
	return this->path;
}
void ExtendedQueueItem::print() {
	cout << "Printing ExtendedQueueITem" << endl;
	cout << "    Depth: " << this->path->getSize() << endl;
	cout << "    NodeID: " << this->node->getNodeID() << endl;
	this->path->printElements();
}
