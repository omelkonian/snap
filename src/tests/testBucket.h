/*
 * testBucket.h
 *
 *  Created on: 12 Эях 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include <stdlib.h>
#include <iostream>
#include <assert.h>

#include "../project_main/defines.h"
#include "../properties/Properties.h"
#include "../Node.h"
#include "../Edge.h"
#include "../list/List.h"
#include "../list/EdgeListItem.h"
#include "../BucketItem.h"
#include "../Bucket.h"

using namespace std;

void testBucket() {
	// Creating EdgeListItems
	Properties* properties = new Properties(PERSON_REL_PROPERTIES_NUM);
	properties->setStringProperty("knows", 0);
	properties->setIntegerProperty(156, 1);

	Edge *e = new Edge(1, 2, properties);

	EdgeListItem *eli = new EdgeListItem(e);

	Properties* properties1 = new Properties(PERSON_REL_PROPERTIES_NUM);
	properties1->setStringProperty("dominates", 0);
	properties1->setIntegerProperty(564, 1);

	Edge *e1 = new Edge(3, 4, properties1);

	EdgeListItem *eli1 = new EdgeListItem(e1);

	Properties* properties2 = new Properties(PERSON_REL_PROPERTIES_NUM);
	properties2->setStringProperty("likes", 0);
	properties2->setIntegerProperty(11, 1);

	Edge *e2 = new Edge(5, 6, properties2);

	EdgeListItem *eli2 = new EdgeListItem(e2);

	// Creating EdgeLists
	List *list = new List();
	List *list2 = new List();

	assert(list->getSize() == 0);
	assert(list->getHead() == NULL);
	assert(list->getTail() == NULL);

	list->insertItem(eli);
	list->insertItem(eli1);

	list2->insertItem(eli2);
	list2->insertItem(eli1);

	// Creating Nodes
	Properties* properties3 = new Properties(PERSON_PROPERTIES_NUM);
	properties3->setStringProperty("Orestis", 0);
	properties3->setStringProperty("Melkonian", 1);
	properties3->setIntegerProperty(21, 2);

	Node *n1 = new Node(1, properties3);

	Properties* properties4 = new Properties(PERSON_PROPERTIES_NUM);
	properties4->setStringProperty("Emilia", 0);
	properties4->setStringProperty("Parasxou", 1);
	properties4->setIntegerProperty(22, 2);

	Node *n2 = new Node(2, properties4);

	Properties* properties5 = new Properties(PERSON_PROPERTIES_NUM);
	properties5->setStringProperty("Orestis", 0);
	properties5->setStringProperty("Melkonian", 1);
	properties5->setIntegerProperty(21, 2);

	Node *n3 = new Node(3, properties5);

	Properties* properties6 = new Properties(PERSON_PROPERTIES_NUM);
	properties6->setStringProperty("Emilia", 0);
	properties6->setStringProperty("Parasxou", 1);
	properties6->setIntegerProperty(22, 2);

	Node *n4 = new Node(4, properties6);

	// Creating BucketItems
	BucketItem *bi1 = new BucketItem(n1, list);
	BucketItem *bi2 = new BucketItem(n2, list2);
	BucketItem *bi3 = new BucketItem(n3, list);
	BucketItem *bi4 = new BucketItem(n4, list2);

	// Creating Bucket

	// Testing insertion in a sorted fashion.
	Bucket *b = new Bucket(4);
	b->insertBucketItem(bi4);
	b->insertBucketItem(bi3);
	b->insertBucketItem(bi1);
	b->insertBucketItem(bi2);

	b->printNodeIds();

	// Testing remove (with given index).
	b->removeBucketItem(bi1, 0);
	b->removeBucketItem(bi3, 1);
	b->printNodeIds();

	b->insertBucketItem(bi1);
	b->insertBucketItem(bi3);
	b->printNodeIds();

	// Testing lookup.
	cout << "Node with ID = 1 looked up and has ID : " << b->lookupBucketItem(1)->getNode()->getId() << endl;
	cout << "Node with ID = 2 looked up and has ID : " << b->lookupBucketItem(2)->getNode()->getId() << endl;
	cout << "Node with ID = 3 looked up and has ID : " << b->lookupBucketItem(3)->getNode()->getId() << endl;
	cout << "Node with ID = 4 looked up and has ID : " << b->lookupBucketItem(4)->getNode()->getId() << endl;
}
