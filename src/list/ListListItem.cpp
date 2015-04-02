/*
 * ListListItem.cpp
 *
 *  Created on: 30 Nov 2014
 *      Author: Orestis Melkonian
 */

#include "ListListItem.h"
#include "IntegerListItem.h"
#include "EdgeListItem.h"
#include <iostream>

using namespace std;

ListListItem::ListListItem(List *list) {
	this->list = list;
}

ListListItem::~ListListItem() {
//	cout << "Deleting ListListItem" << endl;
	delete this->list;
}

List* ListListItem::getList() {
	return this->list;
}

ListListItem* ListListItem::getNext() {
	return (ListListItem*) this->next;
}

void ListListItem::print() {
	cout << "Printing Path" << endl;
	ListItem *cur = this->list->getHead();
	while (cur != NULL) {
		if (dynamic_cast<IntegerListItem*>(cur))
			cur = (IntegerListItem*) cur;
		else if (dynamic_cast<EdgeListItem*>(cur))
			cur = (EdgeListItem*) cur;
		cur->print();
		cur = cur->getNext();
	}
}
