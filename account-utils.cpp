// original contributer: CabrestopUK
#include "account-utils.h"
#include <iostream>
using namespace accountutils;
using std::string;
using std::vector;
//
//		ACCOUNT CLASS
//
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
//
//		WORKSPACECLASSIC CLASS
//
workspaces::workspaceclassic::workspaceclassic() {
	std::cout << "init workspace" << "\n";
}

bool workspaces::workspaceclassic::getAccountStatus(string account_name) {
	/*	Get the status of an accounts existance, True or False 
		Requires string account name as argument */
	
	if (account_map.count(account_name) == 0) {return false;}
	
	return true;
}

float workspaces::workspaceclassic::getAccountValue(string account_name) {
	/*	Get the value of an account
		Requires string account name as argument */
	
	return account_map[account_name].getValue();
}

vector<string> workspaces::workspaceclassic::getAccountLedger(string account_name) {
	/*	Get the ledger(log) of an account
		Requires string account name as argument */
	
	return account_map[account_name].getLedger();
}

vector<string> workspaces::workspaceclassic::getAllAccountNames() {
	/*	(no args) Get a vector of all account names */
	
	vector<string> names;
	for (auto acc : account_map) {
		names.push_back(acc.first);	
	}
	return names;
}

bool workspaces::workspaceclassic::createAccount(string name) {
	/*	Create a new account
		Requires string account name as argument */
	
	if (getAccountStatus(name)) {return false;} // it is probably wise to avoid duplicate account names at least for now due to the account_map system
	
	account_map[name];
	return true;
}

bool workspaces::workspaceclassic::removeAccount(string account_name) {
	/*	Removes an account
		Requires string account name as argument */
	
	if (not getAccountStatus(account_name)) {return false;}
	
	account_map.erase(account_name);
	return true;
}

bool workspaces::workspaceclassic::payment(float amount, string account_name) {
	/*	makes a payment by an amount into an account
		requires argument float amount
		requires argument string account_name */
		
	if (not getAccountStatus(account_name)) {return false;}	
	
	account_map[account_name].editValue(amount); 
	return true;
}

bool workspaces::workspaceclassic::transfer(float amount, string account1, string account2) {
	
	if (not getAccountStatus(account1)) {return false;}
	if (not getAccountStatus(account2)) {return false;}
	
	account_map[account1].editValue(0 - amount);
	account_map[account2].editValue(amount);
	return true;
}