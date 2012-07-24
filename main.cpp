#include <iostream>
#include "TestSuite.h"

using namespace std;

//define TESTING to run tests
#define TESTING

#ifndef TESTING
int main() {
	cout << "Normal program execution.." << endl;
	cin.get();
}
#else
int main() {
	EXECUTE_TEST_SUITE();
}
#endif
