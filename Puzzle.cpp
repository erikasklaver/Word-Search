/*
 * Puzzle.cpp

 *
 *  Created on: Oct 28, 2015
 *      Author: Erika
 *      WORD SEARCH
 */



#include "Puzzle.h"
#include <iostream>
#include <fstream>
#include "Dictionary.h"

using namespace std;

//the constructor
Puzzle::Puzzle() {

	//allows for the puzzle to be read in
	string fileName;
	ifstream puzzleStream;

	//read in the puzzle file name

	do {
		cout << "Enter puzzle file name:";
		cin >> fileName;
		puzzleStream.open(fileName.c_str(), ios::in);

	} while (!puzzleStream.good());  //keep trying until this works

	string line;
	//make sure the file has some stuff in it
	if (!getline(puzzleStream, line)) {
		cerr << "Error: puzzle file is empty" << endl;
		numRows = 0;
		numCols = 0;
		return;
	}

	//put the first puzzle line in theBoard
	numCols = line.size();
	for (int i = 0; i < numCols; i++) {
		theBoard[0][i] = tolower(line.at(i));
	}

	//put the rest of the puzzle lines in theBoard
	for (numRows = 1; getline(puzzleStream, line); numRows++) {

		//make sure it's rectangular
		if (line.size() != numCols) {
			cerr << "Error: puzzle is not rectangular" << endl;
			numRows = 0;
			numCols = 0;
			return;
		}
		//put this puzzle line in theBoard
		for (int i = 0; i < numCols; i++) {
			theBoard[numRows][i] = tolower(line.at(i));
		}
	}

	cout << "Read puzzle with " << numRows << " rows and " << numCols
			<< " columns" << endl << endl;

	//prints out the puzzle with numbers to show location of each letter
	for (int k = 0; k< numCols; k++){
		int kten = k-10;
		if (k == numCols -1){
			cout << kten << endl;
		}else if(k == 0){
			cout << "  "<< k << " ";
		}else{

			if (k <10){
		cout << k << " ";
			}else{
				cout << kten << " ";
			}
		}
	}

	//prints out the puzzle with numbers to show location of each letter
	for (int i = 0; i < numRows; i++) {
		int iten = i-10;

		if(i<10){
			cout << i << " ";
		}else{
			cout << iten << " ";
		}

		for (int j = 0; j < numCols; j++) {

			char c = toupper(theBoard[i][j]);
			if (j == numCols - 1) {

				cout << c << endl;
			} else {
				cout << c << " ";
			}
		}
	}

	cout << endl;

	//reads in the minimum word length inputed by the user
	cout << "Minimum word length: ";
	cin >> minWordLength;
	cout << endl;

	//runs and times the naive approach
	cout << "Using naive approach:"<< endl;
	double start, end, seconds;
	start = clock();
	naiveSolve();
	end = clock();
	seconds = (end -start)/ CLOCKS_PER_SEC;

	cout << "Solution time: " << seconds << " seconds" <<endl <<endl;

	//runs and times the direct approach
	cout << "Using direct approach:"<< endl;
	double start2, end2, seconds2;
	start2 = clock();
	directSolve();
	end2 = clock();
	seconds2 = (end2 -start2)/ CLOCKS_PER_SEC;

	cout << "Solution time: " << seconds2 << " seconds" <<endl<< endl;

	//runs and times the direct approach with prefixes
	cout << "Using direct approach with prefixes:"<< endl;
	double start3, end3, seconds3;
	start3 = clock();
	directPreSolve();
	end3 = clock();
	seconds3 = (end3 -start3)/ CLOCKS_PER_SEC;

	cout << "Solution time: " << seconds3 << " seconds" <<endl<< endl;

}

