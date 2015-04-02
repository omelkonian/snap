/*
 * communities.cpp
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#include "_communities.h"

#include <pthread.h>
#include "forum/ForumList.h"
#include "../list/GraphListItem.h"
#include "../list/IntegerListItem.h"
#include "../Edge.h"
#include "../project_main/GraphQueries.h"

#include "Communities.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../list/ForumListItem.h"
#include "../list/ThreadListItem.h"
#include "../list/CommunityListItem.h"

using namespace std;

// Initialize lists shared across threads.
ForumList *topForums;
Graph *forums;
pthread_mutex_t mutex;
pthread_mutex_t mutex2;
Graph *personGraph;
Graph **graphs;
int graphCounter = 0;

void* findForumSize(void *argument);
void* createForum(void *argument);

Graph** getTopNForums(int n) {

	/*
	 * Find top-N forumIDs.
	 */
	if (pthread_mutex_init(&mutex, NULL)) {
		cout << "ERROR: Unable to initialize mutex." << endl;
		return NULL;
	}
	List *forumIDs = new List();
	forums = new Graph(5, 10);
	topForums = new ForumList(n);
	if (!forumIDs || !forums || !topForums) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}

	// Open forum.csv.
	string line, line1, line2;
	const char *filename = "queries/dataset/forum_hasMember_person.csv";
	ifstream myfile(filename);

	if (myfile.fail()) {
		cout << "ERROR: Unable to open " << filename << endl;
		delete forumIDs;
		delete forums;
		delete topForums;
		pthread_mutex_destroy(&mutex);
		return NULL;
	}

	getline(myfile, line1);
	while (getline(myfile, line)) {
		char *myString = (char*) line.c_str();
		char *p = strtok(myString, "|");
		stringstream s_str(p);
		int forumID;
		s_str >> forumID;
		if (forums->lookupItem(forumID) == NULL) {
			forumIDs->insertItem(new IntegerListItem(forumID));
			forums->insertNode(new Node(forumID, NULL));
		}

		p = strtok(NULL, " ");

		stringstream s_str2(p);
		int personID;
		s_str2 >> personID;
		forums->insertEdge(forumID, new Edge(forumID, personID, NULL));
	}
	myfile.close();

//	cout << "Read all forumIDs (" << forumIDs->getSize() << ")" << endl;

	// Start #forum threads.
	pthread_t threadIDs[MAX_THREADS];
	int forumSizeIDs[MAX_THREADS];

	IntegerListItem *cur = (IntegerListItem*) forumIDs->getHead();
	int counter = 0;
	while (cur) {
		forumSizeIDs[counter] = cur->getInt();
		if (pthread_create(&threadIDs[counter], NULL, findForumSize, &forumSizeIDs[counter])) {
			cout << "ERROR: Thread " << counter << " could not be created."
					<< endl;
			delete forumIDs;
			delete forums;
			delete topForums;
			pthread_mutex_destroy(&mutex);
			return NULL;
		}
		counter++;

		if (counter == MAX_THREADS) {
			// Join threads.
			for (int i = 0; i < counter; i++) {
				if (pthread_join(threadIDs[i], NULL)) {
					cout << "Thread " << counter
							<< " could not be joined with main thread." << endl;
					delete forumIDs;
					delete forums;
					delete topForums;
					pthread_mutex_destroy(&mutex);
					return NULL;
				}
			}
			counter = 0;
		}
		cur = cur->getNext();
	}
//	cout << "Started all threads." << endl;

	// Join remaining threads.
	for (int i = 0; i < counter; i++) {
		if (pthread_join(threadIDs[i], NULL)) {
			cout << "Thread " << counter
					<< " could not be joined with main thread." << endl;
			delete forumIDs;
			delete forums;
			delete topForums;
			pthread_mutex_destroy(&mutex);
			return NULL;
		}
	}

