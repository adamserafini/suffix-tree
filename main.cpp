#include <iostream>
#include "TestSuite.h"
#include <string>
#include <limits>
#include <set>
#include <cassert>

using namespace std;

//define TESTING to run tests
#define TESTING

#ifndef TESTING
int main() {
	cout << "Generating reads..." << endl;
	std::ifstream infile;
	std::ofstream outfile;
	std::string full_sequence;
	infile.open("H37Rv_final.fasta");
	assert(infile);
	if (infile) {
		std::string line;
		getline(infile, line);
		while (getline(infile, line))
			full_sequence += line;
	}
	std::cout << "Total sequence is: " << full_sequence.length() << " characters long." << std::endl;
	outfile.open("H37Rv_final_simreads.FASTA");
	std::set<std::string> strings;
	int count = 0;
	for (int i = 0; i <= full_sequence.length() - 75; i++) {
		count++;
		std::string to_insert = full_sequence.substr(i, 75);
		assert(to_insert.length() == 75);
		strings.insert(to_insert);
	}
	cout << "Read " << count << " strings and set contains " << strings.size() << std::endl;
	count = 0;
	std::set<std::string>::iterator it = strings.begin();
	for (; it != strings.end(); it++) {
		count++;
		outfile << "> Swinepox_NC003389 sim read " << count << std::endl;
		outfile << *it << std::endl;
	}

}
#else
int main() {
	EXECUTE_TEST_SUITE();

}
#endif




