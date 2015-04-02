/*
 * findCliques.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: athan
 */

#include "findCliques.h"

using namespace std;


bool checkEdge(Graph * graph, List* ids , int endNodeId, LinearHashTable *idMapReverse){
	int edgeEndNodeId = idMapReverse->Lookup(endNodeId)->getNode()->getProperties()->getIntegerProperty(0);
	IntegerListItem* ili = (IntegerListItem*) ids->getHead();
	while(ili != NULL){
		int startNodeId= idMapReverse->Lookup(ili->getInt())->getNode()->getProperties()->getIntegerProperty(0);
		BucketItem* startNodeBi = graph->lookupItem(startNodeId);
		List* edgeList = startNodeBi->getEdgeList();
		EdgeListItem* edgeLI =(EdgeListItem*) edgeList->getHead();
		bool found = false;
		while(edgeLI != NULL){
			if(edgeLI->getElement()->getEndNodeId() == edgeEndNodeId)
				found = true;
			edgeLI = edgeLI->getNext();
		}
		if(!found)
			return false;
		ili =ili->getNext();
	}
	return true;
}


void iterate(Graph *g, List *cliques, List *ids, int MIN, int MAX, int k, LinearHashTable *idMapReverse) {
    if (k == 0) {
    	List *copy = new List();
        IntegerListItem *ili = (IntegerListItem*) ids->getHead();
        while (ili) {
            copy->insertItem(new IntegerListItem(idMapReverse->Lookup(ili->getInt())->getNode()->getProperties()->getIntegerProperty(0)));
            ili = ili->getNext();
        }
        cliques->insertItem(new ListListItem(copy));
    }
    else {
        for (int i = MIN; i < MAX; i++) {
            if(!checkEdge(g,ids,i, idMapReverse))
            	continue;
            ids->insertItem(new IntegerListItem(i));
            iterate(g, cliques, ids, i+1, MAX, k-1, idMapReverse);
            ids->deleteItem(ids->getTail());
        }
    }
}



























