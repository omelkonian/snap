/*
 * query2.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: Orestis Melkonian
 */

#include "queries.h"
#include "../project_main/GraphLib.h"
#include "StalkerList.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../graph_metrics/metrics.h"

using namespace std;

Graph* getTopStalkers(int k, int x, int centralityMode, Graph *g, Stalkers *st) {
	cout << "-------------------STALKER QUERY----------------------" << endl;
	const int data_size = DATA_SIZE; // Needed to ensure IDs do not have conflicts.

	/**
	 *  ======================================================
	 * 		A. Create Graphs from .csv files.
	 * 	======================================================
	 */

	int personNo = 0, postNo = 0;
	// Create person_post graph.
	Graph *person_post = new Graph(5, 10);
	if (!person_post) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	{
		string line, line1, line2;

		const char *filename = "queries/dataset/person_likes_post.csv";
		ifstream myfile(filename);
		if (myfile.fail()) {
			cout << "ERROR: Unable to open " << filename << endl;
			delete person_post;
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
			if (person_post->lookupNode(personID) == NULL) {
				personNo++;
				person_post->insertNode(new Node(personID, NULL));
			}

			p = strtok(NULL, " ");

			// Get Place.ID
			stringstream s_str2(p);
			int postID;
			s_str2 >> postID;
			postID += data_size;

			if (person_post->lookupNode(postID) == NULL) {
				postNo++;
				person_post->insertNode(new Node(postID, NULL));
			}

			// Create Edge: Person -> Post
			Properties *prop = new Properties(1);
			prop->setStringProperty("likes", 0);

			Edge *edge = new Edge(personID, postID, prop);
			if (!prop || !edge) {
				cout << "ERROR: Unable to allocate memory." << endl;
				delete person_post;
				return NULL;
			}
			person_post->insertEdge(personID, edge);
		}
		myfile.close();
	}
//	cout << "=============================================" << endl;
//	cout << "Created person_post graph. (" << person_post->getNodeNo() << ")" << endl;
//	cout << "PersonNo: " << personNo << " PostNo: " << postNo << endl;
//	cout << "=============================================" << endl;

	// Update person_post graph.
	{
		string line, line1, line2;

		const char *filename = "queries/dataset/post_hasCreator_person.csv";
		ifstream myfile(filename);
		if (myfile.fail()) {
			cout << "ERROR: Unable to open " << filename << endl;
			delete person_post;
			return NULL;
		}

		getline(myfile, line1);
		while (getline(myfile, line)) {
			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|");
			// Get Post.ID
			stringstream s_str(p);
			int postID;
			s_str >> postID;
			postID += data_size;
			if (person_post->lookupNode(postID) == NULL) {
				postNo++;
				person_post->insertNode(new Node(postID, NULL));
			}

			p = strtok(NULL, " ");

			// Get Person.ID
			stringstream s_str2(p);
			int personID;
			s_str2 >> personID;
			if (person_post->lookupNode(personID) == NULL) {
				personNo++;
				person_post->insertNode(new Node(personID, NULL));
			}

			// Create Edge: Post -> Person
			Properties *prop = new Properties(1);
			prop->setStringProperty("hasCreator", 0);

			Edge *edge = new Edge(postID, personID, prop);
			if (!prop || !edge) {
				cout << "ERROR: Unable to allocate memory." << endl;
				delete person_post;
				return NULL;
			}
			person_post->insertEdge(postID, edge);
		}
		myfile.close();
	}
//	cout << "=============================================" << endl;
//	cout << "Updated person_post graph. (" << person_post->getNodeNo() << ")" << endl;
//	cout << "PersonNo: " << personNo << " PostNo: " << postNo << endl;
//	cout << "=============================================" << endl;

	// Create forum_hasMember_person graph. (in fact, person_isMemberOf_forum)
	Graph *person_isMemberOf_forum = new Graph(5, 10);
	if (!person_isMemberOf_forum) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_post;
		return NULL;
	}
	{
		string line, line1, line2;

		const char *filename = "queries/dataset/forum_hasMember_person.csv";
		ifstream myfile(filename);
		if (myfile.fail()) {
			cout << "ERROR: Unable to open " << filename << endl;
			delete person_post;
			delete person_isMemberOf_forum;
			return NULL;
		}

		getline(myfile, line1);
		while (getline(myfile, line)) {
			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|");
			// Get Forum.ID
			stringstream s_str(p);
			int forumID;
			s_str >> forumID;
			forumID += data_size;
			if (person_isMemberOf_forum->lookupNode(forumID) == NULL)
				person_isMemberOf_forum->insertNode(new Node(forumID, NULL));

			p = strtok(NULL, " ");

			// Get Person.ID
			stringstream s_str2(p);
			int personID;
			s_str2 >> personID;
			if (person_isMemberOf_forum->lookupNode(personID) == NULL)
				person_isMemberOf_forum->insertNode(new Node(personID, NULL));

			// Create Edge: Person -> Forum
			Edge *edge = new Edge(personID, forumID, NULL);
			if (!edge) {
				cout << "ERROR: Unable to allocate memory." << endl;
				delete person_post;
				delete person_isMemberOf_forum;
				return NULL;
			}
			person_isMemberOf_forum->insertEdge(personID, edge);
		}
		myfile.close();
	}
