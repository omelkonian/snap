/*
 * Trend.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: athan
 */

#include "Trend.h"
#include <cstring>
#include "../project_main/defines.h"

using namespace std;

Trend::Trend(int vibe, char* nameOfTrend) {
	this->vibe = vibe;
	this->nameOfTrend = new char[MAX_WORD];
	strcpy(this->nameOfTrend, nameOfTrend);
}

Trend::~Trend() {
	delete[] this->nameOfTrend;
}

char* Trend::getNameOfTrend() {
	return this->nameOfTrend;
}

void Trend::setNameOfTrend(char* nameOfTrend) {
	strcpy(this->nameOfTrend , nameOfTrend);
}

int Trend::getVibe() {
	return this->vibe;
}

void Trend::setVibe(int vibe) {
	this->vibe = vibe;
}
