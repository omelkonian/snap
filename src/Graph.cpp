/*
 * Graph.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: athan
 */

#include <iostream>
#include "Graph.h"
#include "search/BBFS.h"
#include "project_main/GraphLib.h"
#include "list/CommunityListItem.h"
#include "project_main/defines.h"

using namespace std;

Graph::Graph(int m, int c) {
	this->nodeNo = 0;
	this->edgeNo = 0;

	this->initialBucketNo = m;
	this->cellNo = c;
	this->linearHashTable = new LinearHashTable(m, c);
	if (!this->linearHashTable) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
}

Graph::Graph(int m, int c, string name) {
	this->name = name;
	this->nodeNo = 0;
	this->edgeNo = 0;

	this->initialBucketNo = m;
	this->cellNo = c;
	this->linearHashTable = new LinearHashTable(m, c);
	if (!this->linearHashTable) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
}

Graph::~Graph() {
//	cout << "Deleting Graph" << endl;
	delete this->linearHashTable;
//	cout << "Deleted Graph" << endl;
}

int Graph::insertNode(Node* node) {
	this->nodeNo++;
	return this->linearHashTable->Insert(node);
}

int Graph::insertEdge(int nodeId, Edge* element) {
	this->edgeNo++;
	return this->linearHashTable->InsertEdge(nodeId, element);
}

Node* Graph::lookupNode(int id) {
	BucketItem *found = this->linearHashTable->Lookup(id);
	if (found != NULL)
		return found->getNode();
	else
		return NULL;
}

int Graph::reachNode1(int startID, int endID) {
	if (startID == endID)
		return 0;
	if ((this->lookupNode(startID) == NULL) || (this->lookupNode(endID) == NULL))
		return INFINITY_REACH_NODE;
	BBFS *bbfs = new BBFS(this, startID, endID);
	if (!bbfs) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return -1;
	}
	int ret = bbfs->getDistance();
	delete bbfs;
	return ret;
}

BucketItem* Graph::lookupItem(int id) {
	return this->linearHashTable->Lookup(id);
}

int Graph::getBucketItemNo() {
	return this->linearHashTable->getBucketItemNo();
}

int Graph::getCurrentBucketNo() {
	return this->linearHashTable->getCurrentBucketNo();
}

int Graph::getNodeNo() {
	return this->nodeNo;
}

int Graph::getEdgeNo() {
	return this->edgeNo;
}

LinearHashTable* Graph::getHashTable() {
	return this->linearHashTable;
}

int Graph::getCellNo() {
	return this->cellNo;
}

List* Graph::getAllIDs() {
	List *ret = new List();
	if (!ret) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}

	// Traverse HashTable.
	LinearHashTable *hashTable = this->linearHashTable;
	BucketList **bucketListTable = hashTable->getTable();
	for (int i = 0; i < hashTable->getCurrentBucketNo(); i++) {
		BucketList *bucketList = bucketListTable[i];
		BucketListItem *cur = (BucketListItem*) bucketList->getHead();
		while (cur) {
			Bucket *bucket = cur->getElement();
			// Count neighbors and update appropriate counter.
			for (int j = 0; j < bucket->getSize(); j++) {
				BucketItem *bi = bucket->getBucketItemByIndex(j);
				if (bi) {
					IntegerListItem *ili = new IntegerListItem(bi->getNodeID());
					if (!ili) {
						cout << "ERROR: Unable to allocate memory." << endl;
						return NULL;
					}
					ret->insertItem(ili);
				}
			}
			cur = (BucketListItem*) cur->getNext();
		}
	}
	return ret;
}

void Graph::print() {
	cout << endl;
	cout << "==============" << this->name << "==============================" << endl;
	this->linearHashTable->print();
	cout << "============================================" << endl;
	cout << endl;
}

