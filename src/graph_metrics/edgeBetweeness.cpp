/*
 * edgeBetweeness.cpp
 *
 *  Created on: 10 Jan 2015
 *      Author: Orestis Melkonian
 */

#include <cstdlib>

#include "../graph_metrics/metrics.h"
#include "../properties/Properties.h"
#include "../list/IntegerListItem.h"
#include "../list/EdgeListItem.h"
#include "../search/ExtendedBFS2.h"

long double** computeEdgeBetweeness(Graph *g, LinearHashTable *idMap) {
	int nodes = g->getNodeNo();

	// Initialise array.
	long double **scores = (long double**) malloc(nodes * sizeof(long double*));
	if (!scores) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	for (int i = 0; i < nodes; i++) {
		scores[i] = (long double*) malloc(nodes * sizeof(long double));
		if (!scores[i]) {
			cout << "ERROR: Unable to allocate memory." << endl;
			return NULL;
		}
		for (int j = 0; j < nodes; j++)
			scores[i][j] = 0;
	}

	List *allIDs = g->getAllIDs();
	IntegerListItem *cur1 = (IntegerListItem*) allIDs->getHead();
	while (cur1) {
//		IntegerListItem *cur2 = cur1->getNext();
		IntegerListItem *cur2 = (IntegerListItem*) allIDs->getHead(); // only use for directed graphs
		while (cur2) {
			if (cur2->getInt() == cur1->getInt()) {
				cur2 = cur2->getNext();
				continue;
			}
			// Execute ExtendedBFS2.
			ExtendedBFS2 *ebfs = new ExtendedBFS2(g, cur1->getInt(), cur2->getInt());
			if (!ebfs) {
				cout << "ERROR: Unable to allocate memory." << endl;
				return NULL;
			}
			ebfs->run();

			if (ebfs->getShortestPathNo() != 0) {
				long double temp[nodes][nodes];
				for (int i = 0; i < nodes; i++) {
					for (int j = 0; j < nodes; j++)
						temp[i][j] = 0;
				}

				ListListItem *lli = (ListListItem*) ebfs->getShortestPaths()->getHead();
				while (lli) {
					List *path = lli->getList();
					EdgeListItem *eli = (EdgeListItem*) path->getHead();
					while (eli) {
						int startID = eli->getElement()->getStartNodeId();
						int endID = eli->getElement()->getEndNodeId();
						int hashedStartID = idMap->Lookup(startID)->getNode()->getProperties()->getIntegerProperty(0);
						int hashedEndID = idMap->Lookup(endID)->getNode()->getProperties()->getIntegerProperty(0);

						temp[hashedStartID][hashedEndID] += 1.0;

						eli = eli->getNext();
					}
					lli = lli->getNext();
				}
				// Update array of values.
				for (int i = 0; i < nodes; i++) {
					for (int j = 0; j < nodes; j++) {
						scores[i][j] += (long double) (temp[i][j] / (long double) ebfs->getShortestPathNo());
					}
				}
			}
			cur2 = cur2->getNext();
			delete ebfs;
		}
		cur1 = cur1->getNext();
	}
	delete allIDs;

	return scores;
}

