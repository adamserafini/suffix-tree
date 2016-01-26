#include "SuffixTree.h"
#include <emscripten/bind.h>

using namespace emscripten;

void print_tree(std::string input) {
	SuffixTree tree;
	tree.construct(input);
	tree.log_tree();
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("print_tree", &print_tree);
}