//	cout << "All threads finished!" << endl;


	/**
	 * Construct N graphs.
	 */
	if (pthread_mutex_init(&mutex2, NULL)) {
		cout << "ERROR: Unable to initialize mutex." << endl;
		return NULL;
	}
	graphs = (Graph**) malloc(n * sizeof(Graph*));
	if (!graphs) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}
	personGraph = loadGraph(5, 10);

	pthread_t threadIDs2[topForums->getSize()];
	int forumIds[topForums->getSize()];

	counter = 0;
	ForumListItem *fli = (ForumListItem*) topForums->getHead();
	while (fli) {
		forumIds[counter] = fli->getForum()->getForumID();
		if (pthread_create(&threadIDs2[counter], NULL, createForum,
				&forumIds[counter])) {
			cout << "ERROR: Thread " << counter << " could not be created."
					<< endl;
			delete forumIDs;
			delete forums;
			delete topForums;
			pthread_mutex_destroy(&mutex);
			pthread_mutex_destroy(&mutex2);
			delete graphs;
			delete personGraph;
			return NULL;
		}
		counter++;
		fli = fli->getNext();
	}
//	cout << "Started all graph threads." << endl;

	assert(counter == topForums->getSize());

	for (int i = 0; i < counter; i++) {
		if (pthread_join(threadIDs2[i], NULL)) {
			cout << "ERROR: Thread " << i
					<< " could not be joined with main thread." << endl;
			delete forumIDs;
			delete forums;
			pthread_mutex_destroy(&mutex);
			pthread_mutex_destroy(&mutex2);
			delete graphs;
			delete personGraph;
			return NULL;
		}
	}

//	cout << "All graph threads finished!" << endl;

	delete forumIDs;
	delete forums;
	delete topForums;
	delete personGraph;
	pthread_mutex_destroy(&mutex);

	return graphs;
}

void* findForumSize(void *argument) {
	int forumID = *((int*) argument);
	int forumSize = forums->lookupItem(forumID)->getEdgeList()->getSize();

	// Insert into shared list topForums (CRITICAL SECTION).
	if (pthread_mutex_lock(&mutex))
		cout << "ERROR: Unable to lock mutex." << endl;
	else {
		topForums->insertForum(new Forum(forumID, forumSize));
		topForums->update();
		if (pthread_mutex_unlock(&mutex))
			cout << "ERROR: Unable to unlock mutex." << endl;
	}

	pthread_exit(NULL);
	return NULL;
}

void* createForum(void *argument) {
	int forumID = *((int*) argument);
	stringstream strs;
	strs << forumID;
	string str = strs.str();
	string f("Forum");
	string name = f.append(str);

	Graph *graph = new Graph(5, 10, name);
	if (!graph) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return NULL;
	}

	// Initialize graph with people in the forum.
	EdgeListItem *eli =
			(EdgeListItem*) forums->lookupItem(forumID)->getEdgeList()->getHead();
	while (eli) {
		if (!graph->lookupNode(eli->getElement()->getEndNodeId()))
			graph->insertNode(new Node(eli->getElement()->getEndNodeId(), NULL));
		eli = eli->getNext();
	}

	List *allIDs = graph->getAllIDs();
	IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
	while (ili) {
		int id1 = ili->getInt();
		IntegerListItem *ili2 = (IntegerListItem*) allIDs->getHead();
		while (ili2) {
			int id2 = ili2->getInt();
			if (personGraph->reachNode1(id1, id2) == 1) {
				graph->insertEdge(id1, new Edge(id1, id2, NULL));
				graph->insertEdge(id2, new Edge(id2, id1, NULL));
			}
			ili2 = ili2->getNext();
		}

		ili = ili->getNext();
	}
	delete allIDs;

//	// Insert into shared array of graphs (CRITICAL SECTION).
	if (pthread_mutex_lock(&mutex2))
		cout << "ERROR: Unable to lock mutex." << endl;
	else {
		graphs[graphCounter++] = graph;
		if (pthread_mutex_unlock(&mutex2))
			cout << "ERROR: Unable to unlock mutex." << endl;
	}

	pthread_exit(NULL);
	return NULL;
}
