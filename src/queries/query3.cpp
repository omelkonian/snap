/*
 * query3.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: athan
 */

#include "queries.h"
#include "../project_main/GraphLib.h"
#include "../project_main/GraphQueries.h"
#include "../properties/Properties.h"
#include "../project_main/defines.h"
#include "Trend.h"
#include "TrendListItem.h"
#include "TrendList.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../graph_metrics/metrics.h"

using namespace std;


void findTrends(int k, Graph* g, char*** womenTrends, char*** menTrends){

	/**
	 *  ======================================================
	 * 		A. Create Graphs from .csv files.
	 * 	======================================================
	 */

// Create person_hasInterest_tag graph
// Fill the attributes on the tag IDs.

	Graph* persoNhiTagGraph = new Graph(7,20);
	char* file = "queries/dataset/person_hasInterest_tag.csv";
	char* attributesfile = "queries/dataset/tag.csv";
		string line;
		string line1;

		ifstream myfile(file);
		if (myfile.is_open()) {
			getline(myfile, line1);
			while (getline(myfile, line)) {

				char *myString = (char*) line.c_str();
				char *p = strtok(myString, "|");
				// Get the first ID
				stringstream s_str(p);

				int ID1;
				s_str >> ID1;

				if (persoNhiTagGraph ->lookupNode(ID1) == NULL)
					persoNhiTagGraph ->insertNode(new Node(ID1, NULL));

				p = strtok(NULL, " ");
				// Get the second ID
				stringstream s_str2(p);

				int ID2;
				s_str2 >> ID2;

				if (persoNhiTagGraph ->lookupNode(ID2+DATA_SIZE) == NULL)
					persoNhiTagGraph ->insertNode(new Node(ID2+DATA_SIZE, NULL));

				Properties* properties1 = new Properties(1);

				properties1->setStringProperty("Interests",0);
				// Create Edge between IDs
				Edge *edge1 = new Edge(ID2+DATA_SIZE, ID1,  properties1);
				persoNhiTagGraph ->insertEdge(ID2+DATA_SIZE, edge1);

				Properties* properties2 = new Properties(1);

				properties2->setStringProperty("hasInterest",0);
				// Create Edge between IDs
				Edge *edge2 = new Edge( ID1,ID2+DATA_SIZE,  properties2);
				persoNhiTagGraph ->insertEdge(ID1, edge2);
			}
			myfile.close();
			string line2;
			string line3;

			//----Filling with attributes----

			ifstream attfile(attributesfile);
			if(attfile.is_open()){
				int numberOfAttributes = 1;		//name
				getline(attfile,line2);

				while(getline(attfile,line3)){
					char* myString = (char *)  line3.c_str();

					Properties* properties = new Properties(numberOfAttributes);

					char *pch = strtok(myString, "|");
					// Get the ID in order to insert the attributes
					stringstream s_str(pch);

					int nodeId;
					s_str >> nodeId;

					BucketItem* bucketItem= persoNhiTagGraph->getHashTable()->Lookup(nodeId+DATA_SIZE);
					if(bucketItem == NULL){
						cout<<"NULL bucketItem.Searched nodeId :"<<nodeId<<endl;
						continue;
					}
					Node* node = bucketItem->getNode();

					for(int i=0 ; i <numberOfAttributes ; i++){
						pch = strtok(NULL, "|");
						char attribute[MAX_WORD];
						strcpy(attribute,pch);
						properties->setStringProperty(attribute,i);

					}
					node->setProperties(properties);
				}
				attfile.close();
				//----Filling with attributes done----
			}
			else{
				cout << "Unable to open "<<attfile << endl;
				attfile.close();
				myfile.close();
				}
		}
		else{
			cout << "Unable to open "<<file << endl;
			myfile.close();
		}

/**
	 *  ==============================================================
	 * 		B. For each Tag build a MenTagGraph and a WomanTagGraph,
	 * 		insert the nodes from personKnowsperson and find maxCC.
	 * 	===============================================================
	 */


		LinearHashTable* hashTable = persoNhiTagGraph->getHashTable();
		BucketList **bucketListTable = hashTable->getTable();
		TrendList* menTrendList = new TrendList();
		TrendList* womenTrendList = new TrendList();

		int trendamount=0;
		for (int i = 0; i < hashTable->getCurrentBucketNo(); i++){
			BucketList *bucketList = bucketListTable[i];
			BucketListItem *cur = (BucketListItem*)bucketList->getHead();
			while (cur!= NULL){
				Bucket *bucket = cur->getElement();
				for (int j = 0; j < bucket->getSize(); j++){
					BucketItem *bi = bucket->getBucketItemByIndex(j);
					int startNodeId;

					if(( startNodeId = bi->getNodeID()) >= DATA_SIZE){
						//the startNodeId belongs to a tag
						Graph* menTagGraph = new Graph(7,20);
						Graph* womenTagGraph = new Graph(7,20);

						char trendName[MAX_WORD];
						strcpy(trendName,bi->getNode()->getProperties()->getStringProperty(0));

						trendamount++;
						List *edgeList = bi->getEdgeList();
						EdgeListItem* edgeListItem = (EdgeListItem*)edgeList->getHead();
						while (edgeListItem != NULL){

							Edge* edgeElement = edgeListItem->getElement();
							int reachedNodeId;

							if(edgeElement!= NULL)
								reachedNodeId = edgeElement->getEndNodeId();
							else
								break;

							//search the node into the person knows person graph
							BucketItem* searchedBucket = g->lookupItem(reachedNodeId);
							if(searchedBucket != NULL){

								Node* searchedNode = searchedBucket->getNode();

								if(searchedNode != NULL){
									Properties* searchedNodeProperties = searchedNode->getProperties();
									if(searchedNodeProperties != NULL){
										if(searchedNodeProperties->getSize() == 4){ //then we are looking at the properties of a person
											if(strcmp(searchedNodeProperties->getStringProperty(2) , "male")== 0){

												//-------Inserting Node into men----------

												List* searchedEdgeList = searchedBucket->getEdgeList();
												EdgeListItem * searchedEdgeListItem = (EdgeListItem* )searchedEdgeList->getHead();
												Properties* newNodeProperties = new Properties(4);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(0),0);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(1),1);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(2),2);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(3),3);
												menTagGraph->insertNode(new Node(reachedNodeId,newNodeProperties));
												while(searchedEdgeListItem !=NULL){

													Properties* newEdgeProperties = new Properties(1);
													newEdgeProperties->setStringProperty("knows",0);
													menTagGraph->insertEdge(reachedNodeId,new Edge(searchedEdgeListItem->getElement()->getStartNodeId(),searchedEdgeListItem->getElement()->getEndNodeId(),newEdgeProperties) );

													searchedEdgeListItem = (EdgeListItem*) searchedEdgeListItem->getNext();
												}

											}
											else if (strcmp(searchedNodeProperties->getStringProperty(2) , "female")== 0){
												//------------Inserting Node into women----------
												List* searchedEdgeList = searchedBucket->getEdgeList();
												EdgeListItem * searchedEdgeListItem = (EdgeListItem* )searchedEdgeList->getHead();
												Properties* newNodeProperties = new Properties(4);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(0),0);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(1),1);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(2),2);
												newNodeProperties->setStringProperty(searchedNodeProperties->getStringProperty(3),3);
												womenTagGraph->insertNode(new Node(reachedNodeId,newNodeProperties));
												while(searchedEdgeListItem !=NULL){

													Properties* newEdgeProperties = new Properties(1);
													newEdgeProperties->setStringProperty("knows",0);

													womenTagGraph->insertEdge(reachedNodeId, new Edge(searchedEdgeListItem->getElement()->getStartNodeId(),searchedEdgeListItem->getElement()->getEndNodeId(),newEdgeProperties));
													searchedEdgeListItem = (EdgeListItem*) searchedEdgeListItem->getNext();
												}
											}
										}
									}
									else
										cout<<"Found person in the Person_knows_Person graph but has no attributes"<<endl;
								}
								else
									cout<<"No such person in the Person_knows_Person graph "<<reachedNodeId<<endl;
							}
							edgeListItem = (EdgeListItem*) edgeListItem->getNext();
						}
						//Insert into two Lists that hold the trends and their vibes the maxCC of each graph and the trend name
						int manVibe = maxCC(menTagGraph);

						if(manVibe > 1){
							Trend* menTrend = new Trend(manVibe , trendName );
							menTrendList->insertTrend( menTrend);
						}
						int womanVibe = maxCC(womenTagGraph);

						if(womanVibe > 1){
							Trend* womenTrend= new Trend(womanVibe,trendName);
							womenTrendList->insertTrend(womenTrend);
						}
						delete womenTagGraph;
						delete menTagGraph;
					}
				}
				cur = (BucketListItem *)cur->getNext();
			}
		}
		char **menTrendMatrix = new char*[k];
		char **womenTrendMatrix = new char*[k];
		for(int i=0; i< k ; i++){
			menTrendMatrix[i] = new char[MAX_WORD];
			if(menTrendMatrix[i]== NULL){
				cout<<"menTrendMatrix new failed"<<endl;
			}
			womenTrendMatrix[i] = new char[MAX_WORD];
			if(menTrendMatrix[i]== NULL){
				cout<<"womenTrendMatrix new failed"<<endl;
			}
		}
		cout<<"___________________________________________________________________________________________"<<endl;

		for(int i =0 ; i<k; i++){
			Trend* trend = menTrendList->removeHead();
			if(trend != NULL){
				strcpy(menTrendMatrix[i], trend->getNameOfTrend() );
				delete trend;
			}
			else
				menTrendMatrix[i]=NULL ;
		}

		for(int i =0 ; i<k; i++){
			Trend* trend = womenTrendList->removeHead();
			if(trend != NULL){
				strcpy(womenTrendMatrix[i], trend->getNameOfTrend() );
				delete trend;
			}
			else
				womenTrendMatrix[i]= NULL ;
		}

		delete menTrendList;
		delete womenTrendList;

		delete persoNhiTagGraph;

		*menTrends = menTrendMatrix;
		*womenTrends = womenTrendMatrix;


}



