// Copyright (c) 2012 Adam Serafini

#ifndef SRC_SUFFIXTREE_H_
#define SRC_SUFFIXTREE_H_

#include <string>
#include <vector>

class Suffix;
class Node;
class SuffixTree {
 public:
  SuffixTree();
  void construct(std::string);
  std::string log_tree();
  char get_char_at_index(int) const;

 private:
  std::string tree_string;
  std::string log_node(Node* parent);
  std::string get_substr(int, int);
  // Suffix Extension rules (Gusfield, 1997)
  enum Rule {RULE_2, RULE_3};

  // SPA: Single Phase Algorithm (Gusfield, 1997)
  void SPA(int);

  // SEA: Single Extension Algorithm (Gusfield, 1997)
  Rule SEA(Suffix&, int, int);

  // The 'skip/count' trick for traversal (Gusfield, 1997)
  Suffix get_suffix(Node*, int, int);

  // Apply Suffix Extension Rule 2 (Gusfield, 1997)
  void RULE2(Suffix&, int, int);

  Node* root;
  int internal_node_ID;
  int length;
  int* current_end;
  Node* last_leaf_extension;
};

#endif  // SRC_SUFFIXTREE_H_
