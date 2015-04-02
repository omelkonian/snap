/*
 * tests.cpp
 *
 *  Created on: 12 Эях 2014
 *      Author: Orestis Melkonian
 */

#include <stdlib.h>
#include <iostream>
#include <assert.h>

#include "../project_main/defines.h"
#include "../project_main/GraphQueries.h"
#include "../properties/Properties.h"
#include "../Node.h"
#include "../Edge.h"
#include "../list/List.h"
#include "../list/EdgeListItem.h"
#include "../BucketItem.h"
#include "../Bucket.h"
#include "../BucketList.h"

using namespace std;

void _testBucket() {

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

void testBucketList() {
	cout << "Testing BucketList!!!" << endl;
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
	properties3->setStringProperty("Orestis1", 0);
	properties3->setStringProperty("Melkonian", 1);
	properties3->setIntegerProperty(21, 2);

	Node *n1 = new Node(1, properties3);

	Properties* properties4 = new Properties(PERSON_PROPERTIES_NUM);
	properties4->setStringProperty("Emilia1", 0);
	properties4->setStringProperty("Parasxou", 1);
	properties4->setIntegerProperty(22, 2);

	Node *n2 = new Node(2, properties4);

	Properties* properties5 = new Properties(PERSON_PROPERTIES_NUM);
	properties5->setStringProperty("Orestis2", 0);
	properties5->setStringProperty("Melkonian", 1);
	properties5->setIntegerProperty(21, 2);

	Node *n3 = new Node(3, properties5);

	Properties* properties6 = new Properties(PERSON_PROPERTIES_NUM);
	properties6->setStringProperty("Emilia2", 0);
	properties6->setStringProperty("Parasxou", 1);
	properties6->setIntegerProperty(22, 2);

	Node *n4 = new Node(4, properties6);

	Properties* properties7 = new Properties(PERSON_PROPERTIES_NUM);
	properties7->setStringProperty("Orestis3", 0);
	properties7->setStringProperty("Melkonian", 1);
	properties7->setIntegerProperty(21, 2);

	Node *n5 = new Node(5, properties7);

	Properties* properties8 = new Properties(PERSON_PROPERTIES_NUM);
	properties8->setStringProperty("Emilia3", 0);
	properties8->setStringProperty("Parasxou", 1);
	properties8->setIntegerProperty(22, 2);

	Node *n6 = new Node(6, properties8);

	Properties* properties9 = new Properties(PERSON_PROPERTIES_NUM);
	properties9->setStringProperty("Orestis4", 0);
	properties9->setStringProperty("Melkonian", 1);
	properties9->setIntegerProperty(21, 2);

	Node *n7 = new Node(7, properties9);

	Properties* properties10 = new Properties(PERSON_PROPERTIES_NUM);
	properties10->setStringProperty("Emilia4", 0);
	properties10->setStringProperty("Parasxou", 1);
	properties10->setIntegerProperty(22, 2);

	Node *n8 = new Node(8, properties10);

	// Creating BucketItems
	BucketItem *bi1 = new BucketItem(n1, list);
	BucketItem *bi2 = new BucketItem(n2, list2);
	BucketItem *bi3 = new BucketItem(n3, list);
	BucketItem *bi4 = new BucketItem(n4, list2);
	BucketItem *bi5 = new BucketItem(n5, list);
	BucketItem *bi6 = new BucketItem(n6, list2);
	BucketItem *bi7 = new BucketItem(n7, list);
	BucketItem *bi8 = new BucketItem(n8, list2);

	// Creating BucketList , c = 4
	BucketList *bl = new BucketList(4);

	// Testing insert().
	bl->insert(bi1);
	bl->insert(bi2);
	bl->insert(bi3);
	bl->insert(bi8);
	bl->insert(bi6);
	bl->insert(bi7);
	bl->insert(bi4);
	bl->insert(bi5);

//	bl->printIDs();

// Testing lookup().

	bl->lookup(3)->printID();
	bl->lookup(6)->printID();
	bl->lookup(7)->printID();
	bl->lookup(1)->printID();
	bl->lookup(0);

	// Testing remove().
	bl->remove(bi1);
	bl->remove(bi6);
	bl->remove(bi3);
	bl->remove(bi2);

	bl->printIDs();

	cout << "THE END" << endl;
}
