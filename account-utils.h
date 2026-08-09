// original contributer: CabrestopUK
#ifndef ACCOUNT_UTILS
#define ACCOUNT_UTILS

#include <string>
#include <vector>

namespace accountutils {
	/*	ALL THE ACCOUNT TYPES AND THEIR METHODS */
	class account {
		/*	(no args) basic account object - stores account value and ledger of all transactions */
		private: //variables kept in private for personal sanity :) - also incase of any features of specific accounts that require limits on changing value
			float value = 0.00;
			std::vector<std::string> ledger = {};
			int transaction_num = 0; // primarily utilised for ledger
			
		public:
			account();
			float getValue();
			std::vector<std::string> getLedger();
			void editValue(float change);
	};
}
#endif