/*
 * MatchesList.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../list/List.h"
#include "MatchListItem.h"

class MatchesList: public List {
public:
	MatchesList();
	virtual ~MatchesList();

	void insertMatch(Match *match);

	Match* removeHead();
};
