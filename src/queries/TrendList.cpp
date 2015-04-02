/*
 * TrendList.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: athan
 */


#include <assert.h>
#include "TrendList.h"
#include <iostream>
using namespace std;

TrendList::TrendList() {
}

TrendList::~TrendList() {
	//cout << "Deleting TrendList" << endl;
	while (!this->isEmpty()) {
			delete this->removeHead();
		}
	assert(this->isEmpty());
}

void TrendList::insertTrend(Trend* trend) {
	TrendListItem *tli = new TrendListItem(trend);
	if (this->size == 0) {
		this->head = tli;
		this->tail = tli;
	}
	else {
		TrendListItem *cur = (TrendListItem*)this->getHead();
		if (cur->getTrend()->getVibe() < trend->getVibe()) {
			tli->setNext(cur);
			cur->setPrevious(tli);
			this->head = tli;
		}
		else {
			while ((cur = (TrendListItem*)(cur->getNext())) != NULL) {
				if (cur->getTrend()->getVibe() < trend->getVibe()) {
					tli->setNext(cur);
					tli->setPrevious(cur->getPrevious());
					cur->getPrevious()->setNext(tli);
					cur->setPrevious(tli);
					break;
				}
			}
			if (tli->getNext() == NULL) {
				tli->setPrevious(this->getTail());
				this->tail->setNext(tli);
				this->tail = tli;
			}
		}
	}
	this->size++;
}

Trend* TrendList::removeHead() {

	TrendListItem *temp = (TrendListItem*)this->head;
	if(this->head != NULL){
		this->head = this->head->getNext();
		if (this->head == NULL)
			this->tail = NULL;
		else
			this->head->setPrevious(NULL);

		Trend *ret = new Trend(temp->getTrend()->getVibe(), temp->getTrend()->getNameOfTrend());
		delete temp;

		this->size--;
		return ret;
	}
	else
		return NULL;

}
