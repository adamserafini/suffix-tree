#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"
#include "GeneralSuffixTree.h"
#include "Assembler.h"
#include <fstream>

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
	std::vector<std::string> sequences;
	file.parse(sequences);
	SuffixTree st;
    st.construct(sequences[0] + "$");

	std::string test = "TGTAACCT";
	std::vector<int> v = st.get_exact_matches(test);
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
	GeneralSuffixTree gst;
	std::vector<std::string> strings;
	strings.push_back("adam");
	strings.push_back("dame");
	strings.push_back("medal");
	strings.push_back("amicable");
	strings.push_back("able");
	strings.push_back("dab");
	strings.push_back("dada");
	strings.push_back("damn");
	strings.push_back("nooverlap");
	strings.push_back("damaging");
	strings.push_back("damaging");
	strings.push_back("ableton");
	strings.push_back("tons");
	strings.push_back("dale");
	strings.push_back("ale");
	gst.construct(strings);
	
	std::vector<std::string> paths;
    //gst.tidy_leaves();
	
	//gst.retrieve_paths(gst.root, std::string(), paths);

	for (int i = 0; i < paths.size(); i++) {
		std::cout << paths[i] << std::endl;
	}
	for (int i = 0; i < gst.string_index.size(); i++) {
		std::cout << "Position: " <<gst.string_index[i].first << " "
			<< "Length: " << gst.string_index[i].second << std::endl;
	}
	Assembler assembler;
	assembler.compute_overlaps(gst);
	//assembler.print_overlaps(gst);
	gst.log_tree();
	return true;
}

bool BIG_CONCAT_TEST() {
	FASTA_FileReader file("SWINEPOX_SIMULATED_READS.TXT");
	std::vector<std::string> strings;
	file.parse(strings);
	std::cout << "Finished parsing." << std::endl;
	
	GeneralSuffixTree gst;
	gst.construct(strings);
	return true;
}
