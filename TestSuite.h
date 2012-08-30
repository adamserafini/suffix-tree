#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "SuffixTree.h"
#include "FASTA_FileReader.h"
#include "GeneralSuffixTree.h"
#include "Assembler.h"
#include "FASTQ_FileReader.h"

//List of individual tests

//bool FASTA_FILE_READER_TEST();
bool EXACT_MATCH_TEST();
bool GENERAL_SUFFIX_TREE_TEST();
bool LARGE_DATASET_TEST();
bool FASTQ_FILE_READER_TEST();

void EXECUTE_TEST_SUITE() {
	std::cout << "Running tests..." << std::endl;
	typedef bool (*Test)();
	std::vector<Test> tests;
	//tests.push_back(FASTA_FILE_READER_TEST);
	tests.push_back(EXACT_MATCH_TEST);
	tests.push_back(GENERAL_SUFFIX_TREE_TEST);
	//tests.push_back(LARGE_DATASET_TEST);
	//tests.push_back(FASTQ_FILE_READER_TEST);

	for (int i = 0; i < tests.size(); i++) {
		std::cout   << "Test " << i + 1 
					<< (tests[i]() ? " PASSED" : " FAILED")
					<< std::endl;
	}
	std::cout << "Press any key to exit..." << std::endl;
	std::cin.get();
}

/*
bool FASTA_FILE_READER_TEST() {
	FASTA_FileReader file("Swinepox_NC_003389_simreads.fa.31764.CONTIGS");
	std::set<std::string> sequences = file.parse();
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
*/

bool EXACT_MATCH_TEST() {
	FASTA_FileReader file("Swinepox_NC_003389_complete.fasta");
	std::set<std::string> sequences = file.parse();
	SuffixTree st;
	//SuffixTree st("xabxa$");
	//SuffixTree st("AGGTTA$");
    st.construct(*sequences.begin() + "$");
	//st.log_tree(); //caution: a 100k character sequences generates
					 //+10GB log files. use log_tree only for debugging.
	std::string test = "TGTAACCT";
	std::vector<int> v = st.get_exact_matches(test);

	for (int i = 0; i < v.size(); i++) {
		std::cout << v[i] << std::endl;
	}

	if (v.size() == 3 
		&& v[0] == 138
		&& v[1] == 36082 
		&& v[2] == 146447	
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
	//gst.log_tree();
	if (assembler.get_SCS(gst) == "aabcaacababaaddd")
		return true;
	else return false;
}

bool LARGE_DATASET_TEST() {
	FASTA_FileReader file("SWINEPOX_SIMULATED_READS.TXT");
	std::set<std::string> strings = file.parse();

	GeneralSuffixTree gst(strings);
	/*
	Assembler assembler;
	assembler.label_nodes(gst);
	assembler.initialise(gst);
	assembler.greedy_SCS(gst);

	std::string SCS = assembler.get_SCS(gst);
	SuffixTree st;
	st.construct(SCS);
	std::set<std::string>::iterator it = strings.begin();
	for (; it != strings.end(); it++) {
		if ((st.get_exact_matches(*it)).empty())
			return false;
	}
	*/
	return true;
}

bool FASTQ_FILE_READER_TEST() {
	FASTQ_FileReader file("6180_1#1_1.fastq");
	std::set<std::string> strings = file.parse();
	std::cout << "String count: " << strings.size() << std::endl;
	std::set<std::string>::iterator it = strings.begin();
	freopen("fastq.txt", "w", stdout);
	for (; it != strings.end(); it++ ) {
		std::cout << *it << std::endl;
	}
	freopen( "CON", "w", stdout );
	return true;
}

