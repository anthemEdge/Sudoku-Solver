/*
 * PossibleGird.cpp
 *
 *  Created on: 15 Jul 2015
 *      Author: Hongbo Tian
 */

#include "PossibleGird.h"

PossibleGird::PossibleGird() {
}

void PossibleGird::Analysis(Grid grid) {

	clear();
	// Get unsolved positions from grid
	mUnsolvedPos = grid.getUnsolvedPos();
	vector<Pos>::iterator it;

	for (it = mUnsolvedPos.begin(); it != mUnsolvedPos.end(); it++) {
		vector<int> invalid;
		// Collect invalid numbers
		vector<int> invalidRow = grid.getRow(it->row);
		vector<int> invalidCol = grid.getCol(it->col);
		vector<int> invalidSec = grid.getSectionByElement(it->row, it->col);
		invalid.insert(invalid.end(), invalidRow.begin(), invalidRow.end());
		invalid.insert(invalid.end(), invalidCol.begin(), invalidCol.end());
		invalid.insert(invalid.end(), invalidSec.begin(), invalidSec.end());

		// Append identity to them
		for (int i = 0; i < Grid::MAX; i++) {
			invalid.push_back(i + 1);
		}
		// Keeping only the non-repeating values
		mPossibleGrid[it->row][it->col] = nonRepeat(invalid);
	}
}

vector<pair<Pos, int> > PossibleGird::crossRef() {
	vector<pair<Pos, int> > pairs;

	for (int i = 0; i < Grid::MAX; i++) {
		vector<int> rowCollection;
		vector<int> colCollection;
		multimap<int, Pos> rowMap;
		multimap<int, Pos> colMap;

		// Setting up possible arrays and map for rows and columns
		for (int j = 0; j < Grid::MAX; j++) {
			// Same row
			if (mPossibleGrid[i][j].size() > 0) {
				// same row
				// Collect the possible values
				vector<int> possibleRow = mPossibleGrid[i][j];
				rowCollection.insert(rowCollection.end(), possibleRow.begin(),
						possibleRow.end());
				// add to lookup map
				vector<int>::iterator it;
				for (it = possibleRow.begin(); it != possibleRow.end(); it++) {
					rowMap.insert(make_pair(*it, Pos(i, j)));
				}
			}
			// Same column
			if (mPossibleGrid[j][i].size() > 0) {
				// Collect the possible values
				vector<int> possibleCol = mPossibleGrid[j][i];
				colCollection.insert(colCollection.end(), possibleCol.begin(),
						possibleCol.end());
				// Add to lookup map
				vector<int>::iterator it;
				for (it = possibleCol.begin(); it != possibleCol.end(); it++) {
					colMap.insert(make_pair(*it, Pos(j, i)));
				}
			}
		}

		// Find unique if there is a unique non-repeating value
		vector<int> nonRepeatingRow = nonRepeat(rowCollection);
		vector<int> nonRepeatingCol = nonRepeat(colCollection);
		// Add the pos and value of that element to the returning vector

		vector<int>::iterator rowIt, colIt;
		for (rowIt = nonRepeatingRow.begin(); rowIt != nonRepeatingRow.end();
				rowIt++) {
			pairs.push_back(make_pair(rowMap.find(*rowIt)->second, *rowIt));
		}

		for (colIt = nonRepeatingCol.begin(); colIt != nonRepeatingCol.end();
				colIt++) {
			pairs.push_back(make_pair(colMap.find(*colIt)->second, *colIt));
		}
	}

	// cross reference using sections
	for (int sRow = 0; sRow < 3; sRow++) {
		for (int sCol = 0; sCol < 3; sCol++) {
			// Section
			vector<int> possibleSec;
			multimap<int, Pos> secMap;
			for (int iRow = 0; iRow < 3; iRow++) {
				for (int iCol = 0; iCol < 3; iCol++) {
					int row = sRow * 3 + iRow;
					int col = sCol * 3 + iCol;
					if (mPossibleGrid[row][col].size() > 0) {
						// Extract the possible values
						vector<int> possible = mPossibleGrid[row][col];
						// Add the all the possible values in that section
						possibleSec.insert(possibleSec.end(), possible.begin(),
								possible.end());
						// Construct the Lookup map
						for (vector<int>::iterator it = possible.begin();
								it != possible.end(); it++) {
							secMap.insert(make_pair(*it, Pos(row, col)));
						}
					}
				}
			}
			// Section Code
			vector<int> nonRepeatingSec = nonRepeat(possibleSec);
			for (vector<int>::iterator it = nonRepeatingSec.begin();
					it != nonRepeatingSec.end(); it++) {
				pairs.push_back(make_pair(secMap.find(*it)->second, *it));
			}
		}
	}

	return pairs;
}

vector<int> PossibleGird::nonRepeat(vector<int> vec) {
	sort(vec.begin(), vec.end());
	vec.push_back(0);
	int buffer = vec.at(0);
	int counter = 0;
	vector<int> nonRepeat;

	for (vector<int>::iterator it = vec.begin() + 1; it != vec.end(); it++) {
		if (*it != buffer && counter == 0) {
			nonRepeat.push_back(buffer);
			counter = 0;
			buffer = *it;
		} else if (*it != buffer) {
			buffer = *it;
			counter = 0;
		} else {
			counter++;
		}
	}
	return nonRepeat;
}

void PossibleGird::print() {
	vector<Pos>::iterator it;
	for (it = mUnsolvedPos.begin(); it != mUnsolvedPos.end(); it++) {
		cout << it->toString() << flush;
		cout << " : " << flush;
		cout << vecToString(mPossibleGrid[it->row][it->col]) << endl;
	}
}

void PossibleGird::clear() {
	for (int i = 0; i < Grid::MAX; i++) {
		for (int j = 0; j < Grid::MAX; j++) {
			vector<int> dummy;
			mPossibleGrid[i][j] = dummy;
		}
	}
}

string PossibleGird::vecToString(vector<int> vec) {
	stringstream ss;
	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		ss << *it;
		ss << " ";
	}
	return ss.str();
}
