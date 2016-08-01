// Copyright (c) 2012 Adam Serafini

#include <iostream>
#include "SuffixTree.h"

// Small CLI that takes a string as a parameter and
// prints a GraphViz representation of the suffix tree
// to STDOUT.

int main(int argc, char* argv[]) {
  SuffixTree tree;
  // Must be called with 1 and only 1 parameter.
  if (argc != 2) {
    std::cout << "usage: suffixtree inputstring" << std::endl;
    exit(1);
  }
  else {
    tree.construct(argv[1]);
    std::cout << tree.log_tree() << std::endl;
  }
}
