#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include "GraphLib.h"
#include "GraphQueries.h"
#include "defines.h"

#define TRUST_GRAPH_REL_PROPERTIES_NUM 2

#define CHECKINT(text, actual, expected)                         \
  if (actual != expected) {                                   \
    printf("%-30s: Failed | actual = %3d, expected = %3d\n",  \
           text,                                              \
           actual,                                            \
           expected);                                         \
  } else {                                                    \
    printf("%-30s: Success\n", text);                     \
  }

#define CHECKDOUBLE(text, actual, expected)                         \
if ( ABS(actual,expected) > 0.01 ) {                                   \
  printf("%-30s: Failed | actual = %3f, expected = %3f\n",  \
         text,                                              \
         actual,                                            \
         expected);                                         \
} else {                                                    \
  printf("%-30s: Success\n", text);                     \
}

#define ABS(value1, value2) (value1 - value2 < 0 ) ? value2 - value1 : value1 - value2


/* Creates an edge between two persons in Trust graph and sets trust property */
Edge* setEdgeTrustProperties(int startNodeID, int endNodeID, double trust);

/* Prints an edge's properties */
void printEdgeProperties2(int startID, Edge* n);

void testBetweennessCentrality(int bucketsNumber, int bucketSize);
void testClosenessCentrality(int bucketsNumber, int bucketSize);
void testTidalTrust(int bucketsNumber, int bucketSize);
void stalkersGraphRunMetrics(Graph* gStalkers);

