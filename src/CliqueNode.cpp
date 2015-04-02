/*
 * CliqueNode.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: athan
 */

#include "CliqueNode.h"
#include "./list/List.h"
#include <iostream>

using namespace std;


CliqueNode::CliqueNode(int id,Properties* properties, List* clique):
	Node(id,properties){
	this->clique = clique;
}

CliqueNode::~CliqueNode() {
//	cout<<"Deleting Clique Node"<<endl;
	delete this->clique;
}

List* CliqueNode::getClique() {
	return this->clique;
}

void CliqueNode::setClique(List* clique){
	this->clique = clique;
}

void CliqueNode::printPlusClique() {
	cout << "________________________________________" << endl;
	cout << "Printing CliqueNode" << endl;
	cout << "    ID: " << this->id << endl;
	this->properties->print();
	this->clique->printElements();
	cout << "________________________________________" << endl;
}

