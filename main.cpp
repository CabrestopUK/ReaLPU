// original contributer: CabrestopUK
// note "\x9C" has to be used instead of £
#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
using std::string;
using std::map;
using std::vector;
using std::stringstream;

//project includes
#include "account-utils.h"
using accountutils::account;

auto splitString(string input) {
	/* 	Splits a string into a list of "words", separates by spaces 
		Requires a string as an argument only */
	stringstream ss(input); // using stringstream type as it is a simple way to separate words due to the type's methods
	vector<string> split = {};
	string word;
	
	while (ss >> word) { // fundamentally a for loop ish sequence to go through the stringstream by word
		split.push_back(word);
	}
	return split;
}

class term {
	/* 	(no args) CLI instance for ReaLPU */
	
	public:
		map<string, account> account_map; // holds all accounts inside as this is the only scalable way that I could store the object
		string input = "";
		term() {
			std::cout << "ReaLPU ver indev - made by CabrestopUK \n";
		}
		
		void displayAccount(vector<string> split) {
			/*	display the information of a single account 
				only argument is a vector with the split user input (d {accountname})*/
				
			if (split.size() != 2) {std::cout << "invalid syntax - number of args,(d {accountname})\n"; return;}
			if (account_map.count(split[1]) == 0) {std::cout << "not an account!"; return;}
			
			std::cout << "\x9C" << std::fixed << std::setprecision(2) << account_map[split[1]].getValue() << "\n"; 
			for (string ledge : account_map[split[1]].getLedger()) {
				std::cout << ledge << "\n";
			}
		}
		
		void displayAccountList() {
			/* 	(no args) displays all accounts in the account_map with their values */
			
			for (auto acc : account_map) {
				std::cout << acc.first << " \x9C" << std::fixed << std::setprecision(2) << acc.second.getValue() << "\n";
			}
		}
		
		void newAccount(vector<string> split) {
			/* 	creates a new account
				only argument is a vector with the split user input (n {accountname}) */
				
			if (split.size() != 2) {std::cout << "invalid syntax - number of args,(n {accountname})\n"; return;}
			if (account_map.count(split[1]) == 1) {std::cout << "no duplicate accounts!\n"; return;} // it is probably wise to avoid duplicate account names at least for now due to the account_map system
			
			account_map[split[1]];
		}
		
		void removeAccount(vector<string> split) {
			/*	removes an account
				only argument is a vector with the split user input (r {accountname})*/

			if (account_map.count(split[1]) == 0) {std::cout << "not an account!\n"; return;}
			else if (split.size() != 2) {std::cout << "invalid syntax - number of args,(r {accountname})\n"; return;}
			
			account_map.erase(split[1]);
		}
		
		void payment (vector<string> split) {
			/* 	pays an amount into or out of an account
				only argument is a vector with the split user input (p {type} {accountname} {value})*/
			
			float pay_amount;
			
			if (split.size() != 4) {std::cout << "invalid syntax - number of args,(p {type} {accountname} {value}) use i for in and o for out in {type}\n"; return;}
			try{pay_amount = std::stof(split[3]);} catch(std::exception& e) {std::cout << "non numeric\n"; return;}// check if amount is really float by checking if an exception is thrown (kinda ugly way to do it but oh well)
			
			string type = split[1];
			string target_account_name = split[2];
			
			if (account_map.count(target_account_name) == 0) {std::cout << "not an account! \n"; return;}
			
			if (type == "i") {
				account_map[target_account_name].editValue(pay_amount); 
			} 
			else if (type == "o") {
				account_map[target_account_name].editValue(0 - pay_amount);
			}
			
			else {std::cout << "invalid syntax - type,(p {type} {accountname} {value}) use i for in and o for out in {type}\n";}
		}
		
		void transfer (vector<string> split) {
			/*	transfers an amount between accounts
				only argument is a vector with the split user input (t {amount} {payaccount} {recieveaccount})*/
			
			if (split.size() != 4) {std::cout << "invalid syntax - number of args,(t {amount} {payaccount} {recieveaccount})\n";}
			if (account_map.count(split[2]) == 0 and account_map.count(split[3]) == 0) {std::cout << "not an account! \n"; return;}
			
			float transfer_amount;
			try{transfer_amount = std::stof(split[1]);} catch (std::exception& e) {std::cout << "non numeric\n"; return;} // check if amount is really float
			
			account_map[split[2]].editValue(0 - transfer_amount);
			account_map[split[3]].editValue(transfer_amount);
		}
		
		void helpMenu() {
			/*	(no args) display to user all commands that can be used */	
			
			std::cout << "q to quit \n";
			std::cout << "n to make a new account \n";
			std::cout << "r if you want to remove an account \n";
			std::cout << "p to make a payment to or from an account \n";
			std::cout << "t to transfer between accounts \n";
			std::cout << "s to show an accounts info \n";
			std::cout << "d to display all accounts and their balances \n";
		}
		
		void run() {
			/*	(no args) run the cli */
			
			std::cout << "ReaLPU running \n";
			std::cout << "type \"help\" for help \n";
			bool loop = true;
	
			while (loop) {
				std::cout << ">> ";
				getline(std::cin, input);
				
				vector<string> split = splitString(input);
				
				string i = split[0]; // first word or segment of split entails the command used
				
				// commands will be defined separately into their own functions for prettyness and use outside of the designated cli 
				if (i == "q") {loop = false;}
				else if (i == "help") {helpMenu();}
				else if (i == "n") {newAccount(split);}
				else if (i == "r") {removeAccount(split);}
				else if (i == "s") {displayAccount(split);}
				else if (i == "d") {displayAccountList();}
				else if (i == "p") {payment(split);}
				else if (i == "t") {transfer(split);}
				else {std::cout << "that is not a valid input! type \"help\" for help \n";}
			}
		}
};

int main(){
	#ifndef DEBUG // define DEBUG if you want to do any specific testing of only one of the functions
		term running; 
		running.run();
	
		return 0;
	#endif
}
