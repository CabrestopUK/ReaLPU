//original contributor: CabrestopUK
#include <vector>
#include <string>
#include <fstream>

#ifndef CSV
#define CSV
namespace csv {
	class readCsv {
		/* 	reads a csv
			requires the csv file_name as input */
		
		private:
			std::ifstream read;
		
		public:
			readCsv(std::string file_name);
			std::vector<std::vector<std::string>> readFile();
	};
	class writeCsv {
		/* 	writes a csv
			requires the csv file_name as input */
		private:
			std::ofstream write;
		
		public:
			writeCsv(std::string file_name);
			void writeLine(std::vector<std::string> line);
	};
}
#endif