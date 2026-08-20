//original contributor: CabrestopUK
#include "csv.h"
#include <iostream>
#include <stdexcept>

//
//	csv::readCsv class
//
csv::readCsv::readCsv(std::string file_name) {
	read.open(file_name);
	
	if (!read.is_open()) {
		throw std::runtime_error("file not opened");
	}
}

std::vector<std::vector<std::string>> csv::readCsv::readFile() {
	std::string line;
	std::vector<std::vector<std::string>> returnable_file;
	
	while (std::getline(read, line)) {
		std::vector<std::string> line_vector;
		std::string pre_append;
		for (char a_char : line) {
			if (a_char != ',') {
				pre_append += a_char;
			}
			else {
				line_vector.push_back(pre_append);
				pre_append.clear();
			}
		}
		if (pre_append != "") {
			line_vector.push_back(pre_append);
		}
		returnable_file.push_back(line_vector);
	}
	
	return returnable_file;
}
//
//	csv::writeCsv class
//
csv::writeCsv::writeCsv(std::string file_name) {
	write.open(file_name);
	
	if (!write.is_open()) {
		throw std::runtime_error("file not opened");
	}
}

void csv::writeCsv::writeLine(std::vector<std::string> line) {
	bool first_char = true;
	for (std::string part : line) {
		if (first_char == false) {write << ",";}
		else {first_char = false;}
		write << part;
	}
	write << std::endl;
}
//	
// main()
//
#ifdef TEST
int main() {
	csv::writeCsv test_write("foo.csv");
	test_write.writeLine({"yo", "hi", "hello"});
	test_write.writeLine({"la", "dee", "daa"});
	test_write.writeLine({"tic", "tac", "toe"});
	
	csv::readCsv test("foo.csv");
	auto thefile = test.readFile();
	
	for (std::vector<std::string> line : thefile) {
		for (std::string part : line) {
			std::cout << part << "\t";
		}
		std::cout << "\n";
	}
	
	return 0;
}
#endif