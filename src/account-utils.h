// original contributer: CabrestopUK
#ifndef ACCOUNT_UTILS
#define ACCOUNT_UTILS

#include <string>
#include <vector>
#include <map>

namespace accountutils {
	/*	ALL THE ACCOUNT TYPES AND THEIR METHODS */
	
	class account {
		/*	(no args) basic account object - stores account value and ledger of all transactions */
		
		private: //variables kept in private for personal sanity :) - also incase of any features of specific accounts that require limits on changing value
			float value = 0.00;
			std::vector<std::string> ledger = {};
			std::string metadata = "";
			int transaction_num = 0; // primarily utilised for ledger
			
		public:
			account();
			float getValue();
			std::vector<std::string> getLedger();
			void pushLedger(std::vector<std::string> ledger_input);
			void pushMeta(std::string);
			std::string getMeta();
			void editValue(float change);
	};
	
	namespace workspaces {
		/*	CONTAINS WORKSPACES FOR INTERACTING WITH ACCOUNTS */
		
		class workspaceclassic {
			/* 	(no args) basic workspace which can create accounts, delete, make payments into and out of them, and get their values*/
			
			private:
				std::map<std::string, account> account_map; // holds all accounts inside as this is the only scalable way that I could store the object
			public:
				workspaceclassic();
				bool getAccountStatus(std::string account_name);
				float getAccountValue(std::string account_name);
				std::vector<std::string> getAccountLedger(std::string account_name);
				std::string getAccountMeta(std::string account_name);
				std::vector<std::string> getAllAccountNames();
				bool createAccount(std::string name);
				bool removeAccount(std::string account_name);
				bool payment(float amount, std::string account_name);
				bool transfer(float amount, std::string account1, std::string account2);
				bool editAccountMeta(std::string account_name, std::string meta);
				bool fileDump(std::string target_file);
				bool fileCollect(std::string target_file);
		};
	}
}
#endif