/*
 * TrendListItem.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: athan
 */


#include <iostream>
#include "TrendListItem.h"

using namespace std;
TrendListItem::TrendListItem(Trend* trend) {
	this->trend = trend;
}

TrendListItem::~TrendListItem() {
	delete this->trend;
}

Trend* TrendListItem::getTrend() {
	return this->trend;
}

void TrendListItem::print() {
	cout << "TrendListItem with Trend:" << endl;
	cout << "Trend :" << this->trend->getNameOfTrend() << endl;
	cout << "Vibe :" << this->trend->getVibe() << endl;
}
