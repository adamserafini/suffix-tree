#include <iostream>
#include "TestSuite.h"
#include <string>
#include <limits>

using namespace std;

//define TESTING to run tests
#define TESTING

#ifndef TESTING
int main() {
	cout << "Normal program execution.." << endl;
	string s;
	cout << s.max_size() << endl;
	cout << UINT_MAX << endl;
	cin.get();
}
#else
int main() {
	EXECUTE_TEST_SUITE();

}
#endif
