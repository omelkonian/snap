/*
 * test.cpp
 *
 *      Author: Orestis Melkonian
 */
#pragma GCC diagnostic ignored "-Wwrite-strings"

#ifdef __CYGWIN__
#define OS_WINDOWS
#endif

#include <iostream>
#include <assert.h>

#include "project_main/GraphLib.h"
#include "project_main/defines.h"

#include "Node.h"
#include "Edge.h"
#include "list/ListItem.h"
#include "list/EdgeListItem.h"
#include "list/BucketListItem.h"
#include "list/List.h"
#include "list/Queue.h"
#include "properties/Properties.h"

#include "Bucket.h"
#include "BucketItem.h"

#include "tests/tests.h"

using namespace std;

int main() {
	// TEST FLAGS (Set to false if you want test to be run)

	bool testDestructorsFlag = false;

	bool testExtendedBFSFlag = false;
	bool testExtendedBFS2Flag = false;

	bool testMetricsFlag = false;
	bool testEdgeBetweenessFlag = false;

	bool testQueriesFlag = false;

	bool testPreprocessingFlag = false;

	bool testGirvanNewmanFlag = false;

	bool testCliquePercolationMethodFlag = false;

	bool projectMainFlag = true;

	if (testPreprocessingFlag) {
		cout << "#######################Testing Preprocessing#######################" << endl;
		testPreprocessing();
		cout << "#######################Testing FindCommunities#######################" << endl;
//		testFindCommunities();
		cout << "##############################################################" << endl;
	}

	if (testGirvanNewmanFlag) {
		cout << "#######################Testing GirvanNewman#######################" << endl;
		testGirvanNewman();
		cout << "##############################################################" << endl;
	}

	if (testCliquePercolationMethodFlag) {
		cout << "#######################Testing CPM#######################" << endl;
		testCliquePercolationMethod();
		cout << "##############################################################" << endl;
	}

	if (projectMainFlag) {
		cout << "#######################Testing myMain#######################" << endl;
		main_part1();
		main_part2();
		main_part3();
		cout << "##############################################################" << endl;
	}

	if (testQueriesFlag) {
		cout << "#######################Testing Queries#######################" << endl;
		testQuery1();
		testQuery2();
		testQuery3();
		testQuery4();
		cout << "##############################################################" << endl;
	}

	if (testMetricsFlag) {
		cout << "#######################Testing Metrics#######################" << endl;
		testDensity();
		testDegreeDistribution();
		testDiameter();
		testAveragePathLength();
		testClosenessCentrality();
		testBetweennessCentrality();
		cout << "##############################################################" << endl;
	}

	if (testEdgeBetweenessFlag) {
		cout << "#######################Testing Edge Betweeness#######################" << endl;
		testEdgeBetweeness();
		cout << "##############################################################" << endl;
	}

	if (testDestructorsFlag) {
		cout << "#######################Testing Destructors#######################" << endl;
		testDestructors();
		cout << "##############################################################" << endl;
	}

	if (testExtendedBFSFlag) {
		cout << "#######################Testing ExtendedBFS#######################" << endl;
		testExtendedBFS();
		cout << "##############################################################" << endl;
	}

	if (testExtendedBFS2Flag) {
		cout << "#######################Testing ExtendedBFS2#######################" << endl;
		testExtendedBFS2();
		cout << "##############################################################" << endl;
	}

	cout << "\n#######################END OF TESTS#######################" << endl;

	return 0;
}

