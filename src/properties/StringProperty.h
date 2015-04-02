/*
 * StringProperty.h
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "Property.h"

/**
 * Class that represents a string property of a node or an edge.
 * Holds the string.
 */
class StringProperty: public Property {
	char *property;
public:
	StringProperty(char *property);
	virtual ~StringProperty();

	char* getStringProperty();

	int getIntegerProperty();

	void print();
};
