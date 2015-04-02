/*
 * query4.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: athan
 */

#include "queries.h"
#include "../graph_metrics/metrics.h"
#include "../project_main/GraphLib.h"
#include "../project_main/GraphQueries.h"
#include "../graph_metrics/metrics.h"
#include "../properties/Properties.h"
#include "../project_main/defines.h"
#include "Trend.h"
#include "TrendListItem.h"
#include "TrendList.h"
#include "../search/TidalTrust.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

Graph* buildTrustGraph(char* forum, Graph* g) {

	char* forumFile = "queries/dataset/forum.csv";

	cout << "Forum :" << forum << endl;

	int forumID;
	string line;
	string line1;

	ifstream myfile(forumFile);
	if (myfile.is_open()) {
		getline(myfile, line1);		//ignore the first line
		while (getline(myfile, line)) {

			char *myString = (char*) line.c_str();
			char *p = strtok(myString, "|"); // get the forum ID

			// Get the forum ID
			stringstream s_str(p);

			s_str >> forumID;

			p = strtok(NULL, "|");		// get the forum name
			if (strcmp(forum, p) == 0) {
				cout << "Found " << p << " ID : " << forumID << endl;
				break;
			}
		}
	}
	myfile.close();


	Graph* forumHasMemberPerson = new Graph(7, 50);
	char* forumHasMemberPersonFile = "queries/dataset/forum_hasMember_person.csv";

	string line2;
	string line3;

	ifstream myfile2(forumHasMemberPersonFile);
	if (myfile2.is_open()) {
		getline(myfile2, line3);		//ignore the first line
		while (getline(myfile2, line2)) {

			char *myString = (char*) line2.c_str();
			char *p = strtok(myString, "|"); // get the forum ID

			// Get the forum ID
			stringstream s_str(p);

			int searchedforumID;
			s_str >> searchedforumID;

			if (forumID == searchedforumID) {
				p = strtok(NULL, "|");
				// Get the person ID
				stringstream s_str2(p);

				int personID;
				s_str2 >> personID;

				if (forumHasMemberPerson->lookupNode(personID) == NULL) {
					BucketItem * personBI = g->lookupItem(personID);
					assert(personBI != NULL);
					Properties * nodeProperties = personBI->getNode()->getProperties();
					Properties * newNodeProperties;
					if (nodeProperties != NULL){

						newNodeProperties = new Properties(nodeProperties->getSize());

						assert(newNodeProperties->getSize() == 4);

						for (int i = 0; i < newNodeProperties->getSize(); i++)
							newNodeProperties->setStringProperty(nodeProperties->getStringProperty(i), i);
					}
					else{
						newNodeProperties = NULL;
					}
					List * edgeList = personBI->getEdgeList();

					forumHasMemberPerson->insertNode(new Node(personID, newNodeProperties));
					EdgeListItem * edgeLI = (EdgeListItem *) edgeList->getHead();
					while (edgeLI != NULL) {
						Edge* edge = edgeLI->getElement();
						Properties* edgeProperties = edge->getProperties();
						Properties* newEdgeProperties = new Properties(edgeProperties->getSize());

						assert(newEdgeProperties->getSize() == 1);
						newEdgeProperties->setStringProperty("knows", 0);

						Edge* newEdge = new Edge(edge->getStartNodeId(), edge->getEndNodeId(), newEdgeProperties);

						forumHasMemberPerson->insertEdge(personID, newEdge);
						edgeLI = (EdgeListItem *) edgeLI->getNext();
					}
				}
			}
		}
	}
	else{
		cout<<"Couldn't open forum_hasMember_person.csv"<<endl;
	}
	myfile2.close();

//	cout << "=======================================================" << endl;
//	cout << "Graph with members of forum " << forum << " created" << endl;
//	cout << "Node number :" << forumHasMemberPerson->getNodeNo() << endl;
//	cout << "=======================================================" << endl;

	Graph* personLikesPost = new Graph(7, 20);
	char* personLikesPostFile = "queries/dataset/person_likes_post.csv";

	string line4;
	string line5;

	ifstream myfile3(personLikesPostFile);
	if (myfile3.is_open()) {
		getline(myfile3, line5);		//ignore the first line
		while (getline(myfile3, line4)) {

			char *myString = (char*) line4.c_str();
			char *p = strtok(myString, "|"); // get the person ID

			stringstream s_str(p);
			int personID;
			s_str >> personID;

			//No need to insert a person that doesnt concern us into the Graph
			if (forumHasMemberPerson->lookupNode(personID) != NULL) {

				if (personLikesPost->lookupNode(personID) == NULL)
					personLikesPost->insertNode(new Node(personID, NULL));

				p = strtok(NULL, "|");
				stringstream s_str2(p);
				int postID;
				s_str2 >> postID;
				if (personLikesPost->lookupNode(postID + DATA_SIZE) == NULL) {

					Node* postNode = new Node(postID + DATA_SIZE, NULL);
					personLikesPost->insertNode(postNode);

					Properties* edgeProperties1 = new Properties(1);
					edgeProperties1->setStringProperty("Likes", 0);
					Properties* edgeProperties2 = new Properties(1);
					edgeProperties2->setStringProperty("isLikedBy", 0);

					Edge* edge1 = new Edge(personID, postID + DATA_SIZE, edgeProperties1);
					Edge* edge2 = new Edge(postID + DATA_SIZE, personID, edgeProperties2);

					personLikesPost->insertEdge(personID, edge1);
					personLikesPost->insertEdge(postID + DATA_SIZE, edge2);
				} else {

					Properties* edgeProperties1 = new Properties(1);
					edgeProperties1->setStringProperty("Likes", 0);
					Properties* edgeProperties2 = new Properties(1);
					edgeProperties2->setStringProperty("isLikedBy", 0);

					Edge* edge1 = new Edge(personID, postID + DATA_SIZE, edgeProperties1);
					Edge* edge2 = new Edge(postID + DATA_SIZE, personID, edgeProperties2);

					personLikesPost->insertEdge(personID, edge1);
					personLikesPost->insertEdge(postID + DATA_SIZE, edge2);
				}
			}
		}
	}
	myfile3.close();

//	cout << "=======================================================" << endl;
//	cout << "Person Likes Post Graph created" << endl;
//	cout << "Node number :" << personLikesPost->getNodeNo() << endl;
//	cout << "=======================================================" << endl;

	Graph* postHasCreatorPerson = new Graph(7, 20);
	char* postHasCreatorPersonFile = "queries/dataset/post_hasCreator_person.csv";

	string line6;
	string line7;

	ifstream myfile4(postHasCreatorPersonFile);
	if (myfile4.is_open()) {
		getline(myfile4, line7);		//ignore the first line
		while (getline(myfile4, line6)) {

			char *myString = (char*) line6.c_str();
			char *p = strtok(myString, "|"); // get the post ID

			stringstream s_str(p);
			int postID;
			s_str >> postID;

			p = strtok(NULL, "|");
			stringstream s_str2(p);
			int personID;
			s_str2 >> personID;

			//No need to insert a person/post that doesnt concern us into the Graph
			if (forumHasMemberPerson->lookupNode(personID) != NULL) {

				if (postHasCreatorPerson->lookupNode(personID) == NULL)
					postHasCreatorPerson->insertNode(new Node(personID, NULL));

				if (postHasCreatorPerson->lookupNode(postID + DATA_SIZE) == NULL) {
					Node* postNode = new Node(postID + DATA_SIZE, NULL);
					postHasCreatorPerson->insertNode(postNode);

					Properties* edgeProperties1 = new Properties(1);
					edgeProperties1->setStringProperty("Created", 0);
					Properties* edgeProperties2 = new Properties(1);
					edgeProperties2->setStringProperty("hasCreator", 0);

					Edge* edge1 = new Edge(personID, postID + DATA_SIZE, edgeProperties1);
					Edge* edge2 = new Edge(postID + DATA_SIZE, personID, edgeProperties2);

					postHasCreatorPerson->insertEdge(personID, edge1);
					postHasCreatorPerson->insertEdge(postID + DATA_SIZE, edge2);
				} else {
					Properties* edgeProperties1 = new Properties(1);
					edgeProperties1->setStringProperty("Created", 0);
					Properties* edgeProperties2 = new Properties(1);
					edgeProperties2->setStringProperty("hasCreator", 0);

					Edge* edge1 = new Edge(personID, postID + DATA_SIZE, edgeProperties1);
					Edge* edge2 = new Edge(postID + DATA_SIZE, personID, edgeProperties2);

					postHasCreatorPerson->insertEdge(personID, edge1);
					postHasCreatorPerson->insertEdge(postID + DATA_SIZE, edge2);
				}
			}
		}
	}

	myfile4.close();
//	cout << "=======================================================" << endl;
//	cout << "Post has Creator Person Graph created" << endl;
//	cout << "Node number :" << postHasCreatorPerson->getNodeNo() << endl;
//	cout << "=======================================================" << endl;

	Graph* commentHasCreatorPerson = new Graph(7, 20);
	char* commentHasCreatorPersonFile = "queries/dataset/comment_hasCreator_person.csv";

	string line8;
	string line9;

	ifstream myfile5(commentHasCreatorPersonFile);
	if (myfile5.is_open()) {
		getline(myfile5, line9);		//ignore the first line
		while (getline(myfile5, line8)) {
			char *myString = (char*) line8.c_str();
			char *p = strtok(myString, "|"); // get the comment ID

			stringstream s_str(p);
			int commentID;
			s_str >> commentID;

			p = strtok(NULL, "|");
			stringstream s_str2(p);
			int personID;
			s_str2 >> personID;

			//No need to insert a person/comment that doesnt concern us into the Graph
			if (forumHasMemberPerson->lookupNode(personID) != NULL) {

				if (commentHasCreatorPerson->lookupNode(personID) == NULL)
					commentHasCreatorPerson->insertNode(new Node(personID, NULL));

				if (commentHasCreatorPerson->lookupNode(commentID + DATA_SIZE) == NULL) {
					Node* commentNode = new Node(commentID + DATA_SIZE, NULL);
					commentHasCreatorPerson->insertNode(commentNode);

					Properties* edgeProperties1 = new Properties(1);
					edgeProperties1->setStringProperty("Created", 0);
					Properties* edgeProperties2 = new Properties(1);
					edgeProperties2->setStringProperty("hasCreator", 0);

					Edge* edge1 = new Edge(personID, commentID + DATA_SIZE, edgeProperties1);
					Edge* edge2 = new Edge(commentID + DATA_SIZE, personID, edgeProperties2);

					commentHasCreatorPerson->insertEdge(personID, edge1);
					commentHasCreatorPerson->insertEdge(commentID + DATA_SIZE, edge2);
				} else {
					Properties* edgeProperties1 = new Properties(1);
					edgeProperties1->setStringProperty("Created", 0);
					Properties* edgeProperties2 = new Properties(1);
					edgeProperties2->setStringProperty("hasCreator", 0);

					Edge* edge1 = new Edge(personID, commentID + DATA_SIZE, edgeProperties1);
					Edge* edge2 = new Edge(commentID + DATA_SIZE, personID, edgeProperties2);

					commentHasCreatorPerson->insertEdge(personID, edge1);
					commentHasCreatorPerson->insertEdge(commentID + DATA_SIZE, edge2);
				}
			}
		}
	}

	myfile5.close();
//	cout << "=======================================================" << endl;
//	cout << "Comment has Creator Person Graph created" << endl;
//	cout << "Node number :" << commentHasCreatorPerson->getNodeNo() << endl;
//	cout << "=======================================================" << endl;

	Graph* commentReplyOfPost = new Graph(7, 20);
	char* commentReplyOfPostFile = "queries/dataset/comment_replyOf_post.csv";

	string line10;
	string line11;

	ifstream myfile6(commentReplyOfPostFile);
	if (myfile6.is_open()) {
		getline(myfile6, line11);
		while (getline(myfile6, line10)) {
			char *myString = (char*) line10.c_str();
			char *p = strtok(myString, "|"); // get the comment ID

			stringstream s_str(p);
			int commentID;
			s_str >> commentID;

			p = strtok(NULL, "|");
			stringstream s_str2(p);
			int postID;
			s_str2 >> postID;

			if (postHasCreatorPerson->lookupNode(postID + DATA_SIZE) != NULL) {

				if (commentReplyOfPost->lookupNode(postID) == NULL)
					commentReplyOfPost->insertNode(new Node(postID, NULL));

				if (commentHasCreatorPerson->lookupNode(commentID + DATA_SIZE) != NULL) {

					//comment id = commentID + 1734000
					if (commentReplyOfPost->lookupNode(commentID + POST_DATA_SIZE) == NULL) {
						commentReplyOfPost->insertNode(new Node(commentID + POST_DATA_SIZE, NULL));

						Properties* edgeProperties1 = new Properties(1);
						edgeProperties1->setStringProperty("ReplyOf", 0);
						Properties* edgeProperties2 = new Properties(1);
						edgeProperties2->setStringProperty("hasReply", 0);

						Edge* edge1 = new Edge(commentID + POST_DATA_SIZE, postID, edgeProperties1);
						Edge* edge2 = new Edge(postID, commentID + POST_DATA_SIZE, edgeProperties2);

						commentReplyOfPost->insertEdge(commentID + POST_DATA_SIZE, edge1);
						commentReplyOfPost->insertEdge(postID, edge2);
					} else {

						Properties* edgeProperties1 = new Properties(1);
						edgeProperties1->setStringProperty("ReplyOf", 0);
						Properties* edgeProperties2 = new Properties(1);
						edgeProperties2->setStringProperty("hasReply", 0);

						Edge* edge1 = new Edge(commentID + POST_DATA_SIZE, postID, edgeProperties1);
						Edge* edge2 = new Edge(postID, commentID + POST_DATA_SIZE, edgeProperties2);

						commentReplyOfPost->insertEdge(commentID + POST_DATA_SIZE, edge1);
						commentReplyOfPost->insertEdge(postID, edge2);
					}
				}
			}
		}
	}
	myfile6.close();
//	cout << "=======================================================" << endl;
//	cout << "Comment reply of Post Graph created" << endl;
//	cout << "Node number :" << commentReplyOfPost->getNodeNo() << endl;
//	cout << "=======================================================" << endl;

	//check the edgelist of each person inside the TrustGraph , calculate the trust among the rest and insert edge where it applies.

	Graph* TrustGraph = new Graph(7, 20);

	LinearHashTable * hashTable = forumHasMemberPerson->getHashTable();
	BucketList ** bucketListTable = hashTable->getTable();

	for (int i = 0; i < hashTable->getCurrentBucketNo(); i++) {
		BucketList *bucketList = bucketListTable[i];
		BucketListItem *bucketListItem = (BucketListItem*) bucketList->getHead();
		while (bucketListItem != NULL) {
			Bucket* bucket = bucketListItem->getElement();
			for (int j = 0; j < bucket->getSize(); j++) {
				BucketItem * bucketItem = bucket->getBucketItemByIndex(j);
				int startNodeId = bucketItem->getNodeID();
				List * startNodeEdgeList = bucketItem->getEdgeList();
				EdgeListItem * edgeListItem = (EdgeListItem *) startNodeEdgeList->getHead();
				while (edgeListItem != NULL) {
					Edge * edge = edgeListItem->getElement();
					int endID = edge->getEndNodeId();

					//We found an edge to another person , member of the same forum. Calculate the trust between them
					//Create the nodes in the Trust Graph if they dont exist already

					if (TrustGraph->lookupNode(startNodeId) == NULL) {

						Properties* tidalTrustProperties = new Properties(2);
						tidalTrustProperties->setDoubleProperty(-1.0, 0); //trustValue
						tidalTrustProperties->setIntegerProperty(INT_MAX, 1);	 //last updated depth

						//startNode->setTidalTrustProperties(tidalTrustProperties);
						TrustNode* startNode = new TrustNode(startNodeId, NULL, tidalTrustProperties);

						TrustGraph->insertNode(startNode);
						//cout<<"StartNode Created Id: "<<startNodeId<<endl;
					}
					if (TrustGraph->lookupNode(endID) == NULL) {

						Properties* tidalTrustProperties = new Properties(2);
						tidalTrustProperties->setDoubleProperty(-1.0, 0); //trustValue
						tidalTrustProperties->setIntegerProperty(INT_MAX, 1);	 //last updated depth

						//endNode->setTidalTrustProperties(tidalTrustProperties);
						TrustNode* endNode = new TrustNode(endID, NULL, tidalTrustProperties);

						TrustGraph->insertNode(endNode);
						//cout<<"EndNode Created Id: "<<endID<<endl;
					}

					//Create a trustEdge between them
					Properties* trustEdgeProperties = new Properties(2);
					trustEdgeProperties->setStringProperty("trusts", 0);
					trustEdgeProperties->setDoubleProperty(0.0, 1);

					Edge* trustEdge = new Edge(startNodeId, endID, trustEdgeProperties);
					TrustGraph->insertEdge(startNodeId, trustEdge);

					int likesToJFromI = 0;
					int commentsToJFromI = 0;
					int totalLikesFromI = 0;
					int totalCommentsFromI = 0;

					BucketItem* personLikesPostBI = personLikesPost->lookupItem(startNodeId);
					if(personLikesPostBI != NULL){

						List* personLikesPostEdgeList = personLikesPostBI->getEdgeList();
						EdgeListItem* personLikesPostEdgeLI = (EdgeListItem*) personLikesPostEdgeList->getHead();
						while(personLikesPostEdgeLI != NULL){
							Edge* personLikesPostEdge = personLikesPostEdgeLI->getElement();
							if(strcmp(personLikesPostEdge->getProperties()->getStringProperty(0),"Likes") == 0){
								int postID = personLikesPostEdge->getEndNodeId();  //no need to do -DATA_SIZE
								BucketItem* postBI = postHasCreatorPerson->lookupItem(postID);
								if(postBI != NULL){
									List* postEdgeList = postBI->getEdgeList();
									if(postEdgeList->getSize() == 1){		//only one creator
										EdgeListItem* postEdgeLI = (EdgeListItem*) postEdgeList->getHead();
										Edge* postHasCreatorEdge = postEdgeLI->getElement();
										if(strcmp(postHasCreatorEdge->getProperties()->getStringProperty(0),"hasCreator") == 0)
											if(postHasCreatorEdge->getEndNodeId() == endID)
												likesToJFromI++;
									}
								}
								totalLikesFromI++;
							}
							personLikesPostEdgeLI = personLikesPostEdgeLI->getNext();
						}
					}

					BucketItem* personCreatedCommentBI = commentHasCreatorPerson->lookupItem(startNodeId);
					if(personCreatedCommentBI != NULL){

						List* personCreatedCommentEdgeList = personCreatedCommentBI->getEdgeList();
						EdgeListItem* personCreatedCommentELI = (EdgeListItem*) personCreatedCommentEdgeList->getHead();
						while(personCreatedCommentELI != NULL){
							Edge* personCreatedCommentEdge = personCreatedCommentELI->getElement();
							if(strcmp(personCreatedCommentEdge->getProperties()->getStringProperty(0),"Created") == 0){
								int commentID = personCreatedCommentEdge->getEndNodeId() - DATA_SIZE + POST_DATA_SIZE;
								BucketItem* postHasReplyCommentBI = commentReplyOfPost->lookupItem(commentID);
								if(postHasReplyCommentBI != NULL){
									List* postHasReplyCommentEdgeList = postHasReplyCommentBI->getEdgeList();
									if(postHasReplyCommentEdgeList->getSize() == 1){	//one post to reply to
										EdgeListItem* postHasReplyCommentELI = (EdgeListItem*) postHasReplyCommentEdgeList->getHead();
										Edge* postHasReplyCommentEdge = postHasReplyCommentELI->getElement();
										if(strcmp(postHasReplyCommentEdge->getProperties()->getStringProperty(0), "ReplyOf") == 0){
											int postID = postHasReplyCommentEdge->getEndNodeId();
											BucketItem* postBI = postHasCreatorPerson->lookupItem(postID + DATA_SIZE);
											if(postBI != NULL){
												List* postEdgeList = postBI->getEdgeList();
												if(postEdgeList->getSize() == 1){		//only one creator
													EdgeListItem* postEdgeLI = (EdgeListItem*) postEdgeList->getHead();
													Edge* postHasCreatorEdge = postEdgeLI->getElement();
													if(strcmp(postHasCreatorEdge->getProperties()->getStringProperty(0),"hasCreator") == 0)
														if(postHasCreatorEdge->getEndNodeId() == endID)
															commentsToJFromI++;
												}
											}
										}
									}
									totalCommentsFromI++;
								}
							}
							personCreatedCommentELI = personCreatedCommentELI->getNext();
						}
					}

					if ((totalLikesFromI > 0) && (totalCommentsFromI > 0)) {
						double trustAmount = (0.3 * ((double) likesToJFromI/ (double) totalLikesFromI) + 0.7 * ((double) commentsToJFromI / (double) totalCommentsFromI));
						//cout<<"trustAmount is "<<trustAmount<<endl;
						if (trustAmount > 0.0) {
							BucketItem* trustBI = TrustGraph->lookupItem(startNodeId);
							List* trustEdgeList = trustBI->getEdgeList();
							EdgeListItem* trustEdgeLI = (EdgeListItem*) trustEdgeList->getHead();

							while(trustEdgeLI != NULL){
								Edge* checkedTrustEdge = trustEdgeLI->getElement();
								if(checkedTrustEdge->getEndNodeId() == endID)
									if(strcmp(checkedTrustEdge->getProperties()->getStringProperty(0), "trusts") == 0)
										checkedTrustEdge->getProperties()->setDoubleProperty(trustAmount,1);

								trustEdgeLI = trustEdgeLI->getNext();
							}
						}
					}
					else if (totalLikesFromI > 0)  {
						double trustAmount = (0.3 * ((double) likesToJFromI/ (double) totalLikesFromI));
						//cout<<"trustAmount is "<<trustAmount<<endl;
						if (trustAmount > 0.0) {
							BucketItem* trustBI = TrustGraph->lookupItem(startNodeId);
							List* trustEdgeList = trustBI->getEdgeList();
							EdgeListItem* trustEdgeLI = (EdgeListItem*) trustEdgeList->getHead();

							while(trustEdgeLI != NULL){
								Edge* checkedTrustEdge = trustEdgeLI->getElement();
								if(checkedTrustEdge->getEndNodeId() == endID)
									if(strcmp(checkedTrustEdge->getProperties()->getStringProperty(0), "trusts") == 0)
										checkedTrustEdge->getProperties()->setDoubleProperty(trustAmount,1);

								trustEdgeLI = trustEdgeLI->getNext();
							}
						}
					}
					else if  (totalCommentsFromI > 0) {
						double trustAmount =  (0.7 * ((double) commentsToJFromI / (double) totalCommentsFromI));
						//cout<<"trustAmount is "<<trustAmount<<endl;
						if (trustAmount > 0.0) {
							BucketItem* trustBI = TrustGraph->lookupItem(startNodeId);
							List* trustEdgeList = trustBI->getEdgeList();
							EdgeListItem* trustEdgeLI = (EdgeListItem*) trustEdgeList->getHead();

							while(trustEdgeLI != NULL){
								Edge* checkedTrustEdge = trustEdgeLI->getElement();
								if(checkedTrustEdge->getEndNodeId() == endID)
									if(strcmp(checkedTrustEdge->getProperties()->getStringProperty(0), "trusts") == 0)
										checkedTrustEdge->getProperties()->setDoubleProperty(trustAmount,1);

								trustEdgeLI = trustEdgeLI->getNext();
							}
						}
					}
					edgeListItem = (EdgeListItem *) edgeListItem->getNext();
				}
			}
			bucketListItem = (BucketListItem*) bucketListItem->getNext();
		}
	}

	delete commentReplyOfPost;
	delete commentHasCreatorPerson;
	delete postHasCreatorPerson;
	delete personLikesPost;
	delete forumHasMemberPerson;

	return TrustGraph;
}

double estimateTrust(Node* startNode, Node* endNode, Graph* trustGraph) {

	TidalTrust* tidaltrust = new TidalTrust(trustGraph, startNode, endNode);

	double ret = tidaltrust->estimateTrust();

	delete tidaltrust;

	return ret;
}
