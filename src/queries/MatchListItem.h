/*
 * MatchListItem.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "Matches.h"
#include "../list/ListItem.h"

class MatchListItem: public ListItem {
	Match *match;
public:
	MatchListItem(Match *match);
	virtual ~MatchListItem();

	Match* getMatch();
};
