/*
 * Grid.cpp
 *
 *  Created on: 15 Jul 2015
 *      Author: eva
 */

#include "Grid.h"

Grid::Grid() :
		mName("") {
}


void Grid::fill(Pos pos, int value){
	mGrid[pos.row][pos.col] = value;
}

bool Grid::isLegal() {
	bool legal = true;

	// Check for non repeats in rows and columns
	for (int i = 0; i < MAX; i++) {
		vector<int> vRow = getRow(i);
		vector<int> vCol = getCol(i);
		vector<int>::iterator uniqueRow = unique(vRow.begin(), vRow.end());
		vector<int>::iterator uniqueCol = unique(vCol.begin(), vCol.end());
		if (uniqueRow != vRow.end()) {
			legal = false;
		}
		if (uniqueCol != vCol.end()) {
			legal = false;
		}
	}

	// Check for non repeats in sections
	for (int sRow = 0; sRow < 3; sRow++) {
		for (int sCol = 0; sCol < 3; sCol++) {
			// Subsections
			vector<int> vSection = getSection(sRow, sCol);
			vector<int>::iterator uniqueSection = unique(vSection.begin(),
					vSection.end());
			if (uniqueSection != vSection.end()) {
				legal = false;
			}
		}
	}

	return legal;
}

bool Grid::isComplete() {
	bool complete = isLegal();

	// identity vector
	vector<int> identity;
	for (int i = 0; i < MAX; i++) {
		identity.push_back(i + 1);
	}

	// Check for non repeats in rows and columns
	for (int i = 0; i < MAX; i++) {
		vector<int> vRow = getRow(i);
		vector<int> vCol = getCol(i);
		sort(vRow.begin(), vRow.end());
		sort(vCol.begin(), vCol.end());
		if (vRow != identity || vCol != identity) {
			complete = false;
		}
	}

	// Check for non repeats in sections
	for (int sRow = 0; sRow < 3; sRow++) {
		for (int sCol = 0; sCol < 3; sCol++) {
			// Subsections
			vector<int> vSection = getSection(sRow, sCol);
			sort(vSection.begin(), vSection.end());

			if (identity != vSection) {
				complete = false;
			}
		}
	}

	return complete;
}

// Getters for row, column, and sections
vector<int> Grid::getRow(int row) {
	vector<int> vRow;
	for (int col = 0; col < MAX; col++) {
		if (mGrid[row][col] != 0) {
			vRow.push_back(mGrid[row][col]);
		}
	}
	return vRow;
}

vector<int> Grid::getCol(int col) {
	vector<int> vCol;
	for (int row = 0; row < MAX; row++) {
		if (mGrid[row][col] != 0) {
			vCol.push_back(mGrid[row][col]);
		}
	}
	return vCol;
}

vector<int> Grid::getSection(int sRow, int sCol) {
	vector<int> vSection;
	for (int iRow = 0; iRow < 3; iRow++) {
		for (int iCol = 0; iCol < 3; iCol++) {
			int row = sRow * 3 + iRow;
			int col = sCol * 3 + iCol;
			if (mGrid[row][col] != 0) {
				vSection.push_back(mGrid[row][col]);
			}
		}
	}
	return vSection;
}

vector<int> Grid::getSectionByElement(int rRow, int rCol) {

	int sRow = getSectionStart(rRow);
	int sCol = getSectionStart(rCol);

	return getSection(sRow, sCol);
}

vector<Pos> Grid::getUnsolvedPos() {
	vector<Pos> unslovedPos;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (mGrid[row][col] == 0) {
				unslovedPos.push_back(Pos(row, col));
			}
		}
	}
	return unslovedPos;
}

// Read and write to files
bool Grid::read(string path) {
	bool success = true;
	mName = path.c_str();
	string tempLine;
	ifstream myFile3(path.c_str());
	int row = 0;
	if (myFile3.is_open()) {
		while (getline(myFile3, tempLine) && row < MAX) {
			for (int i = 0; i < MAX; i++) {
				mGrid[row][i] = (int) tempLine.at(2 * i) - '0';
			}
			row++;
		}
		myFile3.close();
	} else {
		success = false;
	}
	return success;
}

bool Grid::write() {
	bool success = true;
	string name = "ANS" + mName;
	ofstream file(name.c_str());
	if (file.is_open()) {
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				file << mGrid[i][j];
				file << " ";
			}
			file << "\n";
		}
		file.close();
	} else {
		success = false;
	}
	return success;
}

void Grid::print() {
	for (int row = 0; row < MAX; row++) {
		for (int col = 0; col < MAX; col++) {
			cout << mGrid[row][col] << " " << flush;
		}
		cout << endl;
	}
}

// Misc
int Grid::getSectionStart(int num) {
	int start;
	if (num < 3) {
		start = 0;
	} else if (num < 6) {
		start = 1;
	} else {
		start = 2;
	}
	return start;
}

