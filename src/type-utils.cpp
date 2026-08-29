//original contributer: CabrestopUK
#include "type-utils.h"

#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
using std::string;
using std::vector;
using std::stringstream;

//
//	typeutils namespace
//
vector<string> typeutils::splitString(string input) {
	/* 	Splits a string into a list of "words", separates by spaces 
		Requires a string as an argument only */
	
	bool splittable = false;
	
	for (auto ch : input) {
		if (!isspace(ch)){
			splittable = true;
		}
	}
	
	if (!splittable) {return {""};}	
	stringstream ss(input); // using stringstream type as it is a simple way to separate words due to the type's methods
	vector<string> split = {};
	string word;
	
	while (ss >> word) { // fundamentally a for loop ish sequence to go through the stringstream by word
		split.push_back(word);
	}
	return split;
}
// The below loop will output the user the correct error and where it came from, as well as how to fix it if they can
void erroroutput(std::string command, std::string errortype) { // Command examples: d, p, n...
	std::cout << command << ": " << errortype << "\n"; // Errortype examples: syntax, filesave, null...
	if (errortype == "syntax") {
		std::cout << "Syntax guide:\n";
	}
}
