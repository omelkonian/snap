/*
 * GraphListItem.h
 *
 *  Created on: 9 Jan 2015
 *      Author: Orestis Melkonian
 */

#pragma once
#include "ListItem.h"
#include "../Graph.h"

class GraphListItem: public ListItem {
	Graph *graph;
public:
	GraphListItem(Graph *graph);
	virtual ~GraphListItem();

	Graph* getGraph();
	GraphListItem* getNext();

	void print();
};
