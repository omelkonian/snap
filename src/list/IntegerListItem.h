/*
 * IntegerListItem.h
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "ListItem.h"

class IntegerListItem: public ListItem {
	int element;
public:
	IntegerListItem(int element);
	virtual ~IntegerListItem();

	int getInt() {
		return this->element;
	}

	IntegerListItem* getNext();

	void print();
};
