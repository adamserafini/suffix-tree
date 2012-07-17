
#include <iostream>
#include <string>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"

using namespace std;

int main() {
	freopen( "file.txt", "w", stdout);
	FASTA_FileReader file("Swinepox_NC_003389_complete.fasta");
	string sequence = file.parse();

	//SuffixTree st(sequence);
	SuffixTree st("xabxa$");
    st.construct();
	st.print_tree();
}