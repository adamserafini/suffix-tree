#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"

//List of individual tests

bool EXACT_MATCH_TEST();
bool TWO_STRINGS_TEST1();
bool BIG_CONCAT_TEST();


void EXECUTE_TEST_SUITE() {
	std::cout << "Running tests..." << std::endl;
	typedef bool (*Test)();
	std::vector<Test> tests;
	//tests.push_back(EXACT_MATCH_TEST);
	tests.push_back(TWO_STRINGS_TEST1);
	//tests.push_back(BIG_CONCAT_TEST);

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
	std::string sequence = file.parse();
	SuffixTree st(sequence);
    st.construct();

	std::string test = "TGTAACCT";
	std::vector<int> v = st.get_exact_matches(test);
	std::cout << "Sequence size: " << sequence.length() << std::endl;
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] <<std::endl;
	if (v.size() == 3 
		&& v[0] == 146447 
		&& v[1] == 36082 
		&& v[2] == 138
		)
		return true;
	else return false;
}

bool TWO_STRINGS_TEST1() {
	SuffixTree st("adam0dame1medal2");
	st.construct();
	st.log_tree();

	std::vector<std::string> paths;
    st.retrieve_paths(st.root, std::string(), paths);


	for (int i = 0; i < paths.size(); i++) {
		std::cout << paths[i] << std::endl;
	}

	return true;
}

bool BIG_CONCAT_TEST() {
	FASTA_FileReader file("SWINEPOX_SIMULATED_READS.TXT");
	std::string sequence = file.parse();
	std::cout << "Finished parsing." << std::endl;
	
	SuffixTree st(sequence);
	st.construct();
	return true;
}
