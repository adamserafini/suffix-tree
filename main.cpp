#include "TestSuite.h"
#include "SuffixTree.h"

#include <time.h>

#include "FASTA_FileReader.h"
#include "GeneralSuffixTree.h"

using namespace std;

int main() {
	//SuffixTree tree;
	//tree.construct("xabxa$");
	//tree.log_tree();

	//EXECUTE_TEST_SUITE();

	FASTA_FileReader file("SWINEPOX_SIMULATED_READS.txt");

	time_t start, end;
	time (&start);
	GeneralSuffixTree gst(file.parse());
	time (&end);
	double dif = difftime(end, start);

	cout << "Took: " <<  dif << endl;

	cout << "Done!" << endl;
	cin.get();
	
}

