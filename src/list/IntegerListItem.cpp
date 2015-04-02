/*
 * IntegerListItem.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: Orestis Melkonian
 */

#include "IntegerListItem.h"
#include <iostream>

using namespace std;

IntegerListItem::IntegerListItem(int element) {
	this->element = element;
}

IntegerListItem::~IntegerListItem() {
//	cout << "     Deleting IntegerListItem" << endl;
}

void IntegerListItem::print() {
	cout << "Integer: " << this->element << endl;
}

IntegerListItem* IntegerListItem::getNext() {
	return (IntegerListItem*) this->next;
}
