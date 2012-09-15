#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "SuffixTree.h"
#include "FASTA_FileReader.h"
#include "GeneralSuffixTree.h"
#include "Assembler.h"

bool EXACT_MATCH_TEST();
bool GENERAL_SUFFIX_TREE_TEST();
bool FASTA_FILE_READER_TEST();

void EXECUTE_TEST_SUITE() {
	std::cout << "Running tests..." << std::endl;
	typedef bool (*Test)();
	std::vector<Test> tests;
	tests.push_back(EXACT_MATCH_TEST);
	tests.push_back(GENERAL_SUFFIX_TREE_TEST);
	tests.push_back(FASTA_FILE_READER_TEST);

	for (int i = 0; i < tests.size(); i++) {
		std::cout   << "Test " << i + 1 
					<< (tests[i]() ? " PASSED" : " FAILED")
					<< std::endl;
	}
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.get();
}

bool EXACT_MATCH_TEST() {
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

bool GENERAL_SUFFIX_TREE_TEST() {
	std::set<std::string> strings;
	strings.insert("ababaa");
	strings.insert("caba");
	strings.insert("aaddd");
	strings.insert("aabca");
	strings.insert("aacab");

	GeneralSuffixTree gst(strings);
	Assembler assembler;
	assembler.label_nodes(gst);
	assembler.initialise(gst);
	assembler.greedy_SCS(gst);
	if (assembler.get_SCS(gst) == "aabcaacababaaddd")
		return true;
	else return false;
}

bool FASTA_FILE_READER_TEST() {
	FASTA_FileReader file("Swinepox_NC_003389_simreads.fa.31764.CONTIGS");
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
