/*
 * EdgeListItem.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include "EdgeListItem.h"

using namespace std;

EdgeListItem::EdgeListItem(Edge *element) {
	this->element = element;
}

EdgeListItem::~EdgeListItem() {
//	cout << "     Deleting edgeListItem" << endl;
	delete this->element;
//	cout << "     Deleted edgeListItem" << endl;
}

Edge* EdgeListItem::getElement() {
	return this->element;
}

void EdgeListItem::print() {
	this->element->print();
}

EdgeListItem* EdgeListItem::getNext() {
	return ((EdgeListItem*) this->next);
}

EdgeListItem* EdgeListItem::getPrevious() {
	return ((EdgeListItem*) this->previous);
}
