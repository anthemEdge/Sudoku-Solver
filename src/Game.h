/*
 * Game.h
 *
 *  Created on: 15 Jul 2015
 *      Author: eva
 */

#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <vector>
#include "PossibleGird.h"
#include "Grid.h"
#include "Pos.h"

using namespace std;

class Game {
private:
	string mPath;
	bool mFin;
	bool mHasSolution;
	bool mSucessInput;
	Grid mGameGrid;
	PossibleGird mGamePossibleGrid;
	int mLinearCycle;
	int mCrossRefCycle;
	int mSearchCycle;
	bool search();

public:
	Game(string path);
	bool Evaluate();
	void printStats();
};

#endif /* GAME_H_ */
