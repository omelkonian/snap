/*
 * TrendList.h
 *
 *  Created on: Dec 21, 2014
 *      Author: athan
 */

#pragma once
#include "../list/List.h"
#include "TrendListItem.h"
#include "Trend.h"

class TrendList: public List {
public:
	TrendList();
	virtual ~TrendList();

	void insertTrend(Trend *trend);

	Trend* removeHead();
};

