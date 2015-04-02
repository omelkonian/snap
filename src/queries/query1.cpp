/*
 * query1.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: Orestis Melkonian
 */

#include "queries.h"
#include "../project_main/GraphLib.h"
#include "MatchesList.h"
#include "Match.h"
#include "Matches.h"
#include "../list/EdgeListItem.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Matches* matchSuggestion(Node *n, int k, int h, int x, int limit, Graph *g) {
	const int data_size = DATA_SIZE; // Needed to ensure IDs do not have conflicts.

	/**
	 *  ======================================================
	 * 		A. Create Graphs from .csv files.
	 * 	======================================================
	 */

	// Create person_isLocatedIn_place graph.
	Graph *person_isLocatedIn_place = new Graph(5, 10);
	if (!person_isLocatedIn_place) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	{
		string line, line1, line2;

		const char *filename = "queries/dataset/person_isLocatedIn_place.csv";
		ifstream myfile(filename);

		if (myfile.fail()) {
			cout << "ERROR: Unable to open " << filename << endl;
			delete person_isLocatedIn_place;
			return NULL;
		}

		getline(myfile, line1);
		while (getline(myfile, line)) {
			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|");
			// Get Person.ID
			stringstream s_str(p);
			int personID;
			s_str >> personID;
			person_isLocatedIn_place->insertNode(new Node(personID, NULL));

			p = strtok(NULL, " ");

			// Get Place.ID
			stringstream s_str2(p);
			int placeID;
			s_str2 >> placeID;
			placeID += data_size;

			if (person_isLocatedIn_place->lookupNode(placeID) == NULL)
				person_isLocatedIn_place->insertNode(new Node(placeID, NULL));

			// Create Edge: Person -> Place
			Edge *edge = new Edge(personID, placeID, NULL);
			if (!edge) {
				cout << "ERROR: Unable to allocate memory." << endl;
				delete person_isLocatedIn_place;
				return NULL;
			}
			person_isLocatedIn_place->insertEdge(personID, edge);
		}
		myfile.close();
	}

