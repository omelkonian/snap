/*
 * EdgeListItem.h
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "../Edge.h"
#include "ListItem.h"

/**
 * An edge that is an item of a list.
 */
class EdgeListItem: public ListItem {
	Edge *element;
public:
	EdgeListItem(Edge *element);
	virtual ~EdgeListItem();

	EdgeListItem* getNext();
	EdgeListItem* getPrevious();
	Edge* getElement();

	void print();
};
