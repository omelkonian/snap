/*
 * TidalTrust.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: athan
 */

#include <iostream>
#include <assert.h>
#include "TidalTrust.h"

using namespace std;

TidalTrust::TidalTrust(Graph* graph, Node* startNode, Node* endNode) {
	this->graph = graph;

	this->startNode = new TrustNode(startNode->getId(), startNode->getProperties(), new Properties(2));
	if (!this->startNode) {
		cout << "ERROR: Unable to allocate memory." << endl;
		return;
	}
	this->startNode->getTidalTrustProperties()->setIntegerProperty(-1, 1);
	this->startNode->getTidalTrustProperties()->setIntegerProperty(-1.0, 0);

	this->endNode = new TrustNode(endNode->getId(), endNode->getProperties(), new Properties(2));
	if (!this->endNode) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->startNode;
		return;
	}
	this->endNode->getTidalTrustProperties()->setIntegerProperty(INT_MAX, 1);
	this->endNode->getTidalTrustProperties()->setIntegerProperty(-1.0, 0);

	this->nodeQueue = new Queue();
	this->depthQueue = new Queue();
	if (!this->nodeQueue || !this->depthQueue) {
		cout << "ERROR: Unable to allocate memory." << endl;
		delete this->startNode, this->endNode;
		return;
	}

	this->currentNode = this->graph->lookupItem(startNode->getId());
//	this->currentNode->print();
//	cout<<"______________________"<<endl;

	// Enqueue first node.
	this->nodeQueue->enqueueAsItem(this->currentNode);
	this->depthQueue->enqueueAsInt(0);
}

double TidalTrust::estimateTrust() {

	int steps =0 ;

	if (this->nodeQueue->isEmpty()){
		cout<<"Node Queue is empty"<<endl;
		return -1.0;
	}

	BucketItem *current = nodeQueue->dequeueAsItem();
	assert(current!=NULL);
	int currentDepth = depthQueue->dequeueAsInt();


	if (currentDepth < 0){
		cout<<"Current Depth < 0"<<endl;
		return -1.0;
	}

	while (current != NULL) {
		TrustNode* currentNode = (TrustNode*) current->getNode();
//		cout<<"NodeId :"<<currentNode->getId()<<endl;

		if (currentNode->getId() == this->endNode->getId()){
//			cout<<"Returning: "<<currentNode->getTidalTrustProperties()->getDoubleProperty(0)<<endl;
//			cout<<"_____________________________________"<<endl;
			return currentNode->getTidalTrustProperties()->getDoubleProperty(0);
		}

		List* neighbors = current->getEdgeList();
		assert(neighbors!= NULL);
		EdgeListItem* eli = (EdgeListItem*) neighbors->getHead();

		// Enqueue node's neighbors
		while (eli != NULL) {
			Edge* curTrustEdge = eli->getElement();
			BucketItem* endOfEdge = this->graph->lookupItem(curTrustEdge->getEndNodeId());

			if (endOfEdge == NULL) {
				eli = eli->getNext();
				cout << "Null end of edge" << endl;
				continue;
			}

			TrustNode* visitedNode = (TrustNode*) endOfEdge->getNode();
			int nodeID= visitedNode->getId();
			assert(visitedNode != NULL);

			Properties* visitedNodeProperties = visitedNode->getTidalTrustProperties();
			assert(visitedNodeProperties != NULL);

			if (visitedNodeProperties->getIntegerProperty(1) >= currentDepth) {
				double newTrust = curTrustEdge->getProperties()->getDoubleProperty(1);
				bool update = true;

				if (visitedNodeProperties->getDoubleProperty(0) > newTrust * (currentNode->getTidalTrustProperties()->getDoubleProperty(0)) )
					update = false;

				if (update) {
					if (currentDepth == 0) {
						visitedNodeProperties->setDoubleProperty(newTrust, 0);
						visitedNodeProperties->setIntegerProperty(currentDepth, 1);
						//cout<<"Updating DoubleProperty on NodeID: "<< nodeID <<" with "<<newTrust<<endl;
					} else {
						visitedNodeProperties->setDoubleProperty(newTrust * (currentNode->getTidalTrustProperties()->getDoubleProperty(0)), 0);
						visitedNodeProperties->setIntegerProperty(currentDepth, 1);
						//cout<<"Updating DoubleProperty on NodeID: "<< nodeID <<" with "<<newTrust<<endl;
					}
				}
				depthQueue->enqueueAsInt(currentDepth + 1);
				nodeQueue->enqueueAsItem(endOfEdge);
			}
			eli = eli->getNext();
		}
		current = nodeQueue->dequeueAsItem();
		currentDepth = depthQueue->dequeueAsInt();
	}

	return -1.0;
}

TidalTrust::~TidalTrust() {
//	cout << "Deleting TidalTrust" << endl;

	// Delete Queues.
	delete this->nodeQueue;
	delete this->depthQueue;

	//Reseting the TidalTrust Properties of each Node
	LinearHashTable * hashTable = this->graph->getHashTable();
	BucketList ** bucketListTable = hashTable->getTable();

	for (int i = 0; i < hashTable->getCurrentBucketNo(); i++) {
		BucketList* bucketList = bucketListTable[i];
		BucketListItem *bucketListItem = (BucketListItem*) bucketList->getHead();
		while (bucketListItem != NULL) {
			Bucket* bucket = bucketListItem->getElement();
			for (int j = 0; j < bucket->getSize(); j++) {
				BucketItem * bucketItem = bucket->getBucketItemByIndex(j);
				TrustNode* node = (TrustNode*) bucketItem->getNode();

				Properties* tidalTrustProperties = node->getTidalTrustProperties();
				tidalTrustProperties->setDoubleProperty(-1.0, 0); //trustValue
				tidalTrustProperties->setIntegerProperty(INT_MAX, 1);	 //last updated depth

				node->setTidalTrustProperties(tidalTrustProperties);
			}
			bucketListItem = (BucketListItem*) bucketListItem->getNext();
		}
	}

}
