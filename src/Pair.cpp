/*
 * Pairr.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include "Pair.h"

using namespace std;

Pair::Pair(int nodeID, int distance) {
	this->nodeID = nodeID;
	this->distance = distance;
}

int Pair::getDistance() {
	return distance;
}

int Pair::getNodeId() {
	return nodeID;
}

Pair::~Pair() {
}

void Pair::print() {
	cout << "Printing Pair" << endl;
	cout << "    ID: " << this->nodeID << endl;
	cout << "    Distance: " << this->distance << endl;
}
