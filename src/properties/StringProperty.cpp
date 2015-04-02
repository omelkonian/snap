/*
 * StringProperty.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "StringProperty.h"
#include "../project_main/defines.h"

using namespace std;

StringProperty::StringProperty(char* property) {
	this->property = new char[MAX_WORD];
	if (!this->property) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	strcpy(this->property, property);
}

StringProperty::~StringProperty() {
	delete[] this->property;
}

char* StringProperty::getStringProperty() {
	return this->property;
}

int StringProperty::getIntegerProperty() {
	cout << "ERROR: trying to get int from StringProperty" << endl;
	return -1;
}

void StringProperty::print() {
	cout << "________________________________________" << endl;
	cout << "Printing StringProperty" << endl;
	cout << "    Property(char*): " << this->property << endl;
}
