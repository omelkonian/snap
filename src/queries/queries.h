/*
 * queries.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "Matches.h"
#include "../Graph.h"
#include "../Node.h"
#include "../Edge.h"
#include "Stalkers.h"

#define DATA_SIZE 10000
#define POST_DATA_SIZE 100000000
/*
 * Query 1: Match Suggestion
 */
Matches* matchSuggestion(Node *n, int k, int h, int x, int limit, Graph *g);

/*
 * Query 2: Top Stalkers
 */
Graph* getTopStalkers(int k, int x, int centralityMode, Graph *g, Stalkers *st);

/**
 * Query 3: Find Trends
 */
void findTrends(int k, Graph *g, char ***womenTrends, char ***menTrends);

/**
 * Query 4: Trust
 */
Graph* buildTrustGraph(char *forum, Graph *g);
double estimateTrust(Node *startNode, Node *endNode, Graph *trustGraph);
