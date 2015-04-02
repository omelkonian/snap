/*
 * MatchesList.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#include "MatchesList.h"
#include <assert.h>

MatchesList::MatchesList() {
}

MatchesList::~MatchesList() {
//	cout << "Deleting MatchesList" << endl;
	while (!this->isEmpty()) {
		delete this->removeHead();
	}
	assert(this->isEmpty());
}

void MatchesList::insertMatch(Match* match) {
	MatchListItem *mli = new MatchListItem(match);
	if (!mli) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	if (this->size == 0) {
		this->head = mli;
		this->tail = mli;
	} else {
		MatchListItem *cur = (MatchListItem*) this->getHead();
		if (cur->getMatch()->getSimilarityScore() < match->getSimilarityScore()) {
			mli->setNext(cur);
			cur->setPrevious(mli);
			this->head = mli;
		} else {
			while ((cur = (MatchListItem*) (cur->getNext())) != NULL) {
				if (cur->getMatch()->getSimilarityScore() < match->getSimilarityScore()) {
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

Match* MatchesList::removeHead() {
	MatchListItem *temp = (MatchListItem*) this->head;
	this->head = this->head->getNext();
	if (this->head == NULL)
		this->tail = NULL;
	else
		this->head->setPrevious(NULL);

	Match *ret = new Match(temp->getMatch()->getID(), temp->getMatch()->getSimilarityScore());
	if (!ret) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	delete temp;
	this->size--;
	return ret;
}
