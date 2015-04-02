/*
 * Edge.cpp
 *
 *  Created on: 5 Nov 2014
 *      Author: Orestis Melkonian
 */

#include "Edge.h"
#include <iostream>

using namespace std;

Edge::Edge(int startId, int endId, Properties *properties) {
	this->startNodeID = startId;
	this->endNodeID = endId;
	this->properties = properties;
}

int Edge::getStartNodeId() {
	return startNodeID;
}

int Edge::getEndNodeId() {
	return endNodeID;
}

Properties* Edge::getProperties() {
	return this->properties;
}

Edge::~Edge() {
//	cout << "     Deleting Edge" << endl;
	delete this->properties;
//	cout << "     Deleted Edge" << endl;
}

void Edge::print() {
	cout << "________________________________________" << endl;
	cout << "Printing Edge:" << endl;
	cout << "    StartID: " << this->startNodeID << endl;
	cout << "    EndID: " << this->endNodeID << endl;
	this->properties->print();
}
