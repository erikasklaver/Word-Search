/*
 * Dictionary.h

 *
 *  Created on: Oct 28, 2015
 *      Author: Erika
 *      WORD SEARCH
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>



using namespace std;

class Dictionary {

public:
	//constructor
	Dictionary();

	//the functions used on dictionary
	bool binarySearch(string word);
	bool isPrefix (string word);

	//gets the number of items in the dictionary
	int size () {return (int)dictionary.size();}

	//gets a word at a particular index of the dictionary
	string at(int i) {return dictionary.at(i);}

private:

	vector <string> dictionary;

};

#endif /* DICTIONARY_H_ */
