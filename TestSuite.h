#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"

//List of individual tests
void EXACT_MATCH_TEST();

void EXECUTE_TEST_SUITE() {
	EXACT_MATCH_TEST();
}

void EXACT_MATCH_TEST() {
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
	if (v.size() == 3 && v[0] == 146447 && v[1] == 36082 && v[2] == 138)
		std::cout << "EXACT MATCH TEST PASSED" << std::endl;
	else std::cout << "EXACT MATCH TEST FAILED" << std::endl;
	std::cin.get();
}