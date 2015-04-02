/*
 * Match.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#include "Match.h"

Match::Match(int id, double similarityScore) {
	this->ID = id;
	this->similarityScore = similarityScore;

}

Match::~Match() {
	// TODO Auto-generated destructor stub
}