//	cout << "=============================================" << endl;
//	cout << "Created person_isLocatedIn_place graph. (" << person_isLocatedIn_place->getNodeNo() << ")" << endl;
//	cout << "=============================================" << endl;

	// Create person_works/studiesAt_organisation graph.
	Graph *person_works_studiesAt_organisation = new Graph(5, 10);
	if (!person_works_studiesAt_organisation) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_isLocatedIn_place;
		return NULL;
	}
	{
		string line, line1, line2;

		const char *filename = "queries/dataset/person_workAt_organisation.csv";
		ifstream myfile(filename);
		if (myfile.fail()) {
			cout << "ERROR: Unable to open " << filename << endl;
			delete person_isLocatedIn_place;
			delete person_works_studiesAt_organisation;
			return NULL;
		}

		getline(myfile, line1);
		while (getline(myfile, line)) {
			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|");
			// Get Person.ID
			stringstream s_str(p);
			int personID;
			s_str >> personID;
			if (person_works_studiesAt_organisation->lookupNode(personID) == NULL)
				person_works_studiesAt_organisation->insertNode(new Node(personID, NULL));

			p = strtok(NULL, " ");

			// Get Organisation.ID
			stringstream s_str2(p);
			int organisationID;
			s_str2 >> organisationID;
			organisationID += data_size;

			if (person_works_studiesAt_organisation->lookupNode(organisationID) == NULL)
				person_works_studiesAt_organisation->insertNode(new Node(organisationID, NULL));

			// Create Edge: Person -> Place
			Edge *edge = new Edge(personID, organisationID, NULL);
			person_works_studiesAt_organisation->insertEdge(personID, edge);
			Edge *edge2 = new Edge(organisationID, personID, NULL);
			person_works_studiesAt_organisation->insertEdge(organisationID, edge2);
			if (!edge || !edge2) {
				cout << "ERROR: Unable to allocate memory." << endl;
				delete person_isLocatedIn_place;
				delete person_works_studiesAt_organisation;
				return NULL;
			}
		}
		myfile.close();

		const char *filename2 = "queries/dataset/person_studyAt_organisation.csv";
		ifstream myfile2(filename2);
		if (myfile2.fail()) {
			cout << "ERROR: Unable to open " << filename2 << endl;
			delete person_isLocatedIn_place;
			delete person_works_studiesAt_organisation;
			return NULL;
		}

		getline(myfile2, line1);
		while (getline(myfile2, line)) {
			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|");
			// Get Person.ID
			stringstream s_str(p);
			int personID;
			s_str >> personID;
			if (person_works_studiesAt_organisation->lookupNode(personID) == NULL)
				person_works_studiesAt_organisation->insertNode(new Node(personID, NULL));

			p = strtok(NULL, " ");

			// Get Organisation.ID
			stringstream s_str2(p);
			int organisationID;
			s_str2 >> organisationID;
			organisationID += data_size;

			if (person_works_studiesAt_organisation->lookupNode(organisationID) == NULL)
				person_works_studiesAt_organisation->insertNode(new Node(organisationID, NULL));

			// Create Edge: Person -> Place
			Edge *edge = new Edge(personID, organisationID, NULL);
			person_works_studiesAt_organisation->insertEdge(personID, edge);
		}
		myfile.close();

//		cout << "=============================================" << endl;
//		cout << "Created person_study/workAt_organisation graph. (" << person_works_studiesAt_organisation->getNodeNo() << ")" << endl;
//		cout << "=============================================" << endl;
	}

	// Create person_hasInterest_tag graph.
	Graph *person_hasInterest_tag = new Graph(5, 10);
	if (!person_hasInterest_tag) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_isLocatedIn_place;
		delete person_works_studiesAt_organisation;
		return NULL;
	}
	{
		string line, line1, line2;
		const char *filename = "queries/dataset/person_hasInterest_tag.csv";
		ifstream myfile(filename);
		if (myfile.fail()) {
			cout << "ERROR: Unable to open " << filename << endl;
			delete person_isLocatedIn_place;
			delete person_works_studiesAt_organisation;
			delete person_hasInterest_tag;
			return NULL;
		}

		getline(myfile, line1);
		while (getline(myfile, line)) {
			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|");
			// Get Person.ID
			stringstream s_str(p);
			int personID;
			s_str >> personID;
			if (person_hasInterest_tag->lookupNode(personID) == NULL)
				person_hasInterest_tag->insertNode(new Node(personID, NULL));

			p = strtok(NULL, " ");

			// Get Place.ID
			stringstream s_str2(p);
			int tagID;
			s_str2 >> tagID;
			tagID += data_size;

			if (person_hasInterest_tag->lookupNode(tagID) == NULL)
				person_hasInterest_tag->insertNode(new Node(tagID, NULL));

			// Create Edge: Person -> Place
			Edge *edge = new Edge(personID, tagID, NULL);
			if (!edge) {
				cout << "ERROR: Unable to allocate memory." << endl;
				delete person_isLocatedIn_place;
				delete person_works_studiesAt_organisation;
				delete person_hasInterest_tag;
				return NULL;
			}
			person_hasInterest_tag->insertEdge(personID, edge);
		}
		myfile.close();

//		cout << "=============================================" << endl;
//		cout << "Created person_hasInterest_tag graph. (" << person_hasInterest_tag->getNodeNo() << ")" << endl;
//		cout << "=============================================" << endl;
	}

	/**
	 *  ======================================================
	 * 		B. Find all Matches.
	 * 	======================================================
	 */
	MatchesList *matchesList = new MatchesList();
	if (!matchesList) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_isLocatedIn_place;
		delete person_works_studiesAt_organisation;
		delete person_hasInterest_tag;
		return NULL;
	}
	ResultSet *res = reachNodeN(n->getId(), g);
	Pair *pair;

	// Find place of node.
	BucketItem *found = person_isLocatedIn_place->lookupItem(n->getId());
	EdgeListItem *head = (found) ? ((EdgeListItem*) (found->getEdgeList()->getHead())) : (NULL);
	int placeID1 = (head && found) ? (head->getElement()->getEndNodeId()) : (-1);

	// Find organisation of node.
	List *orgIDs1 = new List();
	if (!orgIDs1) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_isLocatedIn_place;
		delete person_works_studiesAt_organisation;
		delete person_hasInterest_tag;
		delete matchesList;
		return NULL;
	}
	found = person_works_studiesAt_organisation->lookupItem(n->getId());
	head = (found) ? ((EdgeListItem*) (found->getEdgeList()->getHead())) : (NULL);
	while (head != NULL) {
		orgIDs1->insertItem(new IntegerListItem(head->getElement()->getEndNodeId()));
		head = (EdgeListItem*) head->getNext();
	}


	//Find interests of node.
	List *tags1 = new List();
	if (!tags1) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_isLocatedIn_place;
		delete person_works_studiesAt_organisation;
		delete person_hasInterest_tag;
		delete matchesList;
		delete orgIDs1;
		return NULL;
	}
	BucketItem *bi1 = person_hasInterest_tag->lookupItem(n->getId());
	EdgeListItem *cur = (EdgeListItem*) bi1->getEdgeList()->getHead();
	while (cur != NULL) {
		tags1->insertItem(new IntegerListItem(cur->getElement()->getEndNodeId()));
		cur = (EdgeListItem*) cur->getNext();
	}

	while ((pair = res->next()) != NULL) {
		if (pair->getDistance() > h)
			break;

		Node *temp = g->lookupNode(pair->getNodeId());
		assert(temp != NULL);

		// Different gender?
		if (strcmp(temp->getProperties()->getStringProperty(2), n->getProperties()->getStringProperty(2)) == 0)
			continue;

		// At most x age difference?
		char age1[5];
		strncpy(age1, n->getProperties()->getStringProperty(3), 4);
		age1[4] = '\0';
		char age2[5];
		strncpy(age2, temp->getProperties()->getStringProperty(3), 4);
		age2[4] = '\0';

		stringstream s_str(age1);
		stringstream s_str2(age2);
		int ageAsInt1, ageAsInt2;
		s_str >> ageAsInt1;
		s_str2 >> ageAsInt2;

		if (abs(ageAsInt1 - ageAsInt2) > x)
			continue;

		// Located in the same place or works/studies at the same organisation?
		found = person_isLocatedIn_place->lookupItem(temp->getId());
		head = (found) ? ((EdgeListItem*) (found->getEdgeList()->getHead())) : (NULL);
		int placeID2 = (head) ? (head->getElement()->getEndNodeId()) : (-1);

		bool samePlace = (placeID1 == -1 || placeID2 == -1) ? (false) : (placeID1 == placeID2);

		List *orgIDs2 = new List();
		if (!orgIDs2) {
			cout << "ERROR: Unable to allocate memory." << endl;
			delete person_isLocatedIn_place;
			delete person_works_studiesAt_organisation;
			delete person_isLocatedIn_place;
			delete matchesList;
			delete orgIDs1;
			delete tags1;
			return NULL;
		}
		found = person_works_studiesAt_organisation->lookupItem(temp->getId());
		head = (found) ? ((EdgeListItem*) (found->getEdgeList()->getHead())) : (NULL);
		while (head != NULL) {
			orgIDs2->insertItem(new IntegerListItem(head->getElement()->getEndNodeId()));
			head = (EdgeListItem*) head->getNext();
		}

		bool sameOrg = false;
		IntegerListItem *cur1 = (IntegerListItem*) orgIDs2->getHead();
		while (cur1 != NULL) {
			IntegerListItem *cur2 = (IntegerListItem*) orgIDs1->getHead();
			while (cur2 != NULL) {
				if (cur1->getInt() == cur2->getInt()) {
					sameOrg = true;
					break;
				}
				cur2 = (IntegerListItem*) cur2->getNext();
			}
			cur1 = (sameOrg) ? (NULL) : ((IntegerListItem*) cur1->getNext());
		}
		delete orgIDs2;

		if (!(samePlace || sameOrg))
			continue;

		// At least k common interests?
		List *tags2 = new List();
		if (!tags2) {
			cout << "ERROR: Unable to allocate memory." << endl;
			delete person_isLocatedIn_place;
			delete person_works_studiesAt_organisation;
			delete person_hasInterest_tag;
			delete matchesList;
			delete orgIDs1;
			delete tags1;
			return NULL;
		}
		BucketItem *bi2 = person_hasInterest_tag->lookupItem(temp->getId());

		cur = (EdgeListItem*) bi2->getEdgeList()->getHead();
		while (cur != NULL) {
			tags2->insertItem(new IntegerListItem(cur->getElement()->getEndNodeId()));
			cur = (EdgeListItem*) cur->getNext();
		}

		int counter = 0;
		IntegerListItem *ili = (IntegerListItem*) tags1->getHead();
		while (ili != NULL) {
			IntegerListItem *ili2 = (IntegerListItem*) tags2->getHead();
			while (ili2 != NULL) {
				if (ili2->getInt() == ili->getInt()) {
					counter++;
					break;
				}
				ili2 = ili2->getNext();
			}
			ili = ili->getNext();
		}

		if (counter < k)
			continue;

		// Calculate Jaccard.
		double jaccardDistance;

		if (tags1->getSize() + tags2->getSize() - counter == 0)
			jaccardDistance = 1;
		else
			jaccardDistance = (double) (((double) counter) / (double) (tags1->getSize() + tags2->getSize() - counter));
		delete tags2;

		// Add to Matches List.
		Match *match = new Match(temp->getId(), jaccardDistance);
		if (!match) {
			cout << "ERROR: Unable to allocate memory." << endl;
			delete person_isLocatedIn_place;
			delete person_works_studiesAt_organisation;
			delete person_hasInterest_tag;
			delete matchesList;
			delete orgIDs1;
			delete tags1;
			return NULL;
		}
		matchesList->insertMatch(match);
	}
	delete orgIDs1;
	delete tags1;
	delete res;
//	cout << "=============================================" << endl;
//	cout << "               Found all matches (" << matchesList->getSize() << ")" << endl;
//	cout << "=============================================" << endl;

	/**
	 *  ======================================================
	 * 		C. Return top <limit> Matches.
	 * 	======================================================
	 */
	Matches *matches = new Matches(limit);
	if (!matches) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_isLocatedIn_place;
		delete person_works_studiesAt_organisation;
		delete person_hasInterest_tag;
		delete matchesList;
		return NULL;
	}
	for (int i = 0; i < limit; i++) {
		if (matchesList->getSize() == 0)
			break;
		else {
			matches->getTopMatches()[i] = matchesList->removeHead();
			matches->incrementSize();
		}
	}

	delete matchesList;
	delete person_isLocatedIn_place;
	delete person_works_studiesAt_organisation;
	delete person_hasInterest_tag;

	return matches;
}

