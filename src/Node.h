/*
 * Node.h
 *
 *  Created on: 31 Oct 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "properties/Properties.h"

/**
 * Class representing a node (without its relations).
 * Holds the node's ID and its properties.
 */
class Node {
protected:
	int id;
	Properties *properties;
public:
	Node();
	Node(int id, Properties *properties);
	virtual ~Node();

	int getId();

	Properties* getProperties();
	void setProperties(Properties *properties);

	void print();

};
