/*
 * StalkerListItem.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../list/ListItem.h"
#include "Stalker.h"

class StalkerListItem: public ListItem {
	Stalker *stalker;
public:
	StalkerListItem(Stalker *stalker) {
		this->stalker = stalker;
	}
	virtual ~StalkerListItem() {
		delete this->stalker;
	}

	Stalker* getStalker() {
		return this->stalker;
	}

	StalkerListItem* getPrevious() {
		return (StalkerListItem*) this->previous;
	}

	StalkerListItem* getNext() {
		return (StalkerListItem*) this->next;
	}

	void print() {
		this->stalker->print();
	}
};
