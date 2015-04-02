/*
 * testBucket.h
 *
 *  Created on: 12 ��� 2014
 *      Author: Orestis Melkonian
 */

#pragma once
#include "testBFS.h"
#include "testBBFS.h"
#include "testExtendedBFS.h"
#include "testExtendedBFS2.h"
#include "testDestructors.h"
#include "testMetrics.h"
#include "testQueries.h"
#include "testCommunities.h"
#include "testGirvanNewman.h"
#include "testCliquePercolationMethod.h"

void testBucket();
void testBucketList();

/**
 * SEARCH
 */
void testBFS() {
	_testBFS();
}

void testBBFS(int startID, int endID) {
	_testBBFS(startID, endID);
}

void testExtendedBFS() {
	_testExtendedBFS();
}

void testExtendedBFS2() {
	_testExtendedBFS2();
}

/**
 * MEMORY MANAGEMENT
 */
void testDestructors() {
	_testDestructors();
}

/**
 * METRICS
 */
void testDiameter() {
	_testDiameter();
}

void testAveragePathLength() {
	_testAveragePathLength();
}

void testDensity() {
	_testDensity();
}

void testDegreeDistribution() {
	_testDegreeDistribution();
}

void testClosenessCentrality() {
	_testClosenessCentrality();
}

void testBetweennessCentrality() {
	_testBetweennessCentrality();
}

void testEdgeBetweeness() {
	_testEdgeBetweeness();
}

/**
 * QUERIES
 */
void testQuery1() {
	_testQuery1();
}

void testQuery2() {
	_testQuery2();
}

void testQuery3() {
	_testQuery3();
}

void testQuery4() {
	_testQuery4();
}

/**
 * COMMUNITIES
 */
void testPreprocessing() {
	_testPreprocessing();
}
void testFindCommunities() {
	_testFindCommunities();
}

void testGirvanNewman() {
	_testGirvanNewman();
}

void testCliquePercolationMethod(){
	_testCliquePercolationMethod();
}

