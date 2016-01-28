// Copyright (C) 2012 Adam Serafini

#include <emscripten/bind.h>

#include <string>

#include "SuffixTree.h"

void print_tree(std::string input) {
  SuffixTree tree;
  tree.construct(input);
  tree.log_tree();
}

EMSCRIPTEN_BINDINGS(my_module) {
  emscripten::function("print_tree", &print_tree);
}
