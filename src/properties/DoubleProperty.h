/*
 * DoubleProperty.h
 *
 *  Created on: Jan 2, 2015
 *      Author: athan
 */
#pragma once
#include "Property.h"

/**
 * Class that represents a double property of a node r an edge.
 * Holds the double value.
 */
class DoubleProperty: public Property {
	double property;
public:
	DoubleProperty(double property);
	virtual ~DoubleProperty();

	double getDoubleProperty();

	char* getStringProperty();

	void print();
};
