#pragma once
#include "../properties/Properties.h"
#include "../Node.h"
#include "../Edge.h"
#include "../BucketItem.h"
#include "../BucketList.h"
#include "../Graph.h"
#include "../search/ResultSet.h"

int main_part1();
int main_part2();
int main_part3();

struct pairr {
	int ID; // the id of a node
	int distance; //the distance from the node
};
typedef struct pairr Pairr;

/*Help functions for test main*/
Properties* createProperties(int number);
void setStringProperty(char* property, int index, Properties* p);
void setIntegerProperty(int property, int index, Properties* p);
void setDoubleProperty(double property, int index, Properties* p);
char* getStringProperty(int index, Properties* p);
int getIntegerProperty(int index, Properties* p);
double getDoubleProperty(int index, Properties* p);
Node* createNode(int id, Properties* p);
Edge* createEdge(int startID, int endID, Properties* p);

/*Functions for implementation of part 1*/
Graph* createGraph(int m, int c);
int destroyGraph(Graph* g);
int insertNode(Node* n, Graph* g);
int insertEdge(int startID, Edge* e, Graph* g);
Node* lookupNode(int id, Graph* g);
int reachNode1(int startID, int endID, Graph* g);
ResultSet* reachNodeN(int startID, Graph* g);
Pair* next(ResultSet* resultSet);
