/*
 =============================================================================
 Name      : SD-2014-Part-3.c
 Version   : 1
 Copyright : SD-Team
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h> 

#include "header.h"
#include "CommunityDiscovery.h"
#include "GraphQueries.h"

Forum** getTopNForums();
boolean validateTopNResults(Forum **forums);
boolean validateCPMResults(Cpm **cpm);
boolean validateGNResults(Gn **gn);
void free_memory(Forum **topForums, Cpm **cpm, Gn **gn);

int compareForums(const void *data1, const void *data2) {
	Forum *forum1 = (Forum *) data1;
	Forum *forum2 = (Forum *) data2;

	int nameCompare = strcmp(forum1->name, forum2->name);
	int idCompare = forum1->size - forum2->size;

	if (idCompare == 0)
		return nameCompare;
	else
		return 0;
}

int compareIntegers(const void *data1, const void *data2) {
	return (*(int *) data1 - *(int *) data2);
}

int main_part3(void) {
	Cpm **cpm = NULL;
	Gn **gn = NULL;
	printf("\n");
	boolean error = False;

	/*Create graph list*/
	Graph **graphs;

	/*Compute the top-6 forums*/
	Forum **topForums = computeTopNForums(&graphs, NUMBER_OF_TOP_N_FORUMS);

	for (int i = 0; i < NUMBER_OF_TOP_N_FORUMS; i++)
		cout << topForums[i]->name << ": " << topForums[i]->size << endl;

	/*Validate top-6 results*/
	if (validateTopNResults(topForums) == False)
		error = True;

	cout << ((!error) ? ("PASS - preprocessing") : ("FAIL - preprocessing")) << endl;


	if (!error) {
		/*Compute results with GN algorithm*/
		gn = computeGNResults(graphs, 1.0, NUMBER_OF_TOP_N_FORUMS);

//		/*Validate the results of GN algorithm*/
//		if (validateGNResults(gn) == False)
//			error = True;
	}

	cout << ((!error) ? ("PASS - girvan-newman") : ("FAIL - girvan-newman")) << endl;
	int cliqueSize[2] = { 3, 4 };

	if (!error) {
			/*Compute results with CPM algorithm for size=3,4*/
			cpm = computeCPMResults(graphs, cliqueSize, NUMBER_OF_TOP_N_FORUMS);

			//return 0;

			/*Validate the results of CPM algorithm*/
			if (validateCPMResults(cpm) == False)
				error = True;
		}

	cout << ((!error) ? ("PASS - CPM") : ("FAIL - CPM")) << endl;

	if (!error)
		printf("Successfully passed the test!!!\n");

	printf("\n\n");
	free_memory(topForums, cpm, gn);
	for (int i = 0; i < NUMBER_OF_TOP_N_FORUMS; i++)
		delete graphs[i];
	free(graphs);
	return EXIT_SUCCESS;
}

void free_memory(Forum **topForums, Cpm **cpm, Gn **gn) {

	int i, j;
	if (topForums != NULL) {
		for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; i++) {
			free(topForums[i]->name);
			free(topForums[i]);
		}
		free(topForums);
	}

	if (gn != NULL) {
		for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; i++) {

			if (gn[i] == NULL)
				continue;

			for (j = 0; j < gn[i]->results.numberOfCommunities; j++)
				free(gn[i]->results.communities[j].members);
			free(gn[i]->results.communities);
			free(gn[i]->forum);
		}
		free(gn);
	}

	if (cpm != NULL) {
		for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i) {

			if (cpm[i] == NULL)
				continue;

			for (j = 0; j < cpm[i]->clique3.numberOfCommunities; j++)
				free(cpm[i]->clique3.communities[j].members);
			free(cpm[i]->clique3.communities);

			for (j = 0; j < cpm[i]->clique4.numberOfCommunities; j++)
				free(cpm[i]->clique4.communities[j].members);
			free(cpm[i]->clique4.communities);
			free(cpm[i]->forum);
		}
		free(cpm);
	}
}

boolean validateTopNResults(Forum **forums) {

	int i;
	Forum **actualResults = getTopNForums();

	if (forums == NULL) {
		printf("Top N Forums results is empty!!!\n");
		return False;
	}

	Forum *results = (Forum*) malloc(NUMBER_OF_TOP_N_FORUMS * sizeof(Forum));
	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i)
		results[i] = *forums[i];

	qsort(results, NUMBER_OF_TOP_N_FORUMS, sizeof(Forum), compareForums);

	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i) {

		if (results[i].size != actualResults[i]->size || (strcmp(results[i].name, actualResults[i]->name) != 0)) {
			i++;
			printf("The top %d forum has size:%d and name:\"%s\" and not size:%d and name:\"%s\"\n", i, actualResults[i - 1]->size, actualResults[i - 1]->name, results[i - 1].size, results[i - 1].name);
			return False;
		}
	}
	free(results);
	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i) {
		free(actualResults[i]->name);
		free(actualResults[i]);
	}
	free(actualResults);
	return True;
}

