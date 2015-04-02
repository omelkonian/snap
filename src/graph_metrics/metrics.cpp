/*
 * metrics.cpp
 *
 *  Created on: 29 Nov 2014
 *      Author: Orestis Melkonian
 */

#include "metrics.h"
#include "../project_main/defines.h"
#include "../project_main/GraphLib.h"
#include "../search/ExtendedBFS.h"

#include <iostream>
#include <fstream>
#include <assert.h>
#include <cstdlib>

using namespace std;

/**
 * Calculates and returns the maxinum distance of two nodes in the graph.
 */
int diameter(Graph *g) {
	int diameter = 0;
	List *allIDs = g->getAllIDs();
	IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
	while (ili) {
		IntegerListItem *ili2 = ili->getNext();
		while (ili2) {
			int id1 = ili->getInt();
			int id2 = ili2->getInt();
			if (id1 != id2) {
				int distance = g->reachNode1(id1, id2);
				diameter = ((distance != INFINITY_REACH_NODE) && (distance > diameter)) ? (distance) : (diameter);
			}
			ili2 = ili2->getNext();
		}
		ili = ili->getNext();
	}
	return diameter;
}

/**
 * Calculates and returns the density of a graph.
 */
double density(Graph *g) {
	double nodeNo = g->getNodeNo(), edgeNo = g->getEdgeNo();
	return ((2 * edgeNo) / (nodeNo * (nodeNo - 1)));
}

/**
 * Calculates the degree distribution of a graph and visualizes it using GNUPLOT.
 * Only considers out_degree.
 */
void degreeDistribution(Graph *g, bool checkFlag) {
	int nodeNo = g->getNodeNo();

	// Initialize array of N-1 elements to zeros ( holding the P(k)s, for k in (0,n-1) ).
	double totalCounters[nodeNo];
	for (int i = 0; i < nodeNo; i++)
		totalCounters[i] = 0;

	// Traverse HashTable and update all counters.
	LinearHashTable *hashTable = g->getHashTable();
	BucketList **bucketListTable = hashTable->getTable();
	for (int i = 0; i < hashTable->getCurrentBucketNo(); i++) {
		BucketList *bucketList = bucketListTable[i];
		BucketListItem *cur = (BucketListItem*) bucketList->getHead();
		while (cur) {
			Bucket *bucket = cur->getElement();
			// Count neighbors and update appropriate counter.
			for (int j = 0; j < bucket->getSize(); j++) {
				BucketItem *bi = bucket->getBucketItemByIndex(j);
				int count = bi->getEdgeList()->getSize();
				totalCounters[count]++;
			}

			cur = (BucketListItem*) cur->getNext();
		}
	}

	// Divide each counter by N.
	for (int i = 0; i < nodeNo; i++)
		totalCounters[i] = totalCounters[i] / nodeNo;

	if (checkFlag == true) {
		assert(int(totalCounters[0] * 10000) == 9898);
		assert(int(totalCounters[98] * 10000) == 101);
	}

	// Make data file.
	ofstream myFile;
	const char *filename = "graph_metrics/gnuplot/bin/data.txt";
	myFile.open(filename);
	if (myFile.fail()) {
		cout << "ERROR: Unable to open " << filename << endl;
		return;
	}

	myFile << "# K       P(K)" << endl;
	for (int i = 0; i < nodeNo; i++)
		myFile << i << "      " << 100 * totalCounters[i] << endl;
	myFile.close();

	// Run gnuplot to display graph.
#ifdef  __CYGWIN__
	system("cd graph_metrics/gnuplot/bin; ./gnuplot.exe degree.gnu");
#else
	system("cd graph_metrics/gnuplot/bin; wine gnuplot.exe degree.gnu");
#endif
}

/**
 * Calculates and returns the centrality of a node, based on how close it is to the other nodes.
 */
double closenessCentrality(Node *n, Graph *g) {
	double centrality = 0;
	ResultSet* res = reachNodeN(n->getId(), g);

	Pair* pair;
	// Sum up all inverted distances to the other nodes.
	while ((pair = res->next()) != NULL)
		centrality += 1.0 / ((double) pair->getDistance());

	delete res;
	// Normalize.
	return centrality / (g->getNodeNo() - 1);
}

/**
 * Calculates and returns the centrality of a node, based on how many times it acts as a bridge on the shortest path of two nodes.
 */
