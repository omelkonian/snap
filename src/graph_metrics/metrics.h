/*
 * metrics.h
 *
 *  Created on: 29 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../Graph.h"

void degreeDistribution(Graph *g, bool checkFlag);

int diameter(Graph *g);

double averagePathLength(Graph *g);

void numberOfCCsMaxCC(Graph* g, int* numberOfCCs, int* maxCC);
int numberOfCCs(Graph *g);
int maxCC(Graph *g);

double density(Graph *g);

double closenessCentrality(Node *n, Graph *g);
double betweennessCentrality(Node *n, Graph *g);

long double** computeEdgeBetweeness(Graph *g, LinearHashTable *idMap);
