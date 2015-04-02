/*
 * Properties.h
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "Property.h"
#include "StringProperty.h"
#include "IntegerProperty.h"
#include "DoubleProperty.h"

/**
 * Class that represents the properties of a node or an edge.
 * Holds its size (number of properties) and the array of properties.
 */
class Properties {
	int size; // Number of properties (PERSON_PROPERTIES_NUM or PERSON_REL_PROPERTIES_NUM).
	Property **properties; // Array of properties (StringProperty or IntegerProperty).
public:
	Properties(int size);
	virtual ~Properties();

	int getSize();
	void setSize(int size);

	/**
	 * property: the type of the property
	 * index: the position on the property array
	 */
	void setStringProperty(char* property, int index);

	/**
	 * property: the type of the property
	 * index: the position on the property array
	 */
	void setIntegerProperty(int property, int index);
	/**
	 * property: the type of the property
	 * index: the position on the property array
	 */
	void setDoubleProperty(double property, int index);

	/**
	 * Get the integer property at given index.
	 */
	double getDoubleProperty(int index);

	/**
	 * Get the integer property at given index.
	 */
	int getIntegerProperty(int index);

	/**
	 * Get the string property at given index.
	 */
	char* getStringProperty(int index);

	/**
	 * Prints the properties.
	 */
	void print();
};
