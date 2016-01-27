// Copyright (C) 2012 Adam Serafini

#include "SuffixTree.h"

int main() {
  SuffixTree tree;
  tree.construct("xabxa$");
  tree.log_tree();
}
