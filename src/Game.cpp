/*
 * Game.cpp
 *
 *  Created on: 15 Jul 2015
 *      Author: Hongbo Tian
 */

#include "Game.h"

Game::Game(string path) :
		mPath(path), mFin(false), mHasSolution(true), mLinearCycle(0), mCrossRefCycle(
				0), mSearchCycle(0) {
	mSucessInput = mGameGrid.read(path);
	mGamePossibleGrid.Analysis(mGameGrid);
}

bool Game::Evaluate() {

	if (mSucessInput) {
		mGamePossibleGrid.Analysis(mGameGrid);
		bool methodTrigger = true;

		// Linear Constrains Part 1
		// Look for elements with only one possible solution
		vector<Pos>::iterator PosIt;
		for (PosIt = mGamePossibleGrid.mUnsolvedPos.begin();
				PosIt != mGamePossibleGrid.mUnsolvedPos.end(); PosIt++) {
			if (mGamePossibleGrid.mPossibleGrid[PosIt->row][PosIt->col].size()
					== 1) {
				methodTrigger = false;
				mGameGrid.fill(*PosIt,
						mGamePossibleGrid.mPossibleGrid[PosIt->row][PosIt->col].at(
								0));
			}
		}

		// Linear Constrains Part 2
		// Cross-reference rows columns and sections
		// The core of this method is implemented in PossibleGrid
		//returns a array of pairs with Pos and value to fill
		if (methodTrigger) {
			vector<pair<Pos, int> > pairs = mGamePossibleGrid.crossRef();
			vector<pair<Pos, int> >::iterator it;
			for (it = pairs.begin(); it != pairs.end(); it++) {
				methodTrigger = false;
				mGameGrid.fill(it->first, it->second);
			}
		}

		// Calling search method
		if (methodTrigger && !mGameGrid.isComplete()) {
			mFin = search();
		}
		return mGameGrid.isComplete();
	} else {
		cout << "Invalid File Name" << endl;
		return true;
	}
}

bool Game::search() {
	// Depth first search
	cout << "Depth First Search . . . " << endl;
	bool success = true;

	// Queue initialisation
	vector<Grid> searchQueue;
	searchQueue.push_back(mGameGrid);
	while (!searchQueue.operator [](searchQueue.size() - 1).isComplete()
			&& searchQueue.size() > 0) {
		mSearchCycle++;

		Grid currentGrid = searchQueue.at(searchQueue.size() - 1);

		// Test element in queue
		if (currentGrid.isLegal()) {
			PossibleGird possGrid;
			possGrid.Analysis(currentGrid);
			searchQueue.pop_back();
			Pos pos = possGrid.mUnsolvedPos.at(0);
			vector<int> posValues = possGrid.mPossibleGrid[pos.row][pos.col];
			for (vector<int>::iterator it = posValues.begin();
					it != posValues.end(); it++) {
				Grid tempGrid = currentGrid;
				tempGrid.fill(pos, *it);
				searchQueue.push_back(tempGrid);
			}
		} else {
			searchQueue.pop_back();
		}
	}

	if (searchQueue.size() > 0) {
		success = true;
		mGameGrid = searchQueue.at(searchQueue.size() - 1);
	} else {
		mHasSolution = false;
	}
	return success;
}

void Game::printStats() {
	stringstream ss;

	if (mHasSolution) {
		ss << "Solved!!!";
	} else {
		ss << "Has no Solution.";
	}
	if (mSucessInput) {
		cout << ss.str() << endl;
		mGameGrid.print();
	}
}