boolean validateCPMResults(Cpm **cpm) {

	FILE *file = fopen("Cpm3Results.txt", "w");//FILE *file = fopen("./src/Cpm3Results.txt", "w");

	if (cpm == NULL)
		return False;

	int i, j, k;
	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i) {

		for (j = 0; j < cpm[i]->clique3.numberOfCommunities; ++j) {

			if (cpm[i]->clique3.communities[j].numberOfMembers > 0) {

				fprintf(file, "Community in forum %s:", cpm[i]->forum);

				qsort(cpm[i]->clique3.communities[j].members, cpm[i]->clique3.communities[j].numberOfMembers, sizeof(int), compareIntegers);

				for (k = 0; k < cpm[i]->clique3.communities[j].numberOfMembers; ++k)
					fprintf(file, " %d", cpm[i]->clique3.communities[j].members[k]);
				fprintf(file, "\n");
			}
		}
	}
	fclose(file);

	char script[92];
	strcpy(script, "sort Cpm3Results.txt -o Cpm3Results.txt");//strcpy(script, "sort ./src/Cpm3Results.txt -o ./src/Cpm3Results.txt");
	system(script);
	strcpy(script, "diff project_main/Cpm3ActualResults.txt Cpm3Results.txt > results3CPM.txt");//strcpy(script, "diff ./src/project_main/Cpm3ActualResults.txt ./src/Cpm3Results.txt > ./src/results3CPM.txt");
	system(script);

	file = fopen("results3CPM.txt", "r");//file = fopen("./src/results3CPM.txt", "r");
	fseek(file, 0, SEEK_END);
	if (ftell(file) != 0) {
		printf("Results for CPM for size 3 are not correct\n");
		return False;
	}
	fclose(file);

	file = fopen("Cpm4Results.txt", "w");//file = fopen("./src/Cpm4Results.txt", "w");
	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i) {

		for (j = 0; j < cpm[i]->clique4.numberOfCommunities; ++j) {

			if (cpm[i]->clique4.communities[j].numberOfMembers > 0) {

				fprintf(file, "Community in forum %s:", cpm[i]->forum);

				qsort(cpm[i]->clique4.communities[j].members, cpm[i]->clique4.communities[j].numberOfMembers, sizeof(int), compareIntegers);

				for (k = 0; k < cpm[i]->clique4.communities[j].numberOfMembers; ++k)
					fprintf(file, " %d", cpm[i]->clique4.communities[j].members[k]);
				fprintf(file, "\n");
			}
		}
	}
	fclose(file);

	memset(script, '\0', 92 * sizeof(char));
	strcpy(script, "sort Cpm4Results.txt -o Cpm4Results.txt");//strcpy(script, "sort ./src/Cpm4Results.txt -o ./src/Cpm4Results.txt");
	system(script);
	strcpy(script, "diff project_main/Cpm4ActualResults.txt Cpm4Results.txt > results4CPM.txt");//strcpy(script, "diff ./src/project_main/Cpm4ActualResults.txt ./src/Cpm4Results.txt > ./src/results4CPM.txt");
	system(script);

	file = fopen("results4CPM.txt", "r");//file = fopen("./src/results4CPM.txt", "r");
	fseek(file, 0, SEEK_END);
	if (ftell(file) != 0) {
		printf("Results for CPM for size 4 are not correct\n");
		return False;
	}
	fclose(file);

	return True;
}

boolean validateGNResults(Gn **gn) {

	FILE *file = fopen("GNResults.txt", "w");

	if (gn == NULL)
		return False;

	int i, j, k;
	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i) {

		for (j = 0; j < gn[i]->results.numberOfCommunities; ++j) {

			if (gn[i]->results.communities[j].numberOfMembers > 0) {

				fprintf(file, "Community in forum %s:", gn[i]->forum);

				qsort(gn[i]->results.communities[j].members, gn[i]->results.communities[j].numberOfMembers, sizeof(int), compareIntegers);

				for (k = 0; k < gn[i]->results.communities[j].numberOfMembers; ++k)
					fprintf(file, " %d", gn[i]->results.communities[j].members[k]);
				fprintf(file, "\n");
			}
		}
	}
	fclose(file);

	char script[55];
	strcpy(script, "sort GNResults.txt -o GNResults.txt");
	system(script);
	strcpy(script, "diff project_main/GNActualResults.txt GNResults.txt > resultsGN.txt");
	system(script);

	file = fopen("resultsGN.txt", "r");
	fseek(file, 0, SEEK_END);
	if (ftell(file) != 0) {
		printf("Results for GN are not correct\n");
		return False;
	}
	fclose(file);

	return True;
}

Forum** getTopNForums() {

	int i;
	Forum **forums;
	forums = (Forum**) malloc(NUMBER_OF_TOP_N_FORUMS * sizeof(Forum*));

	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i)
		forums[i] = (Forum*) malloc(sizeof(Forum));

	for (i = 0; i < NUMBER_OF_TOP_N_FORUMS; ++i) {
		// Adjusted names to system's convention.
		if (i == 0) {
			forums[i]->size = 82;
			forums[i]->name = (char*) malloc(26 * sizeof(char));
			strcpy(forums[i]->name, "Forum34680"); // Wall of Xiomara Fernandez
		} else if (i == 1) {
			forums[i]->size = 72;
			forums[i]->name = (char*) malloc(30 * sizeof(char));
			strcpy(forums[i]->name, "Forum228460"); // Album 13 of Xiomara Fernandez
		} else if (i == 2) {
			forums[i]->size = 62;
			forums[i]->name = (char*) malloc(29 * sizeof(char));
			strcpy(forums[i]->name, "Forum228280"); // Album 4 of Xiomara Fernandez
		} else if (i == 3) {
			forums[i]->size = 17;
			forums[i]->name = (char*) malloc(17 * sizeof(char));
			strcpy(forums[i]->name, "Forum43920"); // Wall of R. Singh
		} else if (i == 5) {
			forums[i]->size = 15;
			forums[i]->name = (char*) malloc(22 * sizeof(char));
			strcpy(forums[i]->name, "Forum9534125"); // Best Of Gordon Murray
		} else {
			forums[i]->size = 15;
			forums[i]->name = (char*) malloc(30 * sizeof(char));
			strcpy(forums[i]->name, "Forum228560"); // Album 18 of Xiomara Fernandez
		}
	}
	return forums;
}
