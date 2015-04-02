/*
 * general.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#include "general.h"
#include "../project_main/defines.h"

#include <iostream>

using namespace std;

Graph* createGraph1(int m, int c) {
	Graph *ret = new Graph(m, c);
	for (int i = 1; i < 100; i++) {
		ret->insertNode(createNode(i));
		if (i != 1)
			ret->insertEdge(1, createEdge(1, i));
	}
	return ret;
}

BucketList* createBucketList(int nodeNo, int cellNo) {
	BucketList *bucketList = new BucketList(cellNo);
	Bucket *temp;
	for (int i = 0; i < nodeNo; i++) {
		temp = createBucket(cellNo, i * cellNo);
		for (int j = 0; j < temp->getSize(); j++)
			bucketList->insert(temp->getBucketItemByIndex(j));
	}
	return bucketList;
}

BucketListItem* createBucketListItem(int cellNo, int offsetID) {
	return new BucketListItem(createBucket(cellNo, offsetID));
}

Bucket* createBucket(int cellNo, int offsetID) {
	Bucket *ret = new Bucket(cellNo);

	for (int i = 0; i < cellNo; i++) {
		ret->insertBucketItem(createBucketItem(i + (offsetID + 1)));
	}

	return ret;
}

BucketItem* createBucketItem(int id) {
	Node *node = createNode(id);
	List *edgeList = createEdgeList(id);
	return new BucketItem(node, edgeList);
}

List* createEdgeList(int id) {
	List *ret = new List();
	ret->insertItem(createEdgeListItem(id, id + 1));
	ret->insertItem(createEdgeListItem(id, id + 2));
	ret->insertItem(createEdgeListItem(id, id + 3));
	ret->insertItem(createEdgeListItem(id, id + 4));
	return ret;
}

EdgeListItem* createEdgeListItem(int startID, int endID) {
	return new EdgeListItem(createEdge(startID, endID));
}

Edge* createEdge(int startID, int endID) {
	Properties* properties = new Properties(PERSON_REL_PROPERTIES_NUM);
	properties->setStringProperty("knows", 0);
	properties->setIntegerProperty(156, 1);

	return new Edge(startID, endID, properties);
}

Node* createNode(int id) {
	Properties* properties = new Properties(PERSON_PROPERTIES_NUM);
	properties->setStringProperty("Orestis", 0);
	properties->setStringProperty("Melkonian", 1);
	properties->setIntegerProperty(21, 2);

	return new Node(id, properties);
}

