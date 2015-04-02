/*
 * TrustNode.h
 *
 *  Created on: Jan 10, 2015
 *      Author: athan
 */

#pragma once
#include "properties/Properties.h"
#include "Node.h"

class TrustNode: public Node {
	Properties *tidalTrustProperties;			//tidal trust algo
public:

	TrustNode(int id, Properties* properties, Properties *tidalTrustProperties);
	virtual ~TrustNode();

	Properties* getTidalTrustProperties();
	void setTidalTrustProperties(Properties* tidalTrustProperties);

	void printPlusTrustValues();
};
