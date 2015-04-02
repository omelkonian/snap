/*
 * communities.h
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#pragma once

#include "../list/List.h"
#include "Community.h"
#include "Communities.h"
#include "../Graph.h"

// Returns an array of N pointers to graphs of the top-N forums.
Graph** getTopNForums(int n);

Communities* girvanNewman(double modularity, Graph *g);
Communities* cliquePercolationMethod(int k , Graph* graph);
