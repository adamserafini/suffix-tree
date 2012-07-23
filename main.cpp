
#include <iostream>
#include <string>
#include "SuffixTree.h"
#include "FASTA_FileReader.h"

using namespace std;

int main() {
	FASTA_FileReader file("Swinepox_NC_003389_complete.fasta");
	string sequence = file.parse();

	SuffixTree st(sequence + "$");
	//SuffixTree st("xabxa$");
	//SuffixTree st("AGGTTA$");

    st.construct();
	//st.log_tree(); //caution: a 100k character sequences generates
					 //+10GB log files. use log_tree only for debugging.

	std::string test = "TGTAACCT";
	std::vector<int> v = st.get_exact_matches(test);

	freopen("log_file1", "w", stdout);
	cout << st.tree_string.substr(1) << endl;
	for (int i = 0; i < v.size(); i++)
		cout << "Position: " << v[i] << endl;
	cout << "Size: " << v.size() << endl;
	cin.get();
}