// Copyright (c) 2012 Adam Serafini

#include <vector>
#include <map>

#include "Node.h"
#include "SuffixTree.h"

Node::Node(Node* parent, int begin_index, int* end_index, int ID) {
  this->parent = parent;
  this->begin_index = begin_index;
  this->end_index = end_index;
  this->ID = ID;
  suffix_link = NULL;
}

void Node::add_child(const SuffixTree& tree, Node* child_to_add) {
  int key = get_key(tree, child_to_add, child_to_add->begin_index);
  children[key] = child_to_add;
}

void Node::remove_child(const SuffixTree& tree, Node* child_to_remove) {
  int key = get_key(tree, child_to_remove, child_to_remove->begin_index);
  children.erase(key);
}

int Node::get_key(const SuffixTree& tree, Node* node, int index) const {
  char ch = tree.get_char_at_index(index);
  return (ch != '$' ? ch * (-1) : index);
}

void Node::split_edge(const SuffixTree& tree, int char_index, int new_node_ID) {
  Node* new_node = new Node(
    parent, begin_index, new int(char_index), new_node_ID);

  parent->remove_child(tree, this);
  parent->add_child(tree, new_node);

  this->parent = new_node;
  this->begin_index = char_index + 1;
  new_node->add_child(tree, this);
}

Node* Node::get_child(const SuffixTree& tree, int char_index) {
  int key = get_key(tree, this, char_index);
  std::map<int, Node*>::iterator it = children.find(key);
  if (it != children.end())
    return it->second;
  else
    return NULL;
}