//the naive approach function
void Puzzle:: naiveSolve(){

	//holds the number of words found in total
	int numWordsFound = 0;

	//goes through every word in the dictionary and sees if each word is on the puzzle
	for (int i = 0; i < dictionary.size(); i++) {
		string word = dictionary.at(i);

		//will only run if the word is longer than the minimum word length inputed
		if (word.size() >= minWordLength) {


			//goes through every row, column and direction
			for (int row = 0; row < numRows; row++) {
				for (int col = 0; col < numCols; col++) {

					for (int d = 0; d < 8; d++) {

						string puzzleStr = "";
						char f = theBoard[row][col];
						puzzleStr = puzzleStr +f;
						int endRow = 0;
						int endCol = 0;

						//if the first letter is not the same, break from the loop
						if (f != word.at(0)){
							break;
						}

						//checking the east direction
						if (d == 0){

							//this will only check if there is enough room on the board
							if (col <= numCols - word.size()) {
								for (int j = 1; j < word.size();j++) {

									char c = theBoard[row][col+j];

									if (c != word.at(j)){
										break;
									}

									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row;
										endCol = col+j;
									}
								}
							}
						}

						//checking the southeast direction
						if (d == 1){

							//this will only check if there is enough room on the board
							if (row <= numRows - word.size() && col <= numCols - word.size()){
								for (int j = 1; j < word.size();j++) {
									char c = theBoard[row+j][col+j];

									if (c != word.at(j)){
										break;
									}

									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row+j;
										endCol = col+j;
									}
								}
							}
						}

						//checking the south direction
						if (d == 2){

							//this will only check if there is enough room on the board
							if (row <= numRows - word.size()) {
								for (int j = 1; j < word.size();j++) {
									char c = theBoard[row + j][col];

									if (c != word.at(j)){
										break;
									}

									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row+j;
										endCol = col;
									}
								}
							}
						}

						//checking the southwest direction
						if(d == 3){

							//this will only check if there is enough room on the board
							if (row <= numRows - word.size() && col >= word.size()-1) {
								for (int j = 1; j < word.size();j++) {
									char c = theBoard[row + j][col-j];

									if (c != word.at(j)){
										break;
									}
									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row+j;
										endCol = col-j;
									}
								}
							}
						}

						//checking the west direction
						if(d == 4){

							//this will only check if there is enough room on the board
							if (col >= word.size()-1) {
								for (int j = 1; j < word.size();j++) {
									char c = theBoard[row][col-j];

									if (c != word.at(j)){
										break;
									}

									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row;
										endCol = col-j;
									}
								}
							}
						}

						//checking the northwest direction
						if(d == 5){

							//this will only check if there is enough room on the board
							if (row >= word.size()-1 && col >= word.size()-1) {
								for (int j = 1; j < word.size(); j++) {
									char c = theBoard[row - j][col - j];

									if (c != word.at(j)){
										break;
									}

									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row-j;
										endCol = col-j;
									}
								}
							}
						}

						//checking the north direction
						if(d == 6){

							//this will only check if there is enough room on the board
							if (row >= word.size()-1) {
								for (int j = 1; j < word.size();j++) {
									char c = theBoard[row-j][col];

									if (c != word.at(j)){
										break;
									}

									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row-j;
										endCol = col;
									}
								}
							}
						}

						//checking the northeast direction
						if(d == 7){

							//this will only check if there is enough room on the board
							if (row >= word.size()-1 && col <= numCols - word.size()) {
								for (int j = 1; j < word.size();j++) {
									char c = theBoard[row - j][col + j];

									if (c != word.at(j)){
										break;
									}

									puzzleStr = puzzleStr + c;

									//remembers the location of the last letter of the word
									if (j == word.size()-1){
										endRow = row-j;
										endCol = col+j;
									}
								}
							}
						}


						//if the word is on the puzzle it will print out with it's location
						if (word == puzzleStr) {
							numWordsFound++;
							cout << "Found \"" << puzzleStr <<"\" at ("<< row << ","<< col<< ") to ("<<
									endRow << ","<< endCol<< ")" <<endl;
						}
					}
				}
			}
		}
	}

	cout << "Found " << numWordsFound << " matches." <<endl;

}

