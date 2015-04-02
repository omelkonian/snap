/*
 * ForumList.cpp
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#include "ForumList.h"
#include <assert.h>
#include <iostream>

#include "../../list/ForumListItem.h"
using namespace std;

ForumList::ForumList(int limit) {
	this->limit = limit;
}

ForumList::~ForumList() {
	//	cout << "Deleting ForumList" << endl;
	while (!this->isEmpty()) {
		delete this->removeHead();
	}
	assert(this->isEmpty());
}

void ForumList::insertForum(Forum* forum) {
	ForumListItem *fli = new ForumListItem(forum);
	if (!fli) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	if (this->size == 0) {
		this->head = fli;
		this->tail = fli;
	} else {
		ForumListItem *cur = (ForumListItem*) this->getHead();
		if (cur->getForum()->getMemberNo() < forum->getMemberNo()) {
			fli->setNext(cur);
			cur->setPrevious(fli);
			this->head = fli;
		} else {
			while ((cur = cur->getNext()) != NULL) {
				if (cur->getForum()->getMemberNo() < forum->getMemberNo()) {
					fli->setNext(cur);
					fli->setPrevious(cur->getPrevious());
					cur->getPrevious()->setNext(fli);
					cur->setPrevious(fli);
					break;
				}
			}
			if (fli->getNext() == NULL) {
				fli->setPrevious(this->getTail());
				this->tail->setNext(fli);
				this->tail = fli;
			}
		}
	}
	this->size++;
}

Forum* ForumList::removeHead() {
	ForumListItem *temp = (ForumListItem*) this->head;
	this->head = this->head->getNext();
	if (this->head == NULL)
		this->tail = NULL;
	else
		this->head->setPrevious(NULL);

	Forum *ret = new Forum(temp->getForum()->getForumID(), temp->getForum()->getMemberNo());
	if (!ret) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	delete temp;
	this->size--;
	return ret;
}

// Removes smaller items that exceed <limit>.
void ForumList::update() {
	if (this->size <= this->limit)
		return;
	int counter = this->size - this->limit;

	ForumListItem *fli = (ForumListItem*) this->tail;
	while (counter-- > 0) {
		ForumListItem *temp = fli;
		fli = fli->getNext();
		if (counter == 0) {
			this->tail = temp->getPrevious();
			this->tail->setNext(NULL);
		}
		delete temp;
	}
	this->size = this->limit;
	return;
}

void ForumList::print() {
	cout << "Printing ForumList" << endl;
	cout << "   Size: " << this->size << endl;
	cout << "   Limit: " << this->limit << endl;
	ForumListItem *fli = (ForumListItem*) this->head;
	while (fli) {
		fli->print();
		fli = fli->getNext();
	}
}