//	cout << "=============================================" << endl;
//	cout << "Created person_isMemberOf_forum graph. (" << person_isMemberOf_forum->getNodeNo() << ")" << endl;
//	cout << "=============================================" << endl;

	/**
	 *  ======================================================
	 * 		B. Find all Stalkers.
	 * 	======================================================
	 */

	StalkerList *stalkers = new StalkerList();
	if (!stalkers) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_post;
		delete person_isMemberOf_forum;
		return NULL;
	}

	// Traverse all people in person_post graph.
	for (int i = 1; i < data_size; i++) {
		BucketItem *found = person_post->lookupItem(i);
		if (!found)
			continue;

		Node *stalker = found->getNode();
		int stalkerId = i;

		// Check if person is Stalker
		int likes[data_size];
		for (int k = 0; k < data_size; k++) {
			likes[k] = 0;
		}

		// Count all likes.
		List *edges = found->getEdgeList();

		if (edges->getSize() < x)  // Total number of likes should be at least x.
			continue;

		EdgeListItem *cur = (EdgeListItem*) edges->getHead();
		while (cur != NULL) {
			// Get post that person liked.
			int postId = cur->getElement()->getEndNodeId();

			// Get creator of post.
			BucketItem *found = person_post->lookupItem(postId);
			EdgeListItem *head = (EdgeListItem*) found->getEdgeList()->getHead();
			int creatorId = (head && !strcmp(head->getElement()->getProperties()->getStringProperty(0), "hasCreator")) ? (head->getElement()->getEndNodeId()) : (-1);
			likes[creatorId]++;

			cur = cur->getNext();
		}

		// Check if he liked someone's post more than x times, whom he doesn't know.
		for (int k = 1; k < data_size; k++) {
			if (likes[k] > x) {
				if (!(found->knows(k)) && !(g->lookupItem(k)->knows(stalkerId))) {
					// Calculate stalker's centrality score.
					double centralityScore;
					if (centralityMode == 1)
						centralityScore = closenessCentrality(stalker, g);
					else if (centralityMode == 2)
						centralityScore = betweennessCentrality(stalker, g);
					else {
						cout << "ERROR: Invalid centrality mode in stalker query." << endl;
						delete person_post;
						delete person_isMemberOf_forum;
						delete stalkers;
						return NULL;
					}
					// Insert into sorted StalkersList.
					Stalker *st = new Stalker(stalkerId, centralityScore);
					if (!st) {
						cout << "ERROR: Unable to allocate memory." << endl;
						delete person_post;
						delete person_isMemberOf_forum;
						delete stalkers;
						return NULL;
					}
					stalkers->insertStalker(st);
					break;
				}
			}
		}
	}

//	cout << "==========================================" << endl;
//	cout << "         Found all Stalkers! (" << stalkers->getSize() << ")" << endl;
//	cout << "==========================================" << endl;

	/**
	 *  ======================================================
	 * 		C. Return top <k> Stalkers.
	 * 	======================================================
	 */
	for (int i = 0; i < k; i++) {
		st->getTopStalkers()[i] = *stalkers->removeHead();
		st->incrementSize();
		if (stalkers->getSize() == 0)
			break;
	}

	/**
	 *  ======================================================
	 * 		D. Construct person_forum stalker graph.
	 * 	======================================================
	 */
	Graph *ret = new Graph(2, 3);
	if (!ret) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete person_post;
		delete person_isMemberOf_forum;
		delete stalkers;
		return NULL;
	}

	for (int i = 0; i < st->getSize(); i++) {
		int stalkerId = st->getTopStalkers()[i].getID();

		// Get forums that this stalker is member of.
		List *forumIDs = new List();
		if (!forumIDs) {
			cout << "ERROR: Unable to allocate memory." << endl;
			delete person_post;
			delete person_isMemberOf_forum;
			delete stalkers;
			return NULL;
		}
		EdgeListItem *cur = (EdgeListItem*) person_isMemberOf_forum->lookupItem(stalkerId)->getEdgeList()->getHead();
		while (cur != NULL) {
			forumIDs->insertItem(new IntegerListItem(cur->getElement()->getEndNodeId()));
			cur = cur->getNext();
		}
		// Insert forumIDs to person node's properties.
		Properties *prop = new Properties(forumIDs->getSize());
		if (!prop) {
			cout << "ERROR: Unable to allocate memory." << endl;
			delete person_post;
			delete person_isMemberOf_forum;
			delete stalkers;
			delete ret;
			return NULL;
		}
		IntegerListItem *curr = (IntegerListItem*) forumIDs->getHead();
		int index = 0;
		while (curr != NULL) {
			prop->setIntegerProperty(curr->getInt(), index++);
			curr = curr->getNext();
		}

		ret->insertNode(new Node(stalkerId, prop));

		/* If the newly added stalker knows any of the pre-inserted ones,
		 insert the edges between them. */
		List *neighbors = g->lookupItem(stalkerId)->getEdgeList();
		cur = (EdgeListItem*) neighbors->getHead();
		while (cur != NULL) {
			int stalkerId2 = cur->getElement()->getEndNodeId();
			if (ret->lookupItem(stalkerId2) != NULL) {
				Properties *prop = new Properties(1);
				if (!prop) {
					cout << "ERROR: Unable to allocate memory." << endl;
					delete person_post;
					delete person_isMemberOf_forum;
					delete stalkers;
					delete ret;
					return NULL;
				}
				prop->setStringProperty("knows", 0);
				Edge *edge = new Edge(stalkerId, stalkerId2, prop);
				ret->insertEdge(stalkerId, edge);
				prop = new Properties(1);
				if (!prop) {
					cout << "ERROR: Unable to allocate memory." << endl;
					delete person_post;
					delete person_isMemberOf_forum;
					delete stalkers;
					delete ret;
					return NULL;
				}
				prop->setStringProperty("knows", 0);
				edge = new Edge(stalkerId2, stalkerId, prop);
				ret->insertEdge(stalkerId2, edge);
			}
			cur = cur->getNext();
		}
	}

	delete stalkers;
	delete person_post;
	delete person_isMemberOf_forum;

	return ret;
}