int main_part2(void) {
    //firstly execute a test for centrality metrics on small graphs
    int m = 2;
    int c = 3;

    testBetweennessCentrality(m, c);

    testClosenessCentrality(m, c);

    //small example for trust graph estimation
    testTidalTrust(m, c);


    /*create graph from file*/
    int bucketsNumber = 5;
    int bucketSize = 10;
    Graph* g = loadGraph(bucketsNumber, bucketSize);

    //graph metrics calls

    //plot the graph degree distribution
    degreeDistribution(g, false);

    int diam = diameter(g);
    CHECKINT("Graph diameter", diam, 14);

    double avgPthLgth = averagePathLength(g);
    CHECKDOUBLE("Graph average path length", avgPthLgth, 5.0753);

    int ccNumber = numberOfCCs(g);
    CHECKINT("Graph number of components ", ccNumber, 1);

    int maximumCC = maxCC(g);
    CHECKINT("Graph maximum connected component ", maximumCC, 111);

    double dense = density(g);
    CHECKDOUBLE("Graph density ", dense, 0.073);

    /*
     * WRONG CALCULATIONS - only considering neighbors and not multi-step paths!
    int closenessIds[5] = {		1734,   38,   8899,  3501,   75};
    float closenessIdsRes[5] = {0.109, 0.090, 0.072, 0.045, 0.009};
    for (i = 0; i < 5; ++i) {
        int nodeID = closenessIds[i];
        Node* node = lookupNode(nodeID, g);
        double closCentrty = closenessCentrality(node, g);
        CHECKDOUBLE("Graph closeness centrality ", closCentrty, closenessIdsRes[i]);
    }
	*/

    int i, k;
    int betweennessIds[5] = {       1734,   38,     8899,   9900,   75};
    float betweennessIdsRes[5] = {  0.306,  0.053,  0.018,  0.005,  0.000};

    for (i = 0; i < 5; ++i) {
        int nodeID = betweennessIds[i];
        Node* node = lookupNode(nodeID, g);
        double betwCentrty = betweennessCentrality(node, g);
        CHECKDOUBLE("Graph betweenness centrality ", betwCentrty, betweennessIdsRes[i]);
    }

    //graph queries calls
    // Query 1 //
    Matches* match;
    Node *dateNode = lookupNode(3755, g);
    int commonInterests = 1, ageDiff = 30, acquaintanceHops = 3, matchesNum = 1;
    match = matchSuggestion(dateNode, commonInterests, acquaintanceHops, ageDiff, matchesNum, g);

    //match result : 7107 - work_at_organization: 1650
    //get first pair's person ids
    int id1 = getMatch(0, match);

    CHECKINT("Query 1: Date result 1st id", id1, 7107);
    delete match;

    // Query 2 //
    //estimate stalkers graph with closeness centrality
    Graph* stalkersGraphCloseCentr;
    int stalkersNum = 7, likesNumber = 1, centralityMode = 1;
    Stalkers* stalkersCloseCentr = new Stalkers(stalkersNum);
    stalkersGraphCloseCentr = getTopStalkers(stalkersNum, likesNumber, centralityMode, g, stalkersCloseCentr);

    int stalkersResultsIds[] = {347, 495, 7768, 8354, 8403, 8899, 9633};
    int stalkerResultSize = 7;
    int stalkerID;
    int counter = 0;
    for (int i = 0; i < stalkersNum; ++i) {
        stalkerID = getStalkerID(i, stalkersCloseCentr);
        if (stalkerID != -1) {
            ++counter;
        }
        for (k = 0; k < stalkerResultSize; ++k) {
            if (stalkersResultsIds[k] == stalkerID) {
                break;
            }
        }
        if (k == stalkerResultSize) {
            printf("You wrongly labeled person with id %d as Stalker\n", stalkerID);
        }
    }
    CHECKINT("Query 2: Stalker closeness results size", stalkerResultSize, counter);

    //run metrics on stalker-graph
    stalkersGraphRunMetrics(stalkersGraphCloseCentr);

    //estimate stalkers graph with betweenness centrality
    Graph* stalkersGraphBetwCentr;
    Stalkers* stalkersBetwCentr = new Stalkers(stalkersNum);
    centralityMode = 2;
    stalkersGraphBetwCentr = getTopStalkers(stalkersNum, likesNumber, centralityMode, g, stalkersBetwCentr);

    counter = 0;
    for (int i = 0; i < stalkersNum; ++i) {
        stalkerID = getStalkerID(i, stalkersBetwCentr);
        if (stalkerID != -1) {
            ++counter;
        }
        for (k = 0; k < stalkerResultSize; ++k) {
            if (stalkersResultsIds[k] == stalkerID) {
                break;
            }
        }
        if (k == stalkerResultSize) {
            printf("You wrongly labeled person with id %d as Stalker\n", stalkerID);
        }
    }

    CHECKINT("Query 2: Stalker betweenness results size", stalkerResultSize, counter);


    //run metrics on stalker-graph
    stalkersGraphRunMetrics(stalkersGraphBetwCentr);


    // Query 3 - Correct//
    int trendsNum = 4;
    //allocate result tables before calling query and pass them as parameters
    char** womenTrends;
    womenTrends = (char**) malloc(trendsNum * sizeof (char*));
    char** menTrends;
    menTrends = (char**) malloc(trendsNum * sizeof (char*));
    findTrends(trendsNum, g, &womenTrends, &menTrends);


    printf("Top Women - Men Trends\n");
    int j;
    char* menTrendsResults[4] = {"Sun_Yat-sen", "Constantine_the_Great","Sigmund_Freud", "Hussein_of_Jordan"}; //IDS: {417,11622,468,1398}
    char* womenTrendsResults[4] = {"Adolf_Hitler", "Chiang_Kai-shek", NULL, NULL}; //IDS: {138,416,null,null}

    int counterW = 0, counterM = 0;

    for (j = 0; j < 4; ++j) {
        if (menTrends[j] != NULL) {
            ++counterM;

            for (k = 0; k < 4; ++k) {

                if (strcmp(menTrends[j], menTrendsResults[k]) == 0) {
                    break;
                }
            }
            if (k == 4) {
                printf("You wrongly labeled tag with %s as top trend\n", menTrends[j]);
            }
        }
    }
    CHECKINT("Query 3: Mens Trends result size", 4, counterM);


    for (j = 0; j < 4; ++j) {
        if (womenTrends[j] != NULL) {
            ++counterW;

            for (k = 0; k < 2; ++k) {

                if (strcmp(womenTrends[j], womenTrendsResults[k]) == 0) {
                    break;
                }
            }
            if (k == 2) {
                printf("You wrongly labeled tag with %s as top trend\n", menTrends[j]);
            }
        }
    }

    CHECKINT("Query 3: Women Trends result size", 2, counterW);


    cout<<"_____________________________________"<<endl;
    // Query 4 //
//    int forumID = 34680;
    char *forumName = "Wall of Xiomara Fernandez";

    Graph *trustGraph = buildTrustGraph(forumName, g);

    int trustANodeId = 30;
    int trustBNodeId = 9805;
    int trustCNodeId = 9700;
    Node *ta = lookupNode(trustANodeId, trustGraph);
    assert(ta != NULL);
    Node *tb = lookupNode(trustBNodeId, trustGraph);
    assert(tb != NULL);
    Node *tc = lookupNode(trustCNodeId, trustGraph);
    assert(tc != NULL);

    double trustAB;
    trustAB = estimateTrust(ta, tb,  trustGraph);
    printf("Trust between nodes (%d,%d) is %f\n", trustANodeId, trustBNodeId, trustAB);
    CHECKDOUBLE("Trust: (30,9805) ", trustAB, 0.134);
    cout<<"_____________________________________"<<endl;
    double trustAC;
    trustAC = estimateTrust(ta,tc,  trustGraph);
    printf("Trust between nodes (%d,%d) is %f\n", trustANodeId, trustCNodeId, trustAC);
    CHECKDOUBLE("Trust: (30,9700) ", trustAC, 0.15);

    return EXIT_SUCCESS;
}

