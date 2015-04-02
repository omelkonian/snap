/*
 * Stalkers.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: Orestis Melkonian
 */

#include "Stalkers.h"
#include <cstdlib>

Stalkers::Stalkers(int k) {
	this->size = 0;
	this->topStalkers = (Stalker*) malloc(k * sizeof(Stalker));
	if (!this->topStalkers) {
		cout << "ERROR: Unable to allocate memory." << endl;
	}
}

Stalkers::~Stalkers() {
	free(this->topStalkers);
}

int Stalkers::getSize() {
	return this->size;
}

void Stalkers::incrementSize() {
	this->size++;
}

Stalker* Stalkers::getTopStalkers() {
	return this->topStalkers;
}

void Stalkers::print() {
	cout << "Printing Stalkers" << endl;
	for (int i = 0; i < this->size; i++)
		this->topStalkers[i].print();
}
