/*
 * Pairr.h
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
class Pair {
	int nodeID;
	int distance;
public:
	Pair(int nodeID, int distance);
	virtual ~Pair();
	int getDistance();
	int getNodeId();

	void print();
};
