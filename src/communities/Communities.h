/*
 * Communities.h
 *
 *  Created on: Jan 10, 2015
 *      Author: athan
 */
#pragma once
#include "Community.h"

class Communities {
	List* communitiesList;
public:
	Communities(List* communitiesList);
	virtual ~Communities();

	void setCommunitiesList(List* communitiesList);
	List* getCommunitiesList();

	int getCommunity(int nodeID);

	void print();
};

