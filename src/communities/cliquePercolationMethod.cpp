/*
 * cliquePercolationMethod.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: athan
 */


#include "_communities.h"
#include "../list/CommunityListItem.h"
#include "../list/IntegerListItem.h"
#include "../list/ListListItem.h"
#include "../list/GraphListItem.h"
#include "../CliqueNode.h"
#include "../Edge.h"
#include "findCliques.h"
#include <iostream>

using namespace std;

Communities* cliquePercolationMethod(int k , Graph* graph){

	List* allIDs = graph->getAllIDs();
	List* ignoredIDs = new List();

	//Pruning the Graph , removing every node that ultimately has edgeSize < k-1
	bool touched = true;
	int j =0;
	while(touched){
		j++;
		touched = false;
		IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
		while(ili != NULL){
			bool skipped = false;
			int nodeID = ili->getInt();
			BucketItem* bucketItem = graph->lookupItem(nodeID);
			List* edgeList = bucketItem->getEdgeList();
			EdgeListItem* eli = (EdgeListItem*) edgeList->getHead();
			int edgeListSize = edgeList->getSize();

			while(eli != NULL){
				Edge* edge = eli->getElement();
				int endNodeID = edge->getEndNodeId();
				IntegerListItem* ignoredListItem = (IntegerListItem*)ignoredIDs->getHead();
				while(ignoredListItem != NULL){
					if(endNodeID == ignoredListItem->getInt()){
						edgeListSize--;
						break;
					}
					ignoredListItem= ignoredListItem->getNext();
				}
				if( edgeListSize < k-1 ){
					skipped = true;
					IntegerListItem* temp = ili;
					ignoredIDs->insertItem(new IntegerListItem(temp->getInt()));
					touched = true;
					ili = ili->getNext();
					allIDs->deleteItem(temp);
					break;
				}

				eli = eli->getNext();
			}
			if(!skipped)
				ili = ili->getNext();
		}
	}

	IntegerListItem *ili = (IntegerListItem*) allIDs->getHead();
	int nodeNumber = allIDs->getSize();
	LinearHashTable *idMapReverse = new LinearHashTable(nodeNumber, 1); //a reverse map matching [0..nodenumber-1] to nodeIds

	for(int i=0; i<nodeNumber; i++){
		Properties* idReverseMapProp = new Properties(1);
		idReverseMapProp->setIntegerProperty(ili->getInt(),0);
		idMapReverse->Insert(new Node(i,idReverseMapProp));

		ili = ili->getNext();
	}

	//Finding all k-cliques

	List* cliques = new List();
	List *ids = new List();
	iterate(graph,cliques, ids,0 , nodeNumber,k, idMapReverse);
	delete ids;
	delete idMapReverse;

	//Construction of graph with hyper-nodes corresponding to k-cliques

	Graph* cliqueGraph = new Graph(5,10);

	ListListItem* lli = (ListListItem* )cliques->getHead();
	int i=0;
	while(lli != NULL){
		List* clique = lli->getList();
		List* newClique = new List();
		IntegerListItem* cliqueHead = (IntegerListItem*) clique->getHead();

		while(cliqueHead != NULL){
			newClique->insertItem(new IntegerListItem(cliqueHead->getInt()));
			cliqueHead = cliqueHead->getNext();
		}

		cliqueGraph->insertNode(new CliqueNode(i,NULL,newClique));

		i++;
		lli = lli->getNext();
	}

	delete cliques;

	//Insert edges of adjacent hyper-nodes

	List * allCliqueIds = cliqueGraph->getAllIDs();
	IntegerListItem* cliqueILI = (IntegerListItem*) allCliqueIds->getHead();

	while(cliqueILI != NULL){
		int cliqueID = cliqueILI->getInt();
		CliqueNode* cliqueNode = (CliqueNode*) cliqueGraph->lookupNode(cliqueID);
		List* IdsFromCliqueList = cliqueNode->getClique();

		IntegerListItem* nextcliqueILI = (IntegerListItem*) cliqueILI->getNext();
		while(nextcliqueILI != NULL){
			int nextcliqueID = nextcliqueILI->getInt();
			CliqueNode* nextcliqueNode = (CliqueNode*) cliqueGraph->lookupNode(nextcliqueID);
			List* nextIdsFromCliqueList = nextcliqueNode->getClique();

			int count=0;
			IntegerListItem* idILI = (IntegerListItem*) IdsFromCliqueList->getHead();
			while(idILI != NULL){
				int checkID = idILI->getInt();

				IntegerListItem* nextidILI = (IntegerListItem*) nextIdsFromCliqueList->getHead();
				while(nextidILI != NULL){
					int nextcheckID = nextidILI->getInt();
					if(checkID == nextcheckID){
						count++;
						break;
					}
					nextidILI = nextidILI->getNext();
				}

				idILI= idILI->getNext();
			}
			if(count == k-1){

				cliqueGraph->insertEdge(cliqueID,new Edge(cliqueID,nextcliqueID,NULL));
				cliqueGraph->insertEdge(nextcliqueID,new Edge(nextcliqueID,cliqueID,NULL));
			}

			nextcliqueILI = nextcliqueILI->getNext();
		}
		cliqueILI = cliqueILI->getNext();
	}

	//find communities
	Communities* rawCommunities = cliqueGraph->findCommunities();

	List* communities = new List();

	CommunityListItem* cli =(CommunityListItem*) rawCommunities->getCommunitiesList()->getHead();
	int communityId =0;
	while(cli!=NULL){
		Community* community = cli->getCommunity();
		List* communityMembers = community->getCommunityMembers();
		List* communityOfcliques = new List();

		IntegerListItem* communityMember =(IntegerListItem*) communityMembers->getHead();
		while(communityMember!=NULL){

			int hyperNodeId = communityMember->getInt();
			CliqueNode* cliqueNode = (CliqueNode*) cliqueGraph->lookupNode(hyperNodeId);
			List* cliqueNodeList = cliqueNode->getClique();
			List* newClique = new List();

			IntegerListItem* cliqueNodeListHead = (IntegerListItem*) cliqueNodeList->getHead();
			while(cliqueNodeListHead != NULL){
				newClique->insertItem(new IntegerListItem(cliqueNodeListHead->getInt()));
				cliqueNodeListHead = cliqueNodeListHead->getNext();
			}

			ListListItem* clique = new ListListItem(newClique);
			communityOfcliques->insertItem(clique);

			communityMember = communityMember->getNext();
		}

		Community* newcommunity = new Community(communityId, communityOfcliques);
		CommunityListItem* newcli = new CommunityListItem(newcommunity);
		communities->insertItem(newcli);

		communityId++;
		cli = cli->getNext();
	}

	Communities* ret = new Communities(communities);

	delete allIDs;
	delete ignoredIDs;
	delete allCliqueIds;
	delete cliqueGraph;

	return ret;
}

