// Copyright (c) 2012 Adam Serafini

#ifndef SRC_SUFFIX_H_
#define SRC_SUFFIX_H_

class SuffixTree;
class Node;
class Suffix {
  friend class SuffixTree;

 private:
  Suffix(Node*, int);
  Node* node;
  bool new_internal_node;
  int char_index;
  bool ends_at_node() const;
  bool ends_at_leaf() const;
  bool continues_with_char(const SuffixTree&, int) const;
  bool RULE2_conditions(const SuffixTree&, int) const;
  Node* walk_up(int&, int&) const;

};

#endif  // SRC_SUFFIX_H_
