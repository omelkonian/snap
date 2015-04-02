/*
 * Trend.h
 *
 *  Created on: Dec 21, 2014
 *      Author: athan
 */

#pragma once

class Trend {
	int vibe;
	char * nameOfTrend;

public:
	Trend(int vibe, char* nameOfTrend);
	virtual ~Trend();

	char* getNameOfTrend();
	void setNameOfTrend(char* nameOfTrend);

	int getVibe();
	void setVibe(int vibe);
};