double betweennessCentrality(Node *n, Graph *g) {
	int nodeNo = g->getNodeNo();

	double totalSum = 0.0;

	List *allIDs = g->getAllIDs();
	IntegerListItem *cur1 = (IntegerListItem*) allIDs->getHead();
	while (cur1) {
		if (cur1->getInt() == n->getId()) {
			cur1 = cur1->getNext();
			continue;
		}
//		IntegerListItem *cur2 = (IntegerListItem*) allIDs->getHead(); // only use for directed graphs
		IntegerListItem *cur2 = cur1->getNext();
		while (cur2) {
			if (cur2->getInt() == n->getId() || cur2->getInt() == cur1->getInt()) {
				cur2 = (IntegerListItem*) cur2->getNext();
				continue;
			}

			ExtendedBFS *ebfs = new ExtendedBFS(g, cur1->getInt(), cur2->getInt(), n->getId());
			ebfs->run();

			if (ebfs->getShortestPathNo() != 0) {
				totalSum += ((double) ebfs->getShortestPathViaIntermediateNo()) / ((double) ebfs->getShortestPathNo());
			}
			cur2 = (IntegerListItem*) cur2->getNext();
			delete ebfs;
		}
		cur1 = (IntegerListItem*) cur1->getNext();
	}
	delete allIDs;
	// Normalize.
	return totalSum / (((nodeNo - 2) * (nodeNo - 1)) / 2);
}

/**
 * Calculates and returns the average of the distances between any two nodes of the graph.
 */
double averagePathLength(Graph* g) {
	double totalSum = 0.0;
	double totalCounter = 0.0;
	List *allIDs = g->getAllIDs();
	IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
	while (ili) {
//		IntegerListItem *ili2 = (IntegerListItem*) allIDs->getHead();     // only use for directed graphs
		IntegerListItem *ili2 = ili->getNext();
		while (ili2) {
			int id1 = ili->getInt();
			int id2 = ili2->getInt();
			if (id1 != id2) {
				int distance = g->reachNode1(id1, id2);
				totalSum += (distance != INFINITY_REACH_NODE) ? (distance) : (0);
				totalCounter += 1.0;
			}
			ili2 = ili2->getNext();
		}
		ili = ili->getNext();
	}

	return totalSum / ((double) totalCounter);
}

/**
 * Calculates and returns the number of connected subgraphs
 * and the nodes of the biggest connected subgraph in the main graph.
 */

void numberOfCCsMaxCC(Graph* g, int* numberOfCCs, int* maxCC) {
	List* intList = g->getAllIDs();
	int numberOfCC = 0;
	int numberOfNodes = 0;
	int maxNumCC = 0;
	LinearHashTable *hashTable = g->getHashTable();
	BucketList **bucketListTable = hashTable->getTable();
	for (int i = 0; i < hashTable->getCurrentBucketNo(); i++) {
		BucketList *bucketList = bucketListTable[i];
		BucketListItem *cur = (BucketListItem*) bucketList->getHead();
		while (cur != NULL) {
			Bucket *bucket = cur->getElement();
			for (int j = 0; j < bucket->getSize(); j++) {
				BucketItem *bi = bucket->getBucketItemByIndex(j);
				int startNodeId = bi->getNodeID();

				numberOfNodes = 0;
				bool skip = true;

				IntegerListItem* listNode = (IntegerListItem*) intList->getHead();
				while (listNode != NULL) {
					if (listNode->getInt() == startNodeId) {
						intList->deleteItem(listNode);
						numberOfCC++;
						numberOfNodes++;
						skip = false;
						break;
					}
					listNode = (IntegerListItem*) listNode->getNext();
				}

				if (!skip) {
					//reachNodeN from each node of the graph
					ResultSet *res = reachNodeN(startNodeId, g);
					Pair* pair;
					while (pair = res->next()) {
						IntegerListItem* searchListNode = (IntegerListItem*) intList->getHead();
						while (searchListNode != NULL) {
							if (searchListNode->getInt() == pair->getNodeId()) {
								intList->deleteItem(searchListNode);
								numberOfNodes++;
								break;
							}
							searchListNode = (IntegerListItem*) searchListNode->getNext();
						}

					}
					//delete res;		//free(): invalid next size (fast):
				}
				if (numberOfNodes > maxNumCC)
					maxNumCC = numberOfNodes;
			}
			cur = (BucketListItem*) cur->getNext();
		}
	}
	delete intList;

	*numberOfCCs = numberOfCC;
	*maxCC = maxNumCC;
}
int numberOfCCs(Graph* g) {
	int numberOfCCs = 0;
	int maxCC = 0;
	numberOfCCsMaxCC(g, &numberOfCCs, &maxCC);
	return numberOfCCs;
}

int maxCC(Graph* g) {
	int numberOfCCs = 0;
	int maxCC = 0;
	numberOfCCsMaxCC(g, &numberOfCCs, &maxCC);
	return maxCC;
}
