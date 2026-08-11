//original contributer: CabrestopUK
#include "type-utils.h"

#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
using std::string;
using std::vector;
using std::stringstream;

vector<string> typeutils::splitString(string input) {
	/* 	Splits a string into a list of "words", separates by spaces 
		Requires a string as an argument only */
	if (input == "") {return {""};}
	else if (input != "q" && input != "n" && input != "r" && input != "p" && input != "t" && input != "s" && input != "d" && input != "\n" && input != "ver") {std::cout << "That is not a valid input! type \"help\" for help \n";}
	stringstream ss(input); // using stringstream type as it is a simple way to separate words due to the type's methods
	vector<string> split = {};
	string word;
	
	while (ss >> word) { // fundamentally a for loop ish sequence to go through the stringstream by word
		split.push_back(word);
	}
	return split;
}
