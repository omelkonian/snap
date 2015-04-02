/*
 * Node.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: Orestis Melkonian
 */

#include <iostream>
#include "Node.h"
#include "list/List.h"

using namespace std;

Node::Node(int id, Properties *properties) {
	this->id = id;
	this->properties = properties;
}

Node::~Node() {
//	cout << "    Deleting Node" << endl;
	delete this->properties;
//	cout << "    Deleted Node" << endl;
}

int Node::getId() {
	return this->id;
}

Properties* Node::getProperties() {
	return this->properties;
}

void Node::setProperties(Properties *properties) {
	this->properties = properties;
}

void Node::print() {
	cout << "________________________________________" << endl;
	cout << "Printing Node" << endl;
	cout << "    ID: " << this->id << endl;
	this->properties->print();
}
