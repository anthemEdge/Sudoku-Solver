/*
 * Pos.cpp
 *
 *  Created on: 14 Jul 2015
 *      Author: eva
 */

#include "Pos.h"

Pos::Pos(int row, int col) :
		row(row), col(col) {
}

string Pos::toString(){
	stringstream ss;
	ss << "[";
	ss << row;
	ss <<",";
	ss << col;
	ss << "]";
	return ss.str();
}

