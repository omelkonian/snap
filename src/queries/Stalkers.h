/*
 * Stalkers.h
 *
 *  Created on: Dec 22, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "Stalker.h"

class Stalkers {
	int size;
	Stalker *topStalkers;
public:
	Stalkers(int k);
	virtual ~Stalkers();

	int getSize();
	void incrementSize();

	Stalker* getTopStalkers();

	void print();
};
