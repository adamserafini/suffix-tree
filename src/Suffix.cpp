// Copyright (c) 2012 Adam Serafini

#include "Suffix.h"
#include "Node.h"
#include "SuffixTree.h"

Suffix::Suffix(Node* n, int c) : node(n), char_index(c) {
  new_internal_node = false;
}

bool Suffix::ends_at_node() const {
  return char_index == *node->end_index;
}

bool Suffix::ends_at_leaf() const {
  return node->is_leaf() && ends_at_node();
}

bool Suffix::continues_with_char(const SuffixTree& tree, int tree_index) const {
  char ch = tree.get_char_at_index(tree_index);
  bool terminal(ch == '$');
  return (ends_at_node() && node->get_child(tree, tree_index) != NULL)
    || (!ends_at_node() && tree.get_char_at_index(char_index + 1) == ch
      && (!terminal || char_index + 1 == tree_index));
}

Node* Suffix::walk_up(int& begin_index, int& end_index) const {
  if (ends_at_node() && node->suffix_link != NULL) {
    begin_index = *node->end_index;
    end_index = *node->end_index - 1;
    return node;
  } else {
    begin_index = node->begin_index;
    end_index = char_index;
    return node->parent;
  }
}

bool Suffix::RULE2_conditions(const SuffixTree& tree, int tree_index) const {
  return !ends_at_leaf() && !continues_with_char(tree, tree_index);
}
