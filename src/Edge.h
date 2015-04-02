/*
 * Edge.h
 *
 *  Created on: 5 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "properties/Properties.h"

/**
 * Class that represents an edge between two nodes.
 * Holds the two nodes' IDs and the properties of the edge connecting them.
 */
class Edge {
	int startNodeID;
	int endNodeID;
	Properties *properties;
public:
	Edge(int startId, int endId, Properties *properties);
	virtual ~Edge();

	int getStartNodeId();
	int getEndNodeId();
	Properties* getProperties();

	void print();
};
