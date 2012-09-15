#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "SuffixTree.h"
#include "FASTA_FileReader.h"
#include "GeneralSuffixTree.h"
#include "Assembler.h"

bool SUFFIX_TREE_TEST();
bool GREEDY_SCS_TEST();
bool FASTA_FILE_READER_TEST();

void EXECUTE_TEST_SUITE() {
	std::cout << "Running tests..." << std::endl;
	typedef bool (*Test)();
	std::vector<Test> tests;
	tests.push_back(SUFFIX_TREE_TEST);
	tests.push_back(GREEDY_SCS_TEST);
	tests.push_back(FASTA_FILE_READER_TEST);

	for (int i = 0; i < tests.size(); i++) {
		std::cout   << "Test " << i + 1 
					<< (tests[i]() ? " PASSED" : " FAILED")
					<< std::endl;
	}
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.get();
}

bool SUFFIX_TREE_TEST() {
	FASTA_FileReader file("Swinepox_NC_003389_complete.fasta");
	std::set<std::string> sequences = file.parse();
	SuffixTree st;
    st.construct(*sequences.begin() + "$");
	std::string test = "TGTAACCT";
	std::vector<int> v = st.get_exact_matches(test);

	if (v.size() == 3 
		&& v[0] == 146447
		&& v[1] == 138 
		&& v[2] == 36082	
		&& sequences.size() == 1)
		return true;
	else return false;
}

bool GREEDY_SCS_TEST() {
	FASTA_FileReader file("Greedy_SCS_TestSet.fasta");
	GeneralSuffixTree gst(file.parse());
	Assembler assembler;
	assembler.label_nodes(gst);
	assembler.greedy_SCS(gst);
	if (assembler.get_SCS(gst) == "aabcaacababaaddd")
		return true;
	else return false;
}

bool FASTA_FILE_READER_TEST() {
	FASTA_FileReader file("FASTA_FileReader_TestFile.fasta");
	std::set<std::string> strings = file.parse();

	std::set<std::string>::iterator it = strings.begin();

	if (strings.size() != 5
		|| (*it++).length() != 88023
		|| (*it++).length() != 419
		|| (*it++).length() != 34536
		|| (*it++).length() != 276
		|| (*it).length() != 19502)
			return false;
	return true;
}
