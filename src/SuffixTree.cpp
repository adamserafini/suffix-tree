// Copyright (c) 2012 Adam Serafini

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h"

SuffixTree::SuffixTree() {
  // Internal node IDs start at zero and decrement. For example, the root node,
  // which can be considered the first internal node has an ID of 0. The next
  // internal node has an ID of -1, followed by -2 and so forth.

  // While not neccessary for the algorithm to function, each node having a
  // unique ID is important when using Graphiz to visualize the structure.
  internal_node_ID = 0;

  current_end = new int(0);
  root = new Node(NULL, 1, current_end, internal_node_ID);
}

void SuffixTree::construct(std::string s) {
  length = s.length();
  tree_string = '$' + s;

  (*current_end)++;
  last_leaf_extension = new Node(root, 1, current_end, 1);
  root->add_child(*this, last_leaf_extension);

  for (int i = 1; i < length; i++)
    SPA(i);
}

// SPA: Single Phase Algorithm (Gusfield, 1997)
void SuffixTree::SPA(int i) {
  Suffix previous_suffix(last_leaf_extension, *current_end);
  (*current_end)++;

  // Explicitly compute successive extensions starting at j(i) + 1 where (i)
  // is the ID of the last leaf extension from the previous phase.
  for (int j = (last_leaf_extension->ID + 1); j <= i + 1; j++) {
    Rule rule_applied = SEA(previous_suffix, j, i);
    if (rule_applied == RULE_3)
      break;
  }
}

// SEA: Single Extension Algorithm (Gusfield, 1997)
SuffixTree::Rule SuffixTree::SEA(Suffix& previous_suffix, int j, int i) {
  int begin_index, end_index;
  Node* origin = previous_suffix.walk_up(begin_index, end_index);
  Suffix suffix = (origin == root ? get_suffix(root, j, i)
    : get_suffix(origin->suffix_link, begin_index, end_index));

  Rule rule_applied;
  if (suffix.RULE2_conditions(*this, i + 1)) {
    RULE2(suffix, i + 1, j);
    rule_applied = RULE_2;
  } else {
    rule_applied = RULE_3;
  }

  if (previous_suffix.new_internal_node)
    previous_suffix.node->suffix_link = suffix.node;

  previous_suffix = suffix;
  return rule_applied;
}

// The 'skip/count' trick for suffix tree traversal (Gusfield, 1997)
Suffix SuffixTree::get_suffix(Node* origin, int begin_index, int end_index) {
  int char_index = *origin->end_index;

  while (begin_index <= end_index) {
    origin = origin->get_child(*this, begin_index);
    if (origin->edge_length() < end_index - begin_index + 1)
      char_index = *origin->end_index;
    else
      char_index = origin->begin_index + (end_index - begin_index);
    begin_index+=origin->edge_length();
  }
  return Suffix(origin, char_index);
}

std::string SuffixTree::get_substr(int start_pos, int end_pos) {
  if (start_pos > end_pos) return std::string();
  return tree_string.substr(start_pos, end_pos - start_pos + 1);
}

char SuffixTree::get_char_at_index(int index) const {
  return tree_string[index];
}

void SuffixTree::RULE2(Suffix& suffix, int char_index, int new_leaf_ID) {
  if (!suffix.ends_at_node()) {  // eg. in case 2 (path ends inside an edge)
    suffix.node->split_edge(*this, suffix.char_index, --internal_node_ID);
    suffix.node = suffix.node->parent;
    suffix.new_internal_node = true;
  }
  Node* new_leaf = new Node(suffix.node, char_index, current_end, new_leaf_ID);
  suffix.node->add_child(*this, new_leaf);
  last_leaf_extension = new_leaf;
}

std::string SuffixTree::log_tree() {
  return "digraph g{" + log_node(root) + "}";
}

std::string SuffixTree::log_node(Node* parent) {
  std::map<int, Node*>::iterator it = parent->children.begin();

  std::stringstream buffer;

  // Internal nodes (nodes with ID <= 0) are unlabelled points, leaves
  // (nodes with ID > 0) show the ID as plaintext.
  buffer << parent->ID << "[shape="
    << ((parent->ID <= 0) ? "point" : "plaintext") << "];";

  for (; it != parent->children.end(); it++) {
    // Child nodes are stored on the parent node in a map of integers
    // (it->first) to Node pointers (it->second).
    Node* child_node = it->second;
    buffer << parent->ID << "->" << child_node->ID << " [label = \""
      << get_substr(child_node->begin_index, *(child_node->end_index))
      << "\"];" << std::endl << log_node(child_node);
  }

  // Print the suffx link, if there is one.
  Node* suffix_link = parent->suffix_link;
  if (suffix_link)
    buffer << "\"" << parent->ID << "\" -> " << "\""
      << suffix_link->ID << "\" [style=dashed arrowhead=otriangle];"
      << std::endl;

  return buffer.str();
}
