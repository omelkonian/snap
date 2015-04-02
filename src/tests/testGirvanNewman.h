/*
 * testGirvanNewman.h
 *
 *  Created on: 11 ��� 2015
 *      Author: Orestis Melkonian
 */

#pragma once
#include "tests.h"
#include "../list/CommunityListItem.h"

void _testGirvanNewman() {
	// Example from the .pdf given.
	Graph *g = new Graph(1, 5);
	g->insertNode(new Node(1, NULL));
	g->insertNode(new Node(2, NULL));
	g->insertNode(new Node(3, NULL));
	g->insertNode(new Node(4, NULL));
	g->insertNode(new Node(5, NULL));
	g->insertNode(new Node(6, NULL));
	g->insertNode(new Node(7, NULL));
	g->insertNode(new Node(8, NULL));
	g->insertNode(new Node(9, NULL));

	g->insertEdge(1, new Edge(1, 2, NULL));
	g->insertEdge(1, new Edge(1, 3, NULL));
	g->insertEdge(1, new Edge(1, 4, NULL));
	g->insertEdge(2, new Edge(2, 1, NULL));
	g->insertEdge(2, new Edge(2, 3, NULL));
	g->insertEdge(3, new Edge(3, 1, NULL));
	g->insertEdge(3, new Edge(3, 2, NULL));
	g->insertEdge(3, new Edge(3, 4, NULL));
	g->insertEdge(4, new Edge(4, 1, NULL));
	g->insertEdge(4, new Edge(4, 3, NULL));
	g->insertEdge(4, new Edge(4, 5, NULL));
	g->insertEdge(4, new Edge(4, 6, NULL));
	g->insertEdge(5, new Edge(5, 4, NULL));
	g->insertEdge(5, new Edge(5, 6, NULL));
	g->insertEdge(5, new Edge(5, 7, NULL));
	g->insertEdge(5, new Edge(5, 8, NULL));
	g->insertEdge(6, new Edge(6, 4, NULL));
	g->insertEdge(6, new Edge(6, 5, NULL));
	g->insertEdge(6, new Edge(6, 7, NULL));
	g->insertEdge(6, new Edge(6, 8, NULL));
	g->insertEdge(7, new Edge(7, 5, NULL));
	g->insertEdge(7, new Edge(7, 6, NULL));
	g->insertEdge(7, new Edge(7, 8, NULL));
	g->insertEdge(7, new Edge(7, 9, NULL));
	g->insertEdge(8, new Edge(8, 5, NULL));
	g->insertEdge(8, new Edge(8, 6, NULL));
	g->insertEdge(8, new Edge(8, 7, NULL));
	g->insertEdge(9, new Edge(9, 7, NULL));
	cout << "Constructed example graph" << endl;

	Communities *comm = girvanNewman(10, g);

	comm->print();

	List *comList = comm->getCommunitiesList();
	assert(comList->getSize() == 3);

	CommunityListItem *cli = (CommunityListItem*) comList->getHead();
	Community *com1 = cli->getCommunity();
	Community *com2 = cli->getNext()->getCommunity();
	Community *com3 = cli->getNext()->getNext()->getCommunity();

	List *comMem1 = com1->getCommunityMembers();
	assert(comMem1->getSize() == 4);
	List *comMem2 = com2->getCommunityMembers();
	assert(comMem2->getSize() == 4);
	List *comMem3 = com3->getCommunityMembers();
	assert(comMem3->getSize() == 1);

	IntegerListItem *ili1 = (IntegerListItem*) comMem1->getHead();
	assert(ili1->getInt() == 2);
	assert(ili1->getNext()->getInt() == 1);
	assert(ili1->getNext()->getNext()->getInt() == 3);
	assert(ili1->getNext()->getNext()->getNext()->getInt() == 4);
	IntegerListItem *ili2 = (IntegerListItem*) comMem2->getHead();
	assert(ili2->getInt() == 6);
	assert(ili2->getNext()->getInt() == 5);
	assert(ili2->getNext()->getNext()->getInt() == 7);
	assert(ili2->getNext()->getNext()->getNext()->getInt() == 8);
	IntegerListItem *ili3 = (IntegerListItem*) comMem3->getHead();
	assert(ili3->getInt() == 9);

	delete comm;
	delete g;
}
