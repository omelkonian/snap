/*
 * IntegerProperty.h
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "Property.h"

/**
 * Class that represents an integer property of a node r an edge.
 * Holds the integer value.
 */
class IntegerProperty: public Property {
	int property;
public:
	IntegerProperty(int property);
	virtual ~IntegerProperty();

	int getIntegerProperty();

	char* getStringProperty();

	void print();
};
