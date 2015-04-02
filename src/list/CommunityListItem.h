/*
 * CommunityListItem.h
 *
 *  Created on: Jan 10, 2015
 *      Author: athan
 */

#pragma once
#include "../communities/Community.h"
#include "ListItem.h"

class CommunityListItem: public ListItem {
	Community *community;
public:
	CommunityListItem(Community *community);
	virtual ~CommunityListItem();

	CommunityListItem* getNext();

	Community* getCommunity();

	void print();
};
