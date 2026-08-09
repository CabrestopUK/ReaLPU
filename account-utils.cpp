// original contributer: CabrestopUK
#include "account-utils.h"
#include <iostream>
using namespace accountutils;
using std::string;
using std::vector;

account::account(){
	std::cout << "init account" << "\n";
}

float account::getValue(){
	/* 	(no args) returns float value of account */
	
	return value;
}

vector<string> account::getLedger(){
	/* 	(no args) returns ledger(vector) of account transactions */
	
	return ledger;
}

void account::editValue(float change){
	/* 	changes value by float amount 
		requires a float as an argument only*/
		
	value += change;
	// (CabrestopUK) I KNOW WE COULD USE A BETTER LOG FOR THE LEDGER OK, I'M TOO LAZY TO SAVE ANYTHING ELSE - IF YOU WANT IT FORK THE REPO AND MAKE IT AND I WILL HAPPILY STEAL YOUR CODE
	string ledge = "Transaction #[" + std::to_string(transaction_num) + "] - Change \x9C[" + std::to_string(change) + "] New Amount \x9C[" + std::to_string(value) + "]";
	ledger.push_back(ledge);
	transaction_num++;
}