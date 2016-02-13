// Copyright (c) 2012 Adam Serafini

#include <iostream>
#include "SuffixTree.h"

int main() {
  SuffixTree tree;
  tree.construct("xabxa$");
  std::cout << tree.log_tree() << std::endl;
}
