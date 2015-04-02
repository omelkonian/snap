/*
 * TrustNode.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: athan
 */
#include "TrustNode.h"
#include <iostream>
using namespace std;

TrustNode::TrustNode(int id, Properties* properties, Properties* tidalTrustProperties) :
		Node(id, properties) {

	this->tidalTrustProperties = tidalTrustProperties;
}

TrustNode::~TrustNode() {
	delete this->tidalTrustProperties;
}

Properties* TrustNode::getTidalTrustProperties() {
	return this->tidalTrustProperties;
}

void TrustNode::setTidalTrustProperties(Properties *tidalTrustProperties) {
	this->tidalTrustProperties = tidalTrustProperties;
}

void TrustNode::printPlusTrustValues() {
	cout << "________________________________________" << endl;
	cout << "Printing Node" << endl;
	cout << "    ID: " << this->id << endl;
	this->properties->print();
	this->tidalTrustProperties->print();
}