long double Graph::getModularityScore() {
	Communities *communities = this->findCommunities();
	CommunityListItem *cli = (CommunityListItem*) communities->getCommunitiesList()->getHead();

	long double totalSum = 0.0;

	int edges = this->edgeNo;

	List *allIDs = this->getAllIDs();
	IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
	while (ili) {
		int id1 = ili->getInt();
		IntegerListItem *ili2 = (IntegerListItem*) allIDs->getHead();
//		IntegerListItem *ili2 = ili->getNext();
		while (ili2) {
			int id2 = ili2->getInt();
			if (id1 == id2) {
				ili2 = ili2->getNext();
				continue;
			}

			// Are they in the same community?
			int com1 = communities->getCommunity(id1);
			int com2 = communities->getCommunity(id2);
			if (com1 != com2) {
				ili2 = ili2->getNext();
				continue;
			}
			// Are they neighbors?
			List *neighbors1 = this->lookupItem(id1)->getEdgeList();
			List *neighbors2 = this->lookupItem(id2)->getEdgeList();
			long double Ki = (long double) neighbors1->getSize();
			long double Kj = (long double) neighbors2->getSize();

			long double A = 0.0;
			EdgeListItem *eli = (EdgeListItem*) neighbors1->getHead();
			while (eli) {
				if (eli->getElement()->getEndNodeId() == id2)
					A = 1.0;
				eli = eli->getNext();
			}
			eli = (EdgeListItem*) neighbors2->getHead();
			while (eli) {
				if (eli->getElement()->getEndNodeId() == id1)
					A = 1.0;
				eli = eli->getNext();
			}

			totalSum += (A - ((Ki * Kj) / (2.0 * (long double) edges)));

			ili2 = ili2->getNext();
		}
		ili = ili->getNext();
	}
	delete allIDs;
	delete communities;

	return (totalSum / (2.0 * (long double) edges));
}

Communities* Graph::findCommunities() {
	int communityID = 0;
	List* communitiesList = new List();
	if (!communitiesList) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}

	List* intList = this->getAllIDs();

	int numberOfCC = 0;
	int numberOfNodes = 0;

	LinearHashTable *hashTable = this->getHashTable();
	BucketList **bucketListTable = hashTable->getTable();
	for (int i = 0; i < hashTable->getCurrentBucketNo(); i++) {
		BucketList *bucketList = bucketListTable[i];
		BucketListItem *cur = (BucketListItem*) bucketList->getHead();

		while (cur != NULL) {
			Bucket *bucket = cur->getElement();
			for (int j = 0; j < bucket->getSize(); j++) {

				BucketItem *bi = bucket->getBucketItemByIndex(j);
				int startNodeId = bi->getNodeID();
				List* communityMembers = new List();
				if (!communityMembers) {
					cout << "ERROR: Unable to allocate memory." << endl;
					delete intList;
					return NULL;
				}

				numberOfNodes = 0;
				bool skip = true;

				IntegerListItem* listNode = (IntegerListItem*) intList->getHead();
				while (listNode != NULL) {

					if (listNode->getInt() == startNodeId) {
						intList->deleteItem(listNode);

						numberOfCC++;
						numberOfNodes++;

						IntegerListItem *ili = new IntegerListItem(startNodeId);
						if (!ili) {
							cout << "ERROR: Unable to allocate memory." << endl;
							delete communityMembers;
							delete communitiesList;
							delete intList;
							return NULL;
						}
						communityMembers->insertItem(ili); //insert the 1st memberID of the community

						skip = false;
						break;
					}
					listNode = listNode->getNext();
				}
				if (communityMembers->getSize() == 0)	//we have already traversed the nodeId in a previous CC
					delete communityMembers;			//and the communityMembers list is empty

				if (!skip) {
					//reachNodeN from each node of the graph
					ResultSet *res = reachNodeN(startNodeId, this);
					Pair* pair;

					while (pair = res->next()) {
						IntegerListItem* searchListNode = (IntegerListItem*) intList->getHead();
						while (searchListNode != NULL) {
							if (searchListNode->getInt() == pair->getNodeId()) {

								intList->deleteItem(searchListNode);

								IntegerListItem *ili = new IntegerListItem(pair->getNodeId());
								if (!ili) {
									cout << "ERROR: Unable to allocate memory." << endl;
									delete communitiesList;
									delete intList;
									return NULL;
								}
								communityMembers->insertItem(ili);			//insert another memberID of the community
								numberOfNodes++;
								break;
							}
							searchListNode = (IntegerListItem*) searchListNode->getNext();
						}
					}
					communityID++;
					Community* community = new Community(communityID, communityMembers);
					if (!community) {
						cout << "ERROR: Unable to allocate memory." << endl;
						delete communitiesList;
						delete intList;
						return NULL;
					}
					communitiesList->insertItem(new CommunityListItem(community));

					delete res;		//free(): invalid next size (fast):
				}
			}
			cur = (BucketListItem*) cur->getNext();
		}
	}
	Communities* communities = new Communities(communitiesList);
	if (!communities) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete communitiesList;
		delete intList;
		return NULL;
	}

	delete intList;
	return communities;
}

void Graph::printInfo() {
	cout << "Graph: " << this->name << endl;
	cout << "   Nodes: " << this->nodeNo << endl;
	cout << "   Edges: " << this->edgeNo << endl;
}

char* Graph::getName() {
	return (char*) this->name.c_str();
}
