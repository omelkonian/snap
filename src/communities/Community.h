/*
 * Community.h
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */
#pragma once
#include "../list/List.h"

class Community {
	int communityID;
	List* communityMembers;
public:
	Community(int communityID, List* communityMembers);
	virtual ~Community();

	int getCommunityId();

	List* getCommunityMembers();

	void print();
};
