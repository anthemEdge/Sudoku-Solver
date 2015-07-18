//============================================================================
// Name        : Sudoku.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include "Game.h"
using namespace std;

int main() {

	const string PATH = "puzzles/";

	string name;
	cout << "Enter File Name >> "<< flush;
	cin >> name;
	clock_t tStart = clock();
	Game game(PATH+name);
	while(!game.Evaluate()){

	}

	game.printStats();
	cout << "Time Taken: " << (double)(clock()-tStart)/CLOCKS_PER_SEC;


	return 0;
}

