/*
 * Puzzle.h
 *
 *  Created on: Oct 28, 2015
 *      Author: Erika
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"


class Puzzle {

public:

	//the constructor
	Puzzle();

	//each solve method
	void naiveSolve();
	void directSolve();
	void directPreSolve();


private:

	//the largest puzzle can be 30 by 30
	static const int MAX_ROWS = 30;
	static const int MAX_COLUMNS = 30;

	//the number of columns and rows, the smallest word length, the dictionary
	//and an array with the letters in the puzzle
	int numRows;
	int numCols;
	int minWordLength;
	Dictionary dictionary;
	char theBoard[MAX_ROWS][MAX_COLUMNS];

};

#endif /* PUZZLE_H_ */
