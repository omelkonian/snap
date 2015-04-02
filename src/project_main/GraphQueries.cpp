#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GraphQueries.h"
#include "defines.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/* Creates a graph based on schema's relation person_knows_person
 * bucketsNumber: size of hashtable
 * bucketSize: size of cells in a bucket
 * loads also from data file as attributes anything might be useful
 * mustn't save any query/metric estimation
 * return value: the loaded graph*/
Graph* loadGraph(int bucketsNumber, int bucketSize) {

	Graph *graph = new Graph(bucketsNumber, bucketSize);
	if (!graph) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	char* file = "queries/dataset/person_knows_person.csv";
	char* attributesfile = "queries/dataset/person.csv";
	{
		string line;
		string line1;

		ifstream myfile(file);
		if (myfile.fail()) {
			cout << "ERROR: Unable to open " << file << endl;
			delete graph;
			return NULL;
		}

		getline(myfile, line1);
		while (getline(myfile, line)) {
			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|");

			if (!p) continue;

			// Get the first ID
			stringstream s_str(p);

			int ID1;
			s_str >> ID1;

			if (graph->lookupNode(ID1) == NULL)
				graph->insertNode(new Node(ID1, NULL));

			p = strtok(NULL, " ");
			// Get the second ID
			stringstream s_str2(p);

			int ID2;
			s_str2 >> ID2;

			if (graph->lookupNode(ID2) == NULL)
				graph->insertNode(new Node(ID2, NULL));

			Properties* properties = new Properties(1);
			properties->setStringProperty("knows", 0);

			// Create Edge between IDs
			Edge *edge = new Edge(ID1, ID2, properties);
			if (!edge) {
				cout << "ERROR: Unable to allocate memory." << endl;
				return NULL;
			}
			bool alreadyAdded = false; // Check if we have already inserted edge.
			EdgeListItem *eli = (EdgeListItem*) graph->lookupItem(ID1)->getEdgeList()->getHead();
			while (eli) {
				if (eli->getElement()->getEndNodeId() == ID2)
					alreadyAdded = true;
				eli = eli->getNext();
			}
			if (!alreadyAdded)
				graph->insertEdge(ID1, edge);
		}
		myfile.close();

		string line2, line3;

		ifstream attfile(attributesfile);
		if (attfile.fail()) {
			cout << "ERROR: Unable to open " << attributesfile << endl;
			delete graph;
			return NULL;
		}
		int numberOfAttributes = 4;		//firstName|lastName|gender|birthday
		getline(attfile, line2);

		while (getline(attfile, line3)) {
			char* myString = (char *) line3.c_str();

			Properties* properties = new Properties(numberOfAttributes);
			if (!properties) {
				cout << "ERROR: Unable to allocate memory." << endl;
				return NULL;
			}

			char *pch = strtok(myString, "|");
			// Get the ID in order to insert the attributes
			stringstream s_str(pch);
			int nodeId;
			s_str >> nodeId;
			BucketItem* bucketItem = graph->getHashTable()->Lookup(nodeId);
			if (bucketItem == NULL) {
				delete properties;
				continue;
			}
			Node* node = bucketItem->getNode();

			for (int i = 0; i < numberOfAttributes; i++) {
				pch = strtok(NULL, "|");
				if (!pch || (strlen(pch) <= 1)) {
					properties = NULL;
					break;
				}
				char attribute[MAX_WORD];
				strcpy(attribute, pch);
				properties->setStringProperty(attribute, i);

			}
			node->setProperties(properties);
		}
		attfile.close();
	}
//	cout << "=============================================" << endl;
//	cout << "Created person_knows_person graph. (" << graph->getNodeNo() << ")" << endl;
//	cout << "=============================================" << endl;
	return graph;
}

/* Get the matches structure from query 1, the requested
 * pair number and returns the person
 * id. If there is no <pairNumber> result return -1
 */
int getMatch(int pairNumber, Matches* match) {
	return ((pairNumber > match->getSize()) ? (-1) : (match->getTopMatches()[pairNumber]->getID()));
}

/* Gets the stalker structure from query 2, a
 * position and returns the stalker's person id
 * at current position. If there is no <position> result return -1
 */
int getStalkerID(int position, Stalkers* stalk) {
	return ((position > stalk->getSize()) ? (-1) : (stalk->getTopStalkers()[position].getID()));
}
