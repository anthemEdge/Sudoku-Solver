/*
 * Grid.h
 *
 *  Created on: 15 Jul 2015
 *      Author: eva
 */

#ifndef GRID_H_
#define GRID_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Pos.h"

using namespace std;

class Grid {
public:
	const static int MAX = 9;
private:
	int mGrid[MAX][MAX];
	string mName;
public:
	Grid();
	vector<int> getRow(int row);
	vector<int> getCol(int col);
	vector<int> getSection(int sRow, int sCol);
	vector<int> getSectionByElement(int rRow, int rCol);
	vector<Pos> getUnsolvedPos();
	void fill(Pos pos, int value);
	bool isLegal();
	bool isComplete();
public:
	bool read(string path);
	bool write();
	void print();
private:
	int getSectionStart(int num);
};
#endif /* GRID_H_ */
