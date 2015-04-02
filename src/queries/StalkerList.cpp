/*
 * StalkerList.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#include "StalkerList.h"

StalkerList::StalkerList() {}

StalkerList::~StalkerList() {}

void StalkerList::insertStalker(Stalker* stalker) {
	StalkerListItem *mli = new StalkerListItem(stalker);
	if (!mli) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	if (this->size == 0) {
		this->head = mli;
		this->tail = mli;
	} else {
		StalkerListItem *cur = (StalkerListItem*) this->getHead();
		if (cur->getStalker()->getCentralityScore() < stalker->getCentralityScore()) {
			mli->setNext(cur);
			cur->setPrevious(mli);
			this->head = mli;
		} else {
			while ((cur = (StalkerListItem*) (cur->getNext())) != NULL) {
				if (cur->getStalker()->getCentralityScore() < stalker->getCentralityScore()) {
					mli->setNext(cur);
					mli->setPrevious(cur->getPrevious());
					cur->getPrevious()->setNext(mli);
					cur->setPrevious(mli);
					break;
				}
			}
			if (mli->getNext() == NULL) {
				mli->setPrevious(this->getTail());
				this->tail->setNext(mli);
				this->tail = mli;
			}
		}
	}
	this->size++;
}

Stalker* StalkerList::removeHead() {
	StalkerListItem *temp = (StalkerListItem*) this->head;
	if (!temp)
		return NULL;

	this->head = this->head->getNext();

	if (this->head == NULL)
		this->tail = NULL;
	else
		this->head->setPrevious(NULL);

	Stalker *ret = new Stalker(temp->getStalker()->getID(), temp->getStalker()->getCentralityScore());
	if (!ret) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	delete temp;
	this->size--;
	return ret;
}