//the direct approach function
void Puzzle :: directSolve(){

	//integers remembering the number of matches and the end row/column of a word found and the
	//longest word in the dictionary
	int numWordsFound = 0;
	int endRow = 0;
	int endCol = 0;
	int longWordSize = 0;

	//finds the length of the longest word in the dictionary
	for (int j = 0; j<dictionary.size(); j++){
		string currentWord = dictionary.at(j);
		if(currentWord.size()>longWordSize){
			longWordSize= currentWord.size();
		}
	}

	//for every row, column and direction check each word length from the minimum word length to the
	//longest length in the dictionary and see if those words from the puzzle are in the dictionary
	for (int row = 0; row < numRows; row++){
		for (int col = 0; col <numCols; col++){
			for (int d = 0; d<8; d++){

				//checking in the east direction
				if (d == 0){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (col <= numCols - len){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row][col+i];

								if (i == len-1){
									endRow = row;
									endCol = col+i;
								}
							}

						//checks to see if the word on the puzzle is in the dictionary and if it is print
						if (dictionary.binarySearch(puzzleString)){
							numWordsFound++;
							cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("<<
									endRow << ","<< endCol<< ")" <<endl;
							}
						}
					}
				}

				//checking in the southeast direction
				if (d == 1){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row <= numRows - len && col <= numCols - len){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row+i][col+i];

								if (i == len-1){
									endRow = row+i;
									endCol = col+i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \" " << puzzleString <<" \" at ("<< row << ","<< col<< ") to ("
										<<endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking in the south direction
				if (d == 2){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row <= numRows - len){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row+i][col];

								if (i == len-1){
									endRow = row+i;
									endCol = col;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking in the southwest direction
				if (d == 3){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row <= numRows - len && col >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row+i][col-i];

								if (i == len-1){
									endRow = row+i;
									endCol = col-i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking in the west direction
				if (d == 4){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (col >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row][col-i];

								if (i == len-1){
									endRow = row;
									endCol = col-i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}


				//checking in the northwest direction
				if (d == 5){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row >= len-1 && col >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row-i][col-i];

								if (i == len-1){
									endRow = row-i;
									endCol = col-i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking in the north direction
				if (d == 6){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row-i][col];

								if (i == len-1){
									endRow = row-i;
									endCol = col;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking in the northeast direction
				if (d == 7){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row >= len-1 && col <= numCols - len){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString +  theBoard[row-i][col+i];

								if (i == len-1){
									endRow = row-i;
									endCol = col+i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}
			}
		}
	}

	cout << "Found " << numWordsFound << " matches." <<endl;

}

//the direct approach with prefixes function
void Puzzle:: directPreSolve(){

	//integers remembering the number of matches and the end row/column of a word found and the
    //longest word in the dictionary
	int numWordsFound = 0;
	int endRow = 0;
	int endCol = 0;
	int longWordSize = 0;

	//finds the length of the longest word in the dictionary
	for (int j = 0; j<dictionary.size(); j++){
		string currentWord = dictionary.at(j);
		if(currentWord.size()>longWordSize){
			longWordSize= currentWord.size();
		}
	}

	//for every row, column and direction check each word length from the minimum word length to the
	//longest length in the dictionary and see if those words from the puzzle are in the dictionary
	for (int row = 0; row < numRows; row++){
		for (int col = 0; col <numCols; col++){
			for (int d = 0; d<8; d++){

				//checking the east direction
				if (d == 0){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (col <= numCols - len){
							for (int i = 0; i<len; i++){

								puzzleString = puzzleString + theBoard[row][col+i];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;

									break;
								}


								if (i == len-1){
									endRow = row;
									endCol = col+i;
								}
							}

						//checks to see if the word on the puzzle is in the dictionary and if it is print
						if (dictionary.binarySearch(puzzleString)){
							numWordsFound++;
							cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
									<< endRow << ","<< endCol<< ")" <<endl;
							}
						}
					}
				}

				//checking the southeast direction
				if (d == 1){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row <= numRows - len && col <= numCols - len){
							for (int i = 0; i<len; i++){

								puzzleString = puzzleString + theBoard[row+i][col+i];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;
									break;
								}


								if (i == len-1){
									endRow = row+i;
									endCol = col+i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking the south direction
				if (d == 2){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row <= numRows - len){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row+i][col];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;
									break;
								}

								if (i == len-1){
									endRow = row+i;
									endCol = col;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking the southwest direction
				if (d == 3){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row <= numRows - len && col >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row+i][col-i];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;
									break;
								}

								if (i == len-1){
									endRow = row+i;
									endCol = col-i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking the west direction
				if (d == 4){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (col >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row][col-i];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;
									break;
								}

								if (i == len-1){
									endRow = row;
									endCol = col-i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking the northwest direction
				if (d == 5){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row >= len-1 && col >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row-i][col-i];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;
									break;
								}

								if (i == len-1){
									endRow = row-i;
									endCol = col-i;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking the north direction
				if (d == 6){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row >= len-1){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString + theBoard[row-i][col];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;
									break;
								}

								if (i == len-1){
									endRow = row-i;
									endCol = col;
								}
							}

							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}

				//checking the northeast direction
				if (d == 7){
					for (int len = minWordLength; len <longWordSize; len++){
						string puzzleString = "";
						if (row >= len-1 && col <= numCols - len){
							for (int i = 0; i<len; i++){
								puzzleString = puzzleString +  theBoard[row-i][col+i];

								//makes sure that the string is a prefix of a word in the dictionary
								if (!dictionary.isPrefix(puzzleString)){
									len = longWordSize;
									break;
								}

								if (i == len-1){
									endRow = row-i;
									endCol = col+i;
								}
							}



							//checks to see if the word on the puzzle is in the dictionary and if it is print
							if (dictionary.binarySearch(puzzleString)){
								numWordsFound++;
								cout << "Found \"" << puzzleString <<"\" at ("<< row << ","<< col<< ") to ("
										<< endRow << ","<< endCol<< ")" <<endl;

							}
						}
					}
				}
			}
		}
	}

	cout << "Found " << numWordsFound << " matches." <<endl;

}