Edge* setEdgeTrustProperties(int startNodeID, int endNodeID, double trust) {

    /*create edge properties*/
    Properties* propEdge = createProperties(TRUST_GRAPH_REL_PROPERTIES_NUM);
    setDoubleProperty(trust, 1, propEdge);

    /*create an edge*/
    Edge* e = createEdge(startNodeID, endNodeID, propEdge);
    return e;
}

void printEdgeProperties2(int startID, Edge* e) {
    e->print();
}

void testBetweennessCentrality(int bucketsNumber, int bucketSize) {
    //create small graph for testing betweenness Centrality
    Graph* gBetw = createGraph(bucketsNumber, bucketSize);

    Node* n1Betw = createNode(1, NULL);
    Node* n2Betw = createNode(2, NULL);
    Node* n3Betw = createNode(3, NULL);
    Node* n4Betw = createNode(4, NULL);
    Node* n5Betw = createNode(5, NULL);

    insertNode(n1Betw, gBetw);
    insertNode(n2Betw, gBetw);
    insertNode(n3Betw, gBetw);
    insertNode(n4Betw, gBetw);
    insertNode(n5Betw, gBetw);

    /* Create edges and set properties */
    Edge* e1Betw = createEdge(1, 2, NULL);
    Edge* e2Betw = createEdge(2, 1, NULL);
    Edge* e3Betw = createEdge(2, 3, NULL);
    Edge* e4Betw = createEdge(2, 4, NULL);
    Edge* e5Betw = createEdge(3, 2, NULL);
    Edge* e6Betw = createEdge(3, 5, NULL);
    Edge* e7Betw = createEdge(4, 2, NULL);
    Edge* e8Betw = createEdge(4, 5, NULL);
    Edge* e9Betw = createEdge(5, 3, NULL);
    Edge* e10Betw = createEdge(5, 4, NULL);

    /* Insert edges in graph */
    insertEdge(1, e1Betw, gBetw);
    insertEdge(2, e2Betw, gBetw);
    insertEdge(2, e3Betw, gBetw);
    insertEdge(2, e4Betw, gBetw);
    insertEdge(3, e5Betw, gBetw);
    insertEdge(3, e6Betw, gBetw);
    insertEdge(4, e7Betw, gBetw);
    insertEdge(4, e8Betw, gBetw);
    insertEdge(5, e9Betw, gBetw);
    insertEdge(5, e10Betw, gBetw);

    double betwCentrty1 = betweennessCentrality(n1Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:1 ", betwCentrty1, 0.0 / 6.0);

    double betwCentrty2 = betweennessCentrality(n2Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:2 ", betwCentrty2, 0.583);

    double betwCentrty3 = betweennessCentrality(n3Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:3 ", betwCentrty3, 1.0 / 6.0);

    double betwCentrty4 = betweennessCentrality(n4Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:4 ", betwCentrty4, 1.0 / 6.0);

    double betwCentrty5 = betweennessCentrality(n5Betw, gBetw);
    CHECKDOUBLE("Small Graph betweenness centrality node:5 ", betwCentrty5, 0.5 / 6.0);
}

void testClosenessCentrality(int bucketsNumber, int bucketSize) {
    //create small graph for testing betweenness Centrality
    Graph* gClos = createGraph(bucketsNumber, bucketSize);

    Node* n1Clos = createNode(1, NULL);
    Node* n2Clos = createNode(2, NULL);
    Node* n3Clos = createNode(3, NULL);
    Node* n4Clos = createNode(4, NULL);
    Node* n5Clos = createNode(5, NULL);
    Node* n6Clos = createNode(6, NULL);
    Node* n7Clos = createNode(7, NULL);

    insertNode(n1Clos, gClos);
    insertNode(n2Clos, gClos);
    insertNode(n3Clos, gClos);
    insertNode(n4Clos, gClos);
    insertNode(n5Clos, gClos);
    insertNode(n6Clos, gClos);
    insertNode(n7Clos, gClos);

    /* Create edges and set properties */
    Edge* e1Clos = createEdge(1, 2, NULL);
    Edge* e2Clos = createEdge(1, 3, NULL);
    Edge* e3Clos = createEdge(2, 1, NULL);
    Edge* e4Clos = createEdge(2, 3, NULL);
    Edge* e5Clos = createEdge(3, 1, NULL);
    Edge* e6Clos = createEdge(3, 2, NULL);
    Edge* e7Clos = createEdge(3, 4, NULL);
    Edge* e8Clos = createEdge(4, 3, NULL);
    Edge* e9Clos = createEdge(4, 5, NULL);
    Edge* e10Clos = createEdge(5, 4, NULL);
    Edge* e11Clos = createEdge(5, 6, NULL);
    Edge* e12Clos = createEdge(5, 7, NULL);
    Edge* e13Clos = createEdge(6, 5, NULL);
    Edge* e14Clos = createEdge(6, 7, NULL);
    Edge* e15Clos = createEdge(7, 5, NULL);
    Edge* e16Clos = createEdge(7, 6, NULL);


     /* Insert edges in graph */
    insertEdge(1, e1Clos, gClos);
    insertEdge(1, e2Clos, gClos);
    insertEdge(2, e3Clos, gClos);
    insertEdge(2, e4Clos, gClos);
    insertEdge(3, e5Clos, gClos);
    insertEdge(3, e6Clos, gClos);
    insertEdge(3, e7Clos, gClos);
    insertEdge(4, e8Clos, gClos);
    insertEdge(4, e9Clos, gClos);
    insertEdge(5, e10Clos, gClos);
    insertEdge(5, e11Clos, gClos);
    insertEdge(5, e12Clos, gClos);
    insertEdge(6, e13Clos, gClos);
    insertEdge(6, e14Clos, gClos);
    insertEdge(7, e15Clos, gClos);
    insertEdge(7, e16Clos, gClos);


    double closCentrty1 = closenessCentrality(n1Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:1 ", closCentrty1, 3.33 / 6.0);

    double closCentrty2 = closenessCentrality(n2Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:2 ", closCentrty2, 3.33 / 6.0);

    double closCentrty3 = closenessCentrality(n3Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:3 ", closCentrty3, 4.16 / 6.0);

    double closCentrty4 = closenessCentrality(n4Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:4 ", closCentrty4, 4.0 / 6.0);

    double closCentrty5 = closenessCentrality(n5Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:5 ", closCentrty5, 4.16 / 6.0);

    double closCentrty6 = closenessCentrality(n6Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:6 ", closCentrty6, 3.33 / 6.0);

    double closCentrty7 = closenessCentrality(n7Clos, gClos);
    CHECKDOUBLE("Small Graph closeness centrality node:7 ", closCentrty7, 3.33 / 6.0);

}

void testTidalTrust(int bucketsNumber, int bucketSize) {
    //create small graph for testing tidal's trust algorithm result
    Graph* gtt = createGraph(bucketsNumber, bucketSize);

    TrustNode* n1tt = new TrustNode(1, NULL, NULL);
		Properties* tidalTrustProperties1 = new Properties(2);
		tidalTrustProperties1->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties1->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n1tt->setTidalTrustProperties(tidalTrustProperties1);
	TrustNode* n2tt = new TrustNode(2, NULL, NULL);
    	Properties* tidalTrustProperties2 = new Properties(2);
		tidalTrustProperties2->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties2->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n2tt->setTidalTrustProperties(tidalTrustProperties2);
	TrustNode* n3tt = new TrustNode(3, NULL, NULL);
		Properties* tidalTrustProperties3 = new Properties(2);
		tidalTrustProperties3->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties3->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n3tt->setTidalTrustProperties(tidalTrustProperties3);
	TrustNode* n4tt = new TrustNode(4, NULL, NULL);
		Properties* tidalTrustProperties4 = new Properties(2);
		tidalTrustProperties4->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties4->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n4tt->setTidalTrustProperties(tidalTrustProperties4);
    TrustNode* n5tt = new TrustNode(5, NULL, NULL);
		Properties* tidalTrustProperties5 = new Properties(2);
		tidalTrustProperties5->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties5->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n5tt->setTidalTrustProperties(tidalTrustProperties5);
    TrustNode* n6tt = new TrustNode(6, NULL, NULL);
		Properties* tidalTrustProperties6 = new Properties(2);
		tidalTrustProperties6->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties6->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n6tt->setTidalTrustProperties(tidalTrustProperties6);
    TrustNode* n7tt = new TrustNode(7, NULL, NULL);
		Properties* tidalTrustProperties7 = new Properties(2);
		tidalTrustProperties7->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties7->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n7tt->setTidalTrustProperties(tidalTrustProperties7);
    TrustNode* n8tt = new TrustNode(8, NULL, NULL);
		Properties* tidalTrustProperties8 = new Properties(2);
		tidalTrustProperties8->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties8->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n8tt->setTidalTrustProperties(tidalTrustProperties8);
    TrustNode* n9tt = new TrustNode(9, NULL, NULL);
		Properties* tidalTrustProperties9 = new Properties(2);
		tidalTrustProperties9->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties9->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n9tt->setTidalTrustProperties(tidalTrustProperties9);
    TrustNode* n10tt = new TrustNode(10, NULL, NULL);
		Properties* tidalTrustProperties10 = new Properties(2);
		tidalTrustProperties10->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties10->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n10tt->setTidalTrustProperties(tidalTrustProperties10);
    TrustNode* n11tt = new TrustNode(11, NULL, NULL);
		Properties* tidalTrustProperties11 = new Properties(2);
		tidalTrustProperties11->setDoubleProperty(-1.0, 0); //trustValue
		tidalTrustProperties11->setIntegerProperty(INT_MAX, 1);	 //last updated depth
		n11tt->setTidalTrustProperties(tidalTrustProperties11);

    insertNode(n1tt, gtt);
    insertNode(n2tt, gtt);
    insertNode(n3tt, gtt);
    insertNode(n4tt, gtt);
    insertNode(n5tt, gtt);
    insertNode(n6tt, gtt);
    insertNode(n7tt, gtt);
    insertNode(n8tt, gtt);
    insertNode(n9tt, gtt);
    insertNode(n10tt, gtt);
    insertNode(n11tt, gtt);


    Edge* e1tt = setEdgeTrustProperties(1, 2, 1.0);
    Edge* e2tt = setEdgeTrustProperties(1, 5, 1.0);
    Edge* e3tt = setEdgeTrustProperties(2, 3, 0.9);
    Edge* e4tt = setEdgeTrustProperties(2, 4, 0.9);
    Edge* e5tt = setEdgeTrustProperties(3, 6, 0.8);
    Edge* e6tt = setEdgeTrustProperties(4, 6, 0.3);
    Edge* e7tt = setEdgeTrustProperties(4, 7, 0.9);
    Edge* e8tt = setEdgeTrustProperties(5, 10, 0.9);
    Edge* e9tt = setEdgeTrustProperties(6, 9, 1.0);
    Edge* e10tt = setEdgeTrustProperties(7, 8, 1.0);
    Edge* e11tt = setEdgeTrustProperties(8, 9, 1.0);
    Edge* e12tt = setEdgeTrustProperties(9, 11, 1.0);
    Edge* e13tt = setEdgeTrustProperties(10, 11, 0.4);

    /* Insert edges in graph */
    insertEdge(1, e1tt, gtt);
    insertEdge(1, e2tt, gtt);
    insertEdge(2, e3tt, gtt);
    insertEdge(2, e4tt, gtt);
    insertEdge(3, e5tt, gtt);
    insertEdge(4, e6tt, gtt);
    insertEdge(4, e7tt, gtt);
    insertEdge(5, e8tt, gtt);
    insertEdge(6, e9tt, gtt);
    insertEdge(7, e10tt, gtt);
    insertEdge(8, e11tt, gtt);
    insertEdge(9, e12tt, gtt);
    insertEdge(10, e13tt, gtt);

    Node *att = lookupNode(1, gtt);

    Node *btt = lookupNode(11, gtt);

    //Estimate trust(1,11)
    double trust1_11 = estimateTrust(att, btt, gtt);
    CHECKDOUBLE("Graph estimate trust (1,11)", trust1_11, 0.36);

    //Estimate trust(1,9)
    Node *ctt = lookupNode(9, gtt);
    double trust1_9 = estimateTrust(att, ctt, gtt);
    CHECKDOUBLE("Graph estimate trust (1,9)", trust1_9, 0.72);
}

void stalkersGraphRunMetrics(Graph* gStalkers) {

    printf("Stalkers graph executing metrics:\n");
    degreeDistribution(gStalkers, false);

    int diam = diameter(gStalkers);

    double avgPthLgth = averagePathLength(gStalkers);

    int ccNumber = numberOfCCs(gStalkers);

    int maximumCC = maxCC(gStalkers);

    double dense = density(gStalkers);



}


