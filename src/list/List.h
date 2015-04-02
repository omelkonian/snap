/*
 * List.h
 *
 *  Created on: 3 Nov 2014
 *      Author: Orestis Melkonian
 */
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "ListItem.h"

/**
 * List that can hold Buckets (for representing an actual Bucket of the hash table),
 * Edges(for implementing a node's neighbors).
 */
class List {
protected:
	int size;
	ListItem *head;
	ListItem *tail;
public:
	// Constructor and Destructor
	List();
	virtual ~List();

	// Getters
	int getSize();
	ListItem* getHead();
	ListItem* getTail();

	// Checkers
	bool isEmpty();

	// Insertion and Deletion
	virtual bool insertItem(ListItem *item);
	bool deleteItem(ListItem *item);
	bool contains(ListItem *item);

	// Printers
	virtual void print();
	void printElements();

	void setNull();
};
