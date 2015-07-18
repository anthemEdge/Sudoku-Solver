/*
 * Pos.h
 *
 *  Created on: 14 Jul 2015
 *      Author: eva
 */

#ifndef POS_H_
#define POS_H_

#include <sstream>
using namespace std;

struct Pos {
	int row;
	int col;
	Pos(int row, int col);
	string toString();
};

#endif /* POS_H_ */
