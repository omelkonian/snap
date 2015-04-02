/**
 *   Header.h
 */

#pragma once
#include "../Graph.h"
#include "../list/List.h"
#include "../list/GraphListItem.h"
#include "../communities/_communities.h"
#include "GraphLib.h"

#define  NUMBER_OF_TOP_N_FORUMS 6

typedef struct forum {
	int size;
	char *name;
} Forum;

typedef struct community {
	int numberOfMembers;
	int *members;
} community;

typedef struct algorithmResults {
	int numberOfCommunities;
	community *communities;
} algorithmResults;

typedef struct cpm {
	char *forum;
	algorithmResults clique3;
	algorithmResults clique4;
} Cpm;

typedef struct gn {
	char *forum;
	algorithmResults results;
} Gn;

typedef enum {
	False, True
} boolean;

Forum** computeTopNForums(Graph ***retGraphs, int topN) {
	Forum **forums = (Forum**) malloc(topN * sizeof(Forum*));

	Graph **graphs = getTopNForums(topN);
	*retGraphs = graphs;

	for (int i = 0; i < topN; i++) {
		Forum *forum = (Forum*) malloc(sizeof(Forum));
		forum->name = (char*) malloc(MAX_STRING_LENGTH);
		strcpy(forum->name ,graphs[i]->getName());
		forum->size = graphs[i]->getNodeNo();
		forums[i] = forum;
	}

	int max = 0;
	int maxIndex = -1;
	int counter = 0;
	int indexes[topN];

	for (int i = 0; i < topN; i++) {
		bool found = false;
		for (int j = 0; j < counter; j++) {
			if (i == indexes[j]) {
				found = true;
				break;
			}
		}
		if (found) {
			if (i == topN - 1) {
				indexes[counter] = maxIndex;
				max = 0;
				maxIndex = -1;
				counter++;
				if (counter == topN)
					break;
				i = -1;
			}
			continue;
		}

		if (forums[i]->size >= max) {
			max = forums[i]->size;
			maxIndex = i;
		}
		if (i == (topN - 1)) {
			indexes[counter] = maxIndex;
			max = 0;
			maxIndex = -1;
			counter++;
			if (counter == topN)
				break;
			i = -1;
		}
	}

	Forum **retForums = (Forum**) malloc(topN * sizeof(Forum*));
	for (int i = 0; i < topN; i++) {
		retForums[i] = forums[indexes[i]];
	}

	free(forums);
	return retForums;
}
