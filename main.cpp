
#include <iostream>
#include <string>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"

using namespace std;

int main() {
	//FASTA_FileReader file("Swinepox_NC_003389_complete.fasta");
	//string sequence = file.parse();

	//SuffixTree st(sequence);
	SuffixTree st("xabxa$");
    st.construct();
	//st.log_tree(); //caution: a 100k character sequences generates
					 //+10GB log files. use log_tree only for debugging.

	std::string test = "xa";
	std::vector<int> v = st.get_exact_matches(test);
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
	cin.get();
}