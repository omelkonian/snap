/*
 * GraphListItem.cpp
 *
 *  Created on: 9 Jan 2015
 *      Author: Orestis Melkonian
 */

#include "GraphListItem.h"

GraphListItem::GraphListItem(Graph* graph) {
	this->graph = graph;
}

GraphListItem::~GraphListItem() {
	// TODO Auto-generated destructor stub
}

Graph* GraphListItem::getGraph() {
	return this->graph;
}

GraphListItem* GraphListItem::getNext() {
	return (GraphListItem*) this->next;
}

void GraphListItem::print() {
	this->graph->printInfo();
}
