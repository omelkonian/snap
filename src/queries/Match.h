/*
 * Match.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include <iostream>

using namespace std;

class Match {
	int ID;
	double similarityScore;

public:
	Match(int id, double similarityScore);
	virtual ~Match();

	int getID() {
		return this->ID;
	}

	double getSimilarityScore() {
		return this->similarityScore;
	}

	void print() {
		cout << "Printing Match" << endl;
		cout << "  ID: " << this->ID << endl;
		cout << "  similScore: " << this->similarityScore << endl;
	}
};
