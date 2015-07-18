/*
 * PossibleGird.h
 *
 *  Created on: 15 Jul 2015
 *      Author: Hongbo Tian
 */

#ifndef POSSIBLEGIRD_H_
#define POSSIBLEGIRD_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "Grid.h"
#include "Pos.h"

class PossibleGird {
public:
	vector<int> mPossibleGrid[Grid::MAX][Grid::MAX];
	vector<Pos> mUnsolvedPos;
private:
	vector<int> nonRepeat(vector<int> vec);
	void clear();
public:
	PossibleGird();
	void Analysis(Grid grid);
	vector<pair<Pos,int> > crossRef();
	void print();
	string vecToString(vector<int> vec);
};

#endif /* POSSIBLEGIRD_H_ */
