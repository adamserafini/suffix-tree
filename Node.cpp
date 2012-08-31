#include "Node.h"
#include "SuffixTree.h"
#include <algorithm>
#include "CompareNode.h"

Node::Node(Node* parent, int begin_index, int* end_index, int ID) {
	this->parent = parent;
	this->begin_index = begin_index;
	this->end_index = end_index;
	this->ID = ID;
	suffix_link = NULL;
}

void Node::add_child(const SuffixTree& tree, Node* child_to_add) {
	int char_index = child_to_add->begin_index;
	char ch = tree.tree_string[char_index];

	int key = (ch != '$' ? ch * (-1) : char_index);
	children[key] = child_to_add;
}

void Node::remove_child(const SuffixTree& tree, Node* child_to_remove) {
	int char_index = child_to_remove->begin_index;
	char ch = tree.tree_string[char_index];

	int key = (ch != '$' ? ch * (-1) : char_index);
	children.erase(key);
}

void Node::split_edge(const SuffixTree& tree, int char_index, int new_node_ID) {
	Node* new_node = new Node(this->parent, this->begin_index, 
								new int(char_index), new_node_ID);
	parent->remove_child(tree, this);
	parent->add_child(tree, new_node);

	this->parent = new_node;
	this->begin_index = char_index + 1;
	new_node->add_child(tree, this);
}

Node* Node::get_child(const SuffixTree& tree, int char_index) 
{
	char ch = tree.tree_string[char_index];
	int key = (ch != '$' ? ch * (-1) : char_index);

	std::map<int, Node*>::iterator it = children.find(key);
	if (it != children.end())
		return it->second;
	else
		return NULL;
}

void Node::get_children(std::vector<Node*>& ret_children) const {
	std::map<int, Node*>::const_iterator it = children.begin();
	for (; it != children.end(); it++)
		ret_children.push_back(it->second);
}

//only use for testing non-GENERAL suffix trees!!
Node* Node::get_char_child(const SuffixTree& tree, char ch) {
	std::map<int, Node*>::iterator it = children.find(ch * (-1));
	if (it != children.end())
		return it->second;
	else
		return NULL;
}






