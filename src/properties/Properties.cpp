/*
 * Properties.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Properties.h"

using namespace std;

Properties::Properties(int size) {
	this->size = size;
	this->properties = new Property*[size];
	if (!this->properties) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	for (int i = 0; i < size; i++)
		this->properties[i] = NULL;
}

Properties::~Properties() {
//	cout << "       Deleting Properties" << endl;
	for (int i = 0; i < this->size; i++)
		delete this->properties[i];
	delete[] this->properties;
//	cout << "       Deleted Properties" << endl;
}

int Properties::getSize() {
	return this->size;
}

void Properties::setSize(int size) {
	this->size = size;
}

void Properties::setStringProperty(char *property, int index) {
	this->properties[index] = new StringProperty(property);
	if (!this->properties[index]) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
}

void Properties::setIntegerProperty(int property, int index) {
	this->properties[index] = new IntegerProperty(property);
	if (!this->properties[index]) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
}

int Properties::getIntegerProperty(int index) {
	IntegerProperty *cast = (IntegerProperty*) this->properties[index];
	return cast->getIntegerProperty();
}

char* Properties::getStringProperty(int index) {
	StringProperty *cast = (StringProperty*) this->properties[index];
	return cast->getStringProperty();
}

void Properties::print() {
	cout << "________________________________________" << endl;
	cout << "Printing Properties" << endl;
	if (this == NULL) {
		cout << "NULL properties" << endl;
	} else {
		cout << "    Size: " << this->size << endl;
		for (int i = 0; i < this->size; i++) {
			if (dynamic_cast<IntegerProperty*>(this->properties[i]) != 0)
				cout << "    Property" << i << ": " << ((IntegerProperty*) this->properties[i])->getIntegerProperty() << endl;
			else if (dynamic_cast<DoubleProperty*>(this->properties[i]) != 0)
				cout << "    Property" << i << ": " << ((DoubleProperty*) this->properties[i])->getDoubleProperty() << endl;
			else if (dynamic_cast<StringProperty*>(this->properties[i]) != 0)
				cout << "    Property" << i << ": " << ((StringProperty*) this->properties[i])->getStringProperty() << endl;
			else if (this->properties[i] == NULL)
				cout << "Null Property" << endl;
			else
				cout << "ERROR: Property is not Integer, Double, String or NULL" << endl;
		}
	}
}

void Properties::setDoubleProperty(double property, int index) {
	this->properties[index] = new DoubleProperty(property);
}

double Properties::getDoubleProperty(int index) {
	DoubleProperty *cast = (DoubleProperty*) this->properties[index];
	return cast->getDoubleProperty();
}
