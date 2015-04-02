/*
 * findCliques.h
 *
 *  Created on: Jan 15, 2015
 *      Author: athan
 */

#pragma once
#include "../Graph.h"
#include "../list/List.h"
#include "../list/Queue.h"
#include <iostream>

using namespace std;


bool checkEdge(Graph * graph, List* ids , int endNodeId, LinearHashTable *idMapReverse);
void iterate(Graph *g, List *cliques, List *ids, int MIN, int MAX, int k, LinearHashTable *idMapReverse);


