/**
 * CommunityDiscovery.h
 */

#pragma once

#include "header.h"
#include "../Graph.h"
#include "../list/CommunityListItem.h"
#include <stdlib.h>
#include <string.h>

/*
 *
 * Compute the results of CPM algorithm for the set of size which
 * is identified in cliqueSize
 *
 * In this function you can call your personal
 * Communities* cliquePercolationMethod(int k, Graph* g);
 * as many times you want
 *
 */
Cpm** computeCPMResults(Graph **graphs, int *cliqueSize , int N) {

	cout << "----------CPM------------" << endl;
	Cpm **ret = (Cpm**) malloc(N* sizeof(Cpm*));

	for(int i=0 ; i<N ; i++){

		Cpm *cpm = (Cpm*) malloc(sizeof(Cpm));
		cpm->forum = (char*) malloc(MAX_STRING_LENGTH);
		strcpy(cpm->forum, graphs[i]->getName());

		for(int j=0 ; j<2 ; j++){
			Communities * com = cliquePercolationMethod(cliqueSize[j],graphs[i] );

			if(com == NULL){
				free(cpm);
				continue;
			}
			else{
				int numOfCommunities = com->getCommunitiesList()->getSize();
				community* communities = (community*) malloc(numOfCommunities * sizeof(community));

				CommunityListItem* cli = (CommunityListItem*) com->getCommunitiesList()->getHead();
				int counter = 0;
				while(cli != NULL){
					List* cliqueList = cli->getCommunity()->getCommunityMembers();
					ListListItem* cliqueListLli = (ListListItem*) cliqueList->getHead();

					List* membersList = new List();
					while(cliqueListLli != NULL){
						List* communityIDlist = cliqueListLli->getList();
						IntegerListItem* communityIDhead = (IntegerListItem*) communityIDlist->getHead();

						while(communityIDhead != NULL){
							bool found = false;

							IntegerListItem* ilitemp = (IntegerListItem*) membersList->getHead();
							while(ilitemp != NULL){
								if(communityIDhead->getInt() == ilitemp->getInt())
									found = true;

								ilitemp = ilitemp->getNext();
							}
							if(!found)
								membersList->insertItem(new IntegerListItem(communityIDhead->getInt()));

							communityIDhead = communityIDhead->getNext();
						}
						cliqueListLli = cliqueListLli->getNext();
					}

					int *members = (int*) malloc(membersList->getSize() * sizeof(int));
					IntegerListItem* ilitemp = (IntegerListItem*) membersList->getHead();
					for(int k =0; k< membersList->getSize() ; k++){
						members[k] = ilitemp->getInt();
						ilitemp = ilitemp->getNext();
					}
					communities[counter].numberOfMembers = membersList->getSize();
					communities[counter].members = members;


					cli= cli->getNext();
					counter++;
				}
				algorithmResults results;
				results.numberOfCommunities = numOfCommunities;
				results.communities = communities;

				if(j==1)
					cpm->clique4 = results;
				else
					cpm->clique3 = results;
			}
			delete com;
		}
		ret[i] = cpm;
	}

	cout << "Finished all instances of CPM for every Graph" << endl;

	return ret;
}

/*
 * Compute the results of GN algorithm
 */
Gn** computeGNResults(Graph **graphs, double maxModularity, int N) {
	cout << "----------Girvan-Newman------------" << endl;
	Gn **ret = (Gn**) malloc(N * sizeof(Gn*));
	for (int i = 0; i < N; i++) {
		Communities *com = girvanNewman(maxModularity, graphs[i]);
//		com->print();
		int numberOfCom = com->getCommunitiesList()->getSize();
		community *communities = (community*) malloc(numberOfCom * sizeof(community));

		CommunityListItem *cli = (CommunityListItem*) com->getCommunitiesList()->getHead();
		int counter = 0;
		while (cli) {
			int memberNo = cli->getCommunity()->getCommunityMembers()->getSize();
			int *members = (int*) malloc(memberNo * sizeof(int));
			IntegerListItem *ili = (IntegerListItem*) cli->getCommunity()->getCommunityMembers()->getHead();
			for (int j = 0; j < memberNo; j++) {
				members[j] = ili->getInt();
				ili = ili->getNext();
			}

			communities[counter].numberOfMembers = memberNo;
			communities[counter].members = members;
			counter++;

			cli = cli->getNext();
		}

		algorithmResults results;
		results.numberOfCommunities = numberOfCom;
		results.communities = communities;

		Gn *gn = (Gn*) malloc(sizeof(Gn));
		gn->forum = (char*) malloc(MAX_STRING_LENGTH);
		strcpy(gn->forum, graphs[i]->getName());
		gn->results = results;

		ret[i] = gn;

		delete com;
	}

	cout << "Finished all GVs" << endl;

	return ret;
}

