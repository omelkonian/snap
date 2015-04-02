/*
 * girvanNewman.cpp
 *
 *  Created on: 11 Jan 2015
 *      Author: Orestis Melkonian
 */
#include "_communities.h"
#include "../graph_metrics/metrics.h"
#include "../list/IntegerListItem.h"

#include <stdio.h>
#include <assert.h>

using namespace std;

/**
 * Finds a forum's communities utilizing edge betweeness metric.
 */
Communities* girvanNewman(double modularity, Graph *g) {
	int nodes = g->getNodeNo();

	List *deletedEdges = NULL;
	long double maxModularity = 0.0;
	bool maxModularitySet = false;

	// Construct ID_maps
	LinearHashTable *idMap = new LinearHashTable(nodes, 1);
	LinearHashTable *idMapReverse = new LinearHashTable(nodes, 1);
	if (!idMap || !idMapReverse) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	List *allIDs = g->getAllIDs();
	IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
	for (int i = 0; i < nodes; i++) {
		Properties *prop = new Properties(1);
		prop->setIntegerProperty(i, 0);
		idMap->Insert(new Node(ili->getInt(), prop));

		Properties *prop2 = new Properties(1);
		if (!prop || !prop2) {
			cout << "ERROR: Unable to allocate memory." << endl;
			return NULL;
		}
		prop2->setIntegerProperty(ili->getInt(), 0);
		idMapReverse->Insert(new Node(i, prop2));
		ili = ili->getNext();
	}
	delete allIDs;

	// Compute edge betweeness scores.
	long double **scores = computeEdgeBetweeness(g, idMap);

	long double modularityScore = 0;
	long double prevModularityScore = 0;

	bool finished = false;
	while (!finished) {
		// Remove highest scoring edge.
		long double maxScore = -1;
		int maxEdge[2] = { -1, -1 };
		for (int i = 0; i < nodes; i++) {
			for (int j = 0; j < nodes; j++) {
				if (i == j)
					continue;
				if (scores[i][j] > maxScore) {
					maxScore = scores[i][j];
					maxEdge[0] = i;
					maxEdge[1] = j;
				}
			}
		}

		for (int i = 0; i < nodes; i++)
			free(scores[i]);
		free(scores);

		if (maxScore <= 0.000) {
			for (int i = 0; i < nodes; i++)
				free(scores[i]);
			free(scores);
			delete idMap;
			delete idMapReverse;
			return g->findCommunities();
		}

		int realID1 = idMapReverse->Lookup(maxEdge[0])->getNode()->getProperties()->getIntegerProperty(0);
		int realID2 = idMapReverse->Lookup(maxEdge[1])->getNode()->getProperties()->getIntegerProperty(0);

		List *edgeList = g->lookupItem(realID1)->getEdgeList();
		EdgeListItem *head = (EdgeListItem*) edgeList->getHead();
		while (head) {
			if (head->getElement()->getEndNodeId() == realID2) {
				edgeList->deleteItem(head);
				break;
			} else
				head = head->getNext();
		}
		edgeList = g->lookupItem(realID2)->getEdgeList();
		head = (EdgeListItem*) edgeList->getHead();
		while (head) {
			if (head->getElement()->getEndNodeId() == realID1) {
				edgeList->deleteItem(head);
				break;
			} else
				head = head->getNext();
		}

		// Re-compute edge betweeness scores.
		scores = computeEdgeBetweeness(g, idMap);

		// Compute graph's modularity score.
		modularityScore = g->getModularityScore();

		if (maxModularity < modularityScore) {
			maxModularity = modularityScore;
			maxModularitySet = true;
			if (deletedEdges)
				delete deletedEdges;
			deletedEdges = new List();
		}

		if (maxModularitySet) {
			if (modularityScore != maxModularity) {
				deletedEdges->insertItem(new EdgeListItem(new Edge(realID1, realID2, NULL)));
				deletedEdges->insertItem(new EdgeListItem(new Edge(realID2, realID1, NULL)));
			}
		}

		if ((modularityScore > modularity) || (modularityScore < 0.00001)) {
			finished = true;

			if (!deletedEdges->isEmpty()) {
				EdgeListItem *eli = (EdgeListItem*) deletedEdges->getHead();
				while (eli) {
					Edge *e = eli->getElement();
					int id1 = e->getStartNodeId();
					int id2 = e->getEndNodeId();
					g->lookupItem(id1)->getEdgeList()->insertItem(new EdgeListItem(new Edge(id1, id2, NULL)));
					g->lookupItem(id2)->getEdgeList()->insertItem(new EdgeListItem(new Edge(id2, id1, NULL)));
					eli = eli->getNext();
				}
				delete deletedEdges;
			}
		}

		prevModularityScore = modularityScore;
	}

	for (int i = 0; i < nodes; i++)
		free(scores[i]);
	free(scores);
	delete idMap;
	delete idMapReverse;
	return g->findCommunities();
}

