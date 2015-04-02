/*
 * Forum.h
 *
 *  Created on: 8 Jan 2015
 *      Author: Orestis Melkonian
 */

#pragma once
class Forum {
	int forumID;
	int memberNo;
public:
	Forum(int forumID, int memberNo);
	virtual ~Forum();

	int getForumID();
	int getMemberNo();

	void print();
};
