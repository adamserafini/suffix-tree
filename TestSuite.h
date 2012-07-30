#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"

//List of individual tests

bool FASTA_FILE_READER_TEST();
bool EXACT_MATCH_TEST();
bool TWO_STRINGS_TEST1();
bool BIG_CONCAT_TEST();


void EXECUTE_TEST_SUITE() {
	std::cout << "Running tests..." << std::endl;
	typedef bool (*Test)();
	std::vector<Test> tests;
	//tests.push_back(FASTA_FILE_READER_TEST);
	//tests.push_back(EXACT_MATCH_TEST);
	//tests.push_back(TWO_STRINGS_TEST1);
	tests.push_back(BIG_CONCAT_TEST);

	for (int i = 0; i < tests.size(); i++) {
		std::cout   << "Test " << i + 1 
					<< (tests[i]() ? " PASSED" : " FAILED")
					<< std::endl;
	}
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.get();
}

bool FASTA_FILE_READER_TEST() {
	FASTA_FileReader file("Swinepox_NC_003389_simreads.fa.31764.CONTIGS");
	std::vector<std::string> sequences = file.parse();
	if (sequences.size() == 5
		&& sequences[3] == "TACACTTTTTTTTACCGTTTATAAATTATTATTTTTAATAAAAATAATAGATGATTATATTTATCTATACCTAAGGTAAGTAAATTAACATCTTTATTTTATAAAATAATAATTTATAAACGGTAAAAAAAAGTGTAACCTAATCCCTTATAGTCATGTTTTTTGAGAATAAAAACAAACGCATACTTTTTGAACGGAGAAATACCTGTATCCTTAATCCCCTATAACCATATTTTTTTAATCCAACATACTTTTTGAACGGAGAAATACCTGTAT"
		&& sequences[0].length() == 34536
		&& sequences[1].length() == 88023
		&& sequences[2].length() == 19502
		&& sequences[3].length() == 276
		&& sequences[4].length() == 419)
			return true;
	else return false;
}

bool EXACT_MATCH_TEST() {
	FASTA_FileReader file("Swinepox_NC_003389_complete.fasta");
	std::vector<std::string> sequences = file.parse();
	SuffixTree st(sequences[0] + "$");
	//SuffixTree st("xabxa$");
	//SuffixTree st("AGGTTA$");
    st.construct();
	//st.log_tree(); //caution: a 100k character sequences generates
					 //+10GB log files. use log_tree only for debugging.
	std::string test = "TGTAACCT";
	std::vector<int> v = st.get_exact_matches(test);
	if (v.size() == 3 
		&& v[0] == 146447 
		&& v[1] == 36082 
		&& v[2] == 138
		&& sequences.size() == 1)
		return true;
	else return false;
}

bool TWO_STRINGS_TEST1() {
	SuffixTree st("xabxa10xabxa11");
	st.construct();
	st.log_tree();
	return true;
}

bool BIG_CONCAT_TEST() {
	FASTA_FileReader file("Swinepox_NC_003389_simreads.fa.31764.CONTIGS");
	std::vector<std::string> sequences = file.parse();

	std::string concat;
	std::stringstream convert;
	for (int i = 0; i < sequences.size(); i++) {
		convert << i;
		concat = concat + sequences[i] + convert.str();
	}
	SuffixTree st(concat);
	st.construct();
	return true;
}
