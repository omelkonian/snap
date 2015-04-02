/*
 * Graph.h
 *
 *  Created on: Nov 14, 2014
 *      Author: athan
 */

#pragma once
#include <string>

#include "LinearHashTable.h"
#include "Edge.h"
#include "communities/Communities.h"

using namespace std;

class Graph {
	string name;

	int nodeNo;
	int edgeNo;

	int cellNo;
	int initialBucketNo;
	LinearHashTable* linearHashTable;

public:
	Graph(int m, int c, string name);
	Graph(int m, int c);
	virtual ~Graph();

	char* getName();
	int getNodeNo();
	int getEdgeNo();
	int getCellNo();

	int insertNode(Node* node);
	int insertEdge(int nodeId, Edge* element);
	Node* lookupNode(int id);
	BucketItem* lookupItem(int id);

	int reachNode1(int startID, int endID);

	LinearHashTable* getHashTable();
	int getBucketItemNo();
	int getCurrentBucketNo();

	List* getAllIDs();

	Communities* findCommunities();
	long double getModularityScore();

	void print();
	void printInfo();
};
