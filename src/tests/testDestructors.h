/*
 * testDestructors.h
 *
 *  Created on: Nov 20, 2014
 *      Author: athan
 */

#pragma once
#include "../project_main/GraphQueries.h"

void _testDestructors() {
	Graph *g = loadGraph(2, 30);
	delete g;
}
