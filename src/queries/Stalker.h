/*
 * Stalker.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include <iostream>

using namespace std;

class Stalker {
	int id;
	double centralityScore;
public:
	Stalker(int id, double centralityScore);
	virtual ~Stalker();

	int getID() {
		return this->id;
	}

	double getCentralityScore() {
		return this->centralityScore;
	}

	void print() {
		cout << "Stalker ID: " << this->id << "  Centrality: " << this->centralityScore << endl;
	}
};
