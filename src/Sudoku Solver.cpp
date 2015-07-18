//============================================================================
// Name        : Sudoku.cpp
// Author      : Hongbo Tian
// Description : Main Function
//============================================================================

#include <iostream>
#include <time.h>
#include "Game.h"
using namespace std;

int main() {
	const string PATH = "puzzles/";

	// Taking user inputs
	string name;
	cout << "Enter File Name >> "<< flush;
	cin >> name;

	// Timer
	clock_t tStart = clock();

	// Initialise Game & Game Loop
	Game game(PATH+name);
	while(!game.Evaluate()){
	}

	// Print solution and time
	game.printStats();
	cout << "Time Taken: " << (double)(clock()-tStart)/CLOCKS_PER_SEC;

	return 0;
}

