/*
 * MatchListItem.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#include "MatchListItem.h"

MatchListItem::MatchListItem(Match* match) {
	this->match = match;
}

MatchListItem::~MatchListItem() {
	delete this->match;
}

Match* MatchListItem::getMatch() {
	return this->match;
}
