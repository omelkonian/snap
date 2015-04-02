/*
 * ResultSet.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: athan
 */

#include "ResultSet.h"

ResultSet::ResultSet(BFS *bfs) {
	this->bfs = bfs;
	bfs->step();
}

ResultSet::~ResultSet() {
	delete this->bfs;
}

Pair* ResultSet::next() {
	if (!this->bfs->step())
		return this->bfs->getCurrentPair();
	else
		return NULL;
}
