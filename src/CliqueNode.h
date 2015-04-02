/*
 * CliqueNode.h
 *
 *  Created on: Jan 16, 2015
 *      Author: athan
 */

#pragma once
#include "properties/Properties.h"
#include "Node.h"
#include "./list/List.h"

class CliqueNode :public Node {
	List* clique;
public:
	CliqueNode(int id,Properties* properties, List* clique);
	virtual ~CliqueNode();

	List* getClique();
	void setClique(List* clique);

	void printPlusClique();
};

