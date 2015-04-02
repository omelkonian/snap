/*
 * DoubleProperty.cpp
 *
 *  Created on: Jan 2, 2015
 *      Author: athan
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "DoubleProperty.h"

using namespace std;

DoubleProperty::DoubleProperty(double property) {
	this->property = property;
}

DoubleProperty::~DoubleProperty() {
}

double DoubleProperty::getDoubleProperty() {
	return this->property;
}

char* DoubleProperty::getStringProperty() {
	cout << "ERROR: trying to get string from DoubleProperty" << endl;;
	return NULL;
}

void DoubleProperty::print() {
	cout << "________________________________________" << endl;
	cout << "Printing DoubleProperty" << endl;
	cout << "    Property(Double): " << this->property << endl;
}

