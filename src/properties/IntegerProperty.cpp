/*
 * IntegerProperty.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "IntegerProperty.h"

using namespace std;

IntegerProperty::IntegerProperty(int property) {
	this->property = property;
}

IntegerProperty::~IntegerProperty() {
}

int IntegerProperty::getIntegerProperty() {
	return this->property;
}

char* IntegerProperty::getStringProperty() {
	cout << "ERROR: trying to get string from IntegerProperty" << endl;
	return NULL;
}

void IntegerProperty::print() {
	cout << "________________________________________" << endl;
	cout << "Printing IntegerProperty" << endl;
	cout << "    Property(Int): " << this->property << endl;
}
