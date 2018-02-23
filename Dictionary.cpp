/*
 * Dictionary.cpp

 *
 *  Created on: Oct 28, 2015
 *      Author: Erika
 *      WORD SEARCH
 */


#include <iostream>
#include <fstream>
#include "Dictionary.h"

//the constructor
Dictionary::Dictionary() {

	//allows for the dictionary to be read in
	ifstream inputf;
	string filename;

	do {
		// get the file name
		cout << "Enter dictionary file name: ";
		cin >> filename;

		//opens the file
		inputf.open(filename, ios::in);

		if (!inputf.good()) {
			cout << "File " << filename << " could not be opened." << endl;
		}

	//puts each item in the dictionary in a vector of strings
	} while (!inputf.good());

	string str;
	while (inputf >> str) {
		dictionary.push_back(str);
	}

	//shows the number of words in the dictionary
	cout << "Dictionary size is " << dictionary.size() << endl <<endl;

}

//the binary search function
bool Dictionary::binarySearch(string word){

	//the low, high and middle index
	int low = 0;
	int high = dictionary.size();
	int middle = (low+high)/2;

	//the word at the middle index
	string middleWord = dictionary.at(middle);

	//goes through the dictionary
	while (low<= high){

		//returns true if the word we are looking for is the middle word
		if (word == middleWord){
			return true;

		//if the word comes before the middle word, cut the dictionary in half and make the new
		//high the old middle -1 and reset the variables
		}else if(word < middleWord ){
			high = middle - 1;
			middle = (low+high)/2;
			middleWord = dictionary.at(middle);

		//if the word comes before the middle word, cut the dictionary in half and make the new
		//low the old middle +1 and reset the variables
		}else{
			low = middle+1;
			middle = (low+high)/2;
			middleWord = dictionary.at(middle);
		}
	}

	//if we did not find the word in the dictionary
	return false;

}

//the function that determines if the string is a prefix for a word in the dictionary
bool Dictionary:: isPrefix (string word){

		//the low, high and middle index
		int low = 0;
		int high = dictionary.size();
		int middle = (low+high)/2;

		//the size of the word we are checking and the word in the middle of the dictionary
		int wordSize = word.size();
		string middleWord = dictionary.at(middle);

		while (low<= high){
			//returns true if the word is the same as a prefix of the middle word
			if (word == middleWord.substr(0, wordSize)){
				return true;

			//if the prefix of a word comes before the middle word, cut the dictionary in half and make the
			// new high the old middle -1 and reset the variables
			}else if(word < middleWord ){
				high = middle - 1;
				middle = (low+high)/2;
				middleWord = dictionary.at(middle);

			//if the prefix of word comes before the middle word, cut the dictionary in half and make the
			//new low the old middle +1 and reset the variables
			}else{
				low = middle+1;
				middle = (low+high)/2;
				middleWord = dictionary.at(middle);
			}
		}

		//if the word is not a prefix
		return false;

}
