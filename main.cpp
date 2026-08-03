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

auto splitString(string input) {
	stringstream ss(input);
	vector<string> split = {};
	string word;
	while (ss >> word) {
		split.push_back(word);
	}
	return split;
}

class account {
	private:
		float value = 0.00;
		//map<string, float> ledger;
		int transaction_num = 0;
	
	public: // using dedicated methods to return and edit values incase of future features
		account(){
			std::cout << "init account" << "\n";
		}
		
		float getValue(){
		  return value;
		}
		
		void editValue(float change){
		  value += change;
		  transaction_num++;
		}
};

class term {
	public:
		map<string, account> account_map;
		string input = "";
		term() {
			std::cout << "ReaLPU ver indev - made by CabrestopUK \n";
		}
		
		void displayAccount(string command) {
			vector<string> split = splitString(command);
			if (split.size() == 2 and account_map.count(split[1]) == 1) {
				std::cout << "\x9C" << std::fixed << std::setprecision(2) << account_map[split[1]].getValue() << "\n";
			}
			else if (account_map.count(split[1]) == 0){
				std::cout << "invalid syntax - {accountname},(d {accountname})\n";
			}
			else {
				std::cout << "invalid syntax - number of args,(d {accountname})\n";
			}
		}
		
		void displayAccountList() {
			for (auto acc : account_map) {
				std::cout << acc.first << " \x9C" << std::fixed << std::setprecision(2) << acc.second.getValue() << "\n";
			}
		}
		
		void newAccount(string command) {
			vector<string> split = splitString(command);
			if (account_map.count(split[1]) == 1) {
				std::cout << "no duplicate accounts!\n";
			}
			else if (split.size() == 2) {
				account_map[split[1]];
			}
			else {
				std::cout << "invalid syntax - number of args,(n {accountname})\n";
			}
		}
		
		void removeAccount(string command) {
			vector<string> split = splitString(command);
			if (account_map.count(split[1]) == 0) {
				std::cout << "not an account!\n";
			}
			else if (split.size() == 2) {
				account_map.erase(split[1]);
			}
			else {
				std::cout << "invalid syntax - number of args,(r {accountname})\n";
			}
		}
		
		void payment (string command) {
			vector<string> split = splitString(command);
			float pay_amount;
			if (split.size() == 4) {
				try{ // check if amount is really float
					pay_amount = std::stof(split[3]);
				}
				catch(std::exception& e) {
					std::cout << "non numeric\n";
					return;
				}
				string type = split[1];
				string target_account_name = split[2];
				
				if (account_map.count(target_account_name) == 0) {
					std::cout << "not an account! \n";
				}
				else if (type == "i") {
					account_map[target_account_name].editValue(pay_amount);
				} 
				else if (type == "o") {
					account_map[target_account_name].editValue(0 - pay_amount);	
				}
				else {
					std::cout << "invalid syntax - type,(p {type} {accountname} {value}) use i for in and o for out in {type}\n";
				}
			}
			else {
				std::cout << "invalid syntax - number of args,(p {type} {accountname} {value}) use i for in and o for out in {type}\n";
			}
		}
		
		void transfer (string command) {
			vector<string> split = splitString(command);
			float transfer_amount;
			
			if (account_map.count(split[2]) == 0 and account_map.count(split[3]) == 0) {
				std::cout << "not an account! \n";
			}
			else if (split.size() == 4) {
				try{ // check if amount is really float
					transfer_amount = std::stof(split[1]);
				}
				catch (std::exception& e) {
					std::cout << "non numeric\n";
					return;
				}
				account_map[split[2]].editValue(0 - transfer_amount);
				account_map[split[3]].editValue(transfer_amount);
			}
			else {
				std::cout << "invalid syntax - number of args,(t {amount} {payaccount} {recieveaccount})\n";
			}
		}
		
		void helpMenu() {
			std::cout << "q to quit \n";
			std::cout << "n to make a new account \n";
			std::cout << "r if you want to remove an account \n";
			std::cout << "p to make a payment to or from an account \n";
			std::cout << "t to transfer between accounts \n";
			std::cout << "s to show an accounts info \n";
			std::cout << "d to display all accounts and their balances \n";
		}
		
		void run() {
			std::cout << "ReaLPU running \n";
			std::cout << "type \"help\" for help \n";
			bool loop = true;
	
			while (loop) {
				std::cout << ">> ";
				getline(std::cin, input);
				
				char i = input[0]; // first character is all we need for the first step, command funcs will handle arguments
				
				// commands will be defined separately into their own functions for prettyness and use outside of the designated cli 
				if (i == 'q') {loop = false;}
				else if (not input.substr(0, 4).compare("help")) {helpMenu();}
				else if (i == 'n') {newAccount(input);}
				else if (i == 'r') {removeAccount(input);}
				else if (i == 's') {displayAccount(input);}
				else if (i == 'd') {displayAccountList();}
				else if (i == 'p') {payment(input);}
				else if (i == 't') {transfer(input);}
				else {std::cout << "that is not a valid input! type \"help\" for help \n";}
			}
		}
};

int main(){
	term running;
	running.run();
	
	return 0;
}
