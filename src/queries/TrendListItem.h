/*
 * TrendListItem.h
 *
 *  Created on: Dec 21, 2014
 *      Author: athan
 */

#pragma once
#include "Trend.h"
#include "../list/ListItem.h"

class TrendListItem: public ListItem {
	Trend *trend;
public:
	TrendListItem(Trend *trend);
	virtual ~TrendListItem();

	Trend* getTrend();
	void print();
};

