/*
 * Matches.h
 *
 *  Created on: Dec 5, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "stdlib.h"

#include "Match.h"

class Matches {
	int size;
	Match** topMatches;
public:
	Matches(int limit) {
		this->size = 0;
		this->topMatches = (Match**) malloc(sizeof(Match*) * limit);
	}
	virtual ~Matches() {
		for (int i = 0; i < this->size; i++)
			delete this->topMatches[i];
		free(this->topMatches);
	}

	int getSize() {
		return this->size;
	}
	void incrementSize() {
		this->size++;
	}

	Match** getTopMatches() {
		return this->topMatches;
	}

	void print() {
		cout << "Printing Matches" << endl;
		for (int i = 0; i < this->size; i++)
			this->topMatches[i]->print();
	}
};
