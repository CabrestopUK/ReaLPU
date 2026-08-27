// original contributer: CabrestopUK
#include "account-utils.h"
#include "type-utils.h"
#include "csv.h"
using namespace typeutils;

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
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

void account::pushLedger(vector<string> ledger_input){
	/*	Overwrites the account ledger
		requires vector input of strings (the ledger) */
	
	ledger = ledger_input;
}

void account::pushMeta(std::string meta_input) {
	/*	Overwrites the account ledger
		requires vector input of strings (the ledger) */
	
	metadata = meta_input;
}

string account::getMeta() {
	return metadata;
}

void account::editValue(float change){
	/* 	changes value by float amount 
		requires a float as an argument only*/
		
	value += change;
	// (CabrestopUK) I KNOW WE COULD USE A BETTER LOG FOR THE LEDGER OK, I'M TOO LAZY TO SAVE ANYTHING ELSE - IF YOU WANT IT FORK THE REPO AND MAKE IT AND I WILL HAPPILY STEAL YOUR CODE
	
	string ledge = "Transaction:#[" + std::to_string(transaction_num) + "]-Change:\x9C[" + std::to_string(change) + "]-NewAmount:\x9C[" + std::to_string(value) + "]";
	ledger.push_back(ledge);
	transaction_num++;
}
//
//		DEBITACCOUNT CLASS
//
debitAccount::account(){
	std::cout << "init debitAccount" << "\n";
}

float debitAccount::getValue(){
	/* 	(no args) returns float value of debitAccount */
	
	return value;
}

vector<string> debitAccount::getLedger(){
	/* 	(no args) returns ledger(vector) of debitAccount transactions */
	
	return ledger;
}

void debitAccount::pushLedger(vector<string> ledger_input){
	/*	Overwrites the debitAccount ledger
		requires vector input of strings (the ledger) */
	
	ledger = ledger_input;
}

void debitAccount::pushMeta(std::string meta_input) {
	/*	Overwrites the debitAccount ledger
		requires vector input of strings (the ledger) */
	
	metadata = meta_input;
}

string debitAccount::getMeta() {
	return metadata;
}

bool debitAccount::editValue(float change){
	/* 	changes value by float amount returns false if over budget 
		requires a float as an argument only */
	if (value + change < 0) {return false;}

	value += change;
	
	string ledge = "Transaction:#[" + std::to_string(transaction_num) + "]-Change:\x9C[" + std::to_string(change) + "]-NewAmount:\x9C[" + std::to_string(value) + "]";
	ledger.push_back(ledge);
	transaction_num++;
	return true;
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

string workspaces::workspaceclassic::getAccountMeta(string account_name) {
	/* 	Get the metadata (description) of an account
		Requires string account_name as argument */
		
	return account_map[account_name].getMeta();
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
	/*	transfers an amount from one account to another 
		requires argument float amount
		requires argument string account1, account2 */
	
	if (not getAccountStatus(account1)) {return false;}
	if (not getAccountStatus(account2)) {return false;}
	
	account_map[account1].editValue(0 - amount);
	account_map[account2].editValue(amount);
	return true;
}

bool workspaces::workspaceclassic::editAccountMeta(string account_name, string meta) {
	/*	returns the account meta (description) returns true or false depending on if the command is a success
		requires string account_name
		requires string meta */
	
	if (not getAccountStatus(account_name)) {return false;}
	
	account_map[account_name].pushMeta(meta);
	return true;
}

bool workspaces::workspaceclassic::fileDump(string target_file) {
	/*	saves workspace to a file
		requires argument target_file (target file address) */
	
	try {
		csv::writeCsv write(target_file);
	}
	catch (std::runtime_error &e) {
		return false;
	}
	
	csv::writeCsv write(target_file); //(CabrestopUK) inefficient AF i know but it is [00:25] right now and i need sleep :)
	vector<string> line;
	
	for (auto acc : account_map) {
		line.push_back(acc.first);
		line.push_back(std::to_string(acc.second.getValue()));
		line.push_back(acc.second.getMeta());
		for (auto ledge : acc.second.getLedger()) {
			line.push_back(ledge);
		}
		write.writeLine(line);
		line.clear();
	}
	
	return true;
}

bool workspaces::workspaceclassic::fileCollect(string target_file) {
	/*	loads workspace from a file
		requires argument target_file (target file address) */
	
	try {
		csv::readCsv read(target_file);
	}
	catch (std::runtime_error &e) {
		return false;
	}
	
	csv::readCsv read(target_file); //(CabrestopUK) inefficient AF i know but it is [00:25] right now and i need sleep :)
	auto vector_file = read.readFile();
	
	//(the lines of the savefile will be something like this: {name},{value},{ledger1},{ledger2}...)
	for (vector<string> split : vector_file) {
		account_map[split[0]];
		account_map[split[0]].editValue(std::stof(split[1]));
		account_map[split[0]].pushMeta(split[2]);
		vector<string> pushable_ledger = {};
		for (long long unsigned int i = 3; i < split.size(); i++) {
			pushable_ledger.push_back(split[i]);
		}
		account_map[split[0]].pushLedger(pushable_ledger);
	}
	return true;
}
