/*
 * ResultSet.h
 *
 *  Created on: Nov 20, 2014
 *      Author: athan
 */

#pragma once
#include "../Pair.h"
#include "BFS.h"

class ResultSet {
	BFS *bfs;
public:
	ResultSet(BFS *bfs);
	virtual ~ResultSet();

	Pair* next();
};
