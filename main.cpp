#include <iostream>
#include "TestSuite.h"
#include <string>
#include <limits>
#include <set>
#include <cassert>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"
#include <time.h>
#include "Node.h"
#include <numeric>
#include <algorithm>

using namespace std;




//define TESTING to run tests
//#define TESTING

#ifndef TESTING
int overlap(string left, string right)
{
	for (int i = 0; i < left.length(); i++)
	{
		if (left.substr(i) == right.substr(0, left.length() - i))
			return left.length() - i;
	}
	return 0;
}

int main()
{
	SuffixTree st;
	st.construct("war0ar1");
	st.log_tree();

	/*
	FASTA_FileReader file("SWINEPOX_SIMULATED_READS_10k.txt");
	set<string> reads = file.parse();

	GeneralSuffixTree gst(reads);
	std::vector<Node*> nodes_to_visit (1, gst.root);
	std::vector<int> child_count;

	while (!nodes_to_visit.empty()) {
		Node* current_node = nodes_to_visit.back();
		nodes_to_visit.pop_back();
		if (!current_node->is_leaf()) {
			child_count.push_back(current_node->children.size());
			current_node->get_children(nodes_to_visit);
		}
	}

	int total = std::accumulate(child_count.begin(), child_count.end(), 0);
	cout << "Total children: " << total << std::endl;
	cout << "Node count: " << child_count.size() << std::endl;

	int max = 0;
	int plus_k_count = 0;
	int plus_hundred_count = 0;
	for (int i = 0; i < child_count.size(); i++) {
		if (child_count[i] > max) max = child_count[i];
		if (child_count[i] >= 1000) plus_k_count++;
		if (child_count[i] >= 100) plus_hundred_count++;
	}

	cout << "Max = " << max << "\n";

	cout << "1k count = " << plus_k_count << endl;

	cout << "100 count = " << plus_hundred_count << endl;

	cin.get();
	*/
	/*
	srand ( time(NULL) );
	FASTA_FileReader file("Swinepox_NC_003389_simreads.FASTA");
	set<string> reads = file.parse();
	int size = reads.size();
	vector<string> string_vector(reads.begin(), reads.end());
	cout << "Vector size: " << string_vector.size() << std::endl;

	time_t start, end;
	time (&start);
	for (int i = 0; i < 100000; i++) {
		overlap (string_vector[rand() % size], string_vector[rand() % size]);
	}

	time (&end);
	
	cout << "Took: " << difftime (end,start) << " seconds" << endl;

	cin.get();
	*/
}




















	/*
	std::ifstream infile_SCS;
	infile_SCS.open("SCS.txt");
	assert(infile_SCS);

	FASTA_FileReader f("Swinepox_NC_003389_complete.fasta");
	std::set<string> originals = f.parse();
	assert(originals.size() == 1);
	std::string original = *originals.begin();

	std::string SCS;
	std::getline(infile_SCS, SCS);

	cout << "SCS length: " << SCS.length() << std::endl;
	cout << "Original length: " << original.length() << std::endl;

	size_t found;
	found = SCS.find(original.substr(122848, 23605));
	if (found!=string::npos)
		cout << "At position: " << found << std::endl;

	cout << "Program ended" << std::endl;
	cin.get();
	*/
	
	/*
	SuffixTree st;
	st.construct("xabxac");
	st.log_tree();
	*/
	/*
	cout << "Generating reads..." << endl;
	std::ifstream infile;
	std::ofstream outfile;
	std::string full_sequence;
	infile.open("Swinepox_NC_003389_complete.fasta");
	assert(infile);
	if (infile) {
		std::string line;
		getline(infile, line);
		while (getline(infile, line))
			full_sequence += line;
	}
	std::cout << "Total sequence is: " << full_sequence.length() << " characters long." << std::endl;
	*/
	/*
	std::set<std::string> strings;
	for (int frag_length = 36; frag_length <= 150; frag_length++)
	{
		int count = 0;
		for (int i = 0; i <= full_sequence.length() - frag_length; i++) {
			count++;
			std::string to_insert = full_sequence.substr(i, frag_length);
			assert(to_insert.length() == frag_length);
			strings.insert(to_insert);
		}
		cout	<< "Fragment size: " << frag_length << " "
				<< "Read " << count << " strings and set contains " << strings.size() << std::endl;
		strings.clear();
		if (count == strings.size()) cin.get();
	}
	cin.get();
	

	outfile.open("Swinepox_NC_003389_complete_141.FASTA");
	std::set<std::string> strings;
	int count = 0;
	for (int i = 0; i <= full_sequence.length() - 141; i++) {
		count++;
		std::string to_insert = full_sequence.substr(i, 141);
		assert(to_insert.length() == 141);
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
	*/
#else
int main() {
	EXECUTE_TEST_SUITE();

}
#endif




