#include "TestSuite.h"
#include "SuffixTree.h"

using namespace std;

int main() {
	SuffixTree tree;
	tree.construct("xabxa$");
	tree.log_tree();

	EXECUTE_TEST_SUITE();
}

