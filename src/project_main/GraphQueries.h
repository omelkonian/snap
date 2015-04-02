#pragma once
#include "../queries/queries.h"
#include "../graph_metrics/metrics.h"
#include "GraphLib.h"
#include "../queries/Matches.h"
#include "../queries/Stalkers.h"
#include "../TrustNode.h"


//help functions
Graph* loadGraph(int bucketsNumber, int bucketSize);
int getStalkerID(int position, Stalkers* stalk);
int getMatch(int pairNumber, Matches* match);

//metrics functions - already defined in metrics.h

//queries functions - already defined in queries.h
