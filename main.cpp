// original contributer: CabrestopUK
// note "\x9C" has to be used instead of £
#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <vector>
using std::string;
using std::map;
using std::vector;

//project includes
#include "account-utils.h"
using accountutils::account;
using namespace accountutils::workspaces;
#include "type-utils.h"
using namespace typeutils;

class term {
	/* 	(no args) CLI instance for ReaLPU */
	
	public:
		string input = "";
		workspaceclassic ws;
		
		term() {
			std::cout << "ReaLPU ver indev - Developed by CabrestopUK and Troy.\n";
		}
		
		void displayAccount(vector<string> split) {
			/*	display the information of a single account 
				only argument is a vector with the split user input (d {accountname})*/
			
			if (split.size() != 2) {std::cout << "Invalid syntax - number of args,(d {accountname})\n"; return;}
			
			string account_name = split[1];
			if (not ws.getAccountStatus(account_name)) {std::cout << "Not an account! \n"; return;}
		
			std::cout << "\x9C" << std::fixed << std::setprecision(2) << ws.getAccountValue(account_name) << "\n"; 
			for (string ledge : ws.getAccountLedger(account_name)) {
				std::cout << ledge << "\n";
			}
		}
		
		void displayAccountList() {
			/* 	(no args) displays all accounts in the account_map with their values */
			
			for (string name : ws.getAllAccountNames()) {
				std::cout << name << " \x9C" << std::fixed << std::setprecision(2) << ws.getAccountValue(name) << "\n";
			}
		}
		
		void newAccount(vector<string> split) {
			/* 	creates a new account
				only argument is a vector with the split user input (n {accountname}) */
				
			if (split.size() != 2) {std::cout << "Invalid syntax - number of args,(n {accountname})\n"; return;}
			
			string name = split[1];
			
			bool status = ws.createAccount(name);
			if (not status) {std::cout << "No duplicate accounts!\n";} 
		}
		
		void removeAccount(vector<string> split) {
			/*	removes an account
				only argument is a vector with the split user input (r {accountname})*/
			
			if (split.size() != 2) {std::cout << "Invalid syntax - number of args,(r {accountname})\n"; return;}
			string name = split[1];
			
			bool status = ws.removeAccount(name);
			if (not status) {std::cout << "Not an account!\n"; return;}
		}
		
		void payment (vector<string> split) {
			/* 	pays an amount into or out of an account
				only argument is a vector with the split user input (p {type} {accountname} {value})*/
			
			float pay_amount;
			
			if (split.size() != 4) {std::cout << "Invalid syntax - number of args,(p {type} {accountname} {value}) use i for in and o for out in {type}\n"; return;}
			try{pay_amount = std::stof(split[3]);} catch(std::exception& e) {std::cout << "Non numeric\n"; return;}// check if amount is really float by checking if an exception is thrown (kinda ugly way to do it but oh well)
			
			string type = split[1];
			string target_account_name = split[2];
			
			bool status;
			
			if (type == "i") {
				status = ws.payment(pay_amount, target_account_name);
			} 
			else if (type == "o") {
				status = ws.payment(0 - pay_amount, target_account_name);
			}
			else {std::cout << "Invalid syntax - type,(p {type} {accountname} {value}) use i for in and o for out in {type}\n"; return;}
			
			if (not status) {std::cout << "Not an account! \n"; return;}
		}
		
		void transfer (vector<string> split) {
			/*	transfers an amount between accounts
				only argument is a vector with the split user input (t {amount} {payaccount} {recieveaccount})*/
			
			if (split.size() != 4) {std::cout << "Invalid syntax - number of args,(t {amount} {payaccount} {recieveaccount})\n"; return;}
			
			float transfer_amount;
			try{transfer_amount = std::stof(split[1]);} catch (std::exception& e) {std::cout << "non numeric\n"; return;} // check if amount is really float
			
			bool status = ws.transfer(transfer_amount, split[2], split[3]);
			
			if (not status) {std::cout << "Not an account! \n"; return;}
		}
		
		void save(vector<string> split) {
			/*	saves the workspace to a file
				only argument is a vector with the split user input (o {file_name})*/
			
			if (split.size() != 2) {std::cout << "Invalid syntax - number of args,(o {filename})" << "\n"; return;}
			bool status = ws.fileDump(split[1]);
			if (!status) {std::cout << "File did not open..." << "\n"; return;}
			std::cout << "saved! \n";
		}
		
		void load(vector<string> split) {
			/*	saves the workspace to a file
				only argument is a vector with the split user input (i {file_name})*/
			
			if (split.size() != 2) {std::cout << "Invalid syntax - number of args,(i {filename})" << "\n"; return;}
			bool status = ws.fileCollect(split[1]);
			if (!status) {std::cout << "File did not open..." << "\n"; return;}
			std::cout << "Loaded! \n";
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
			std::cout << "o to save the workspace to a file \n";
			std::cout << "i to load a workspace from a file \n";
		}
		
		void run() {
			/*	(no args) run the cli */
			
			std::cout << "ReaLPU running \n";
			std::cout << "Type \"help\" for help \n";
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
				else if (i == "i") {load(split);}
				else if (i == "o") {save(split);}
				else {std::cout << "That is not a valid input! type \"help\" for help \n";}
			}
		}
};

int main(){
	#ifndef DEBUG // define DEBUG if you want to do any specific testing of something
		term running; 
		running.run();
	
		return 0;
	#endif
}
