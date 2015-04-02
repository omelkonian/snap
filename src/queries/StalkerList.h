/*
 * StalkerList.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../list/List.h"
#include "Stalker.h"
#include "StalkerListItem.h"

class StalkerList: public List {
public:
	StalkerList();
	virtual ~StalkerList();

	void insertStalker(Stalker *stalker);

	Stalker* removeHead();
};
