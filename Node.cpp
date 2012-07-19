#include "Node.h"
#include "SuffixTree.h"
#include <iostream>

Node::Node(Node* parent, int begin_index, int end_index, int ID) {
	this->parent = parent;
	this->begin_index = begin_index;
	this->end_index = end_index;
	this->ID = ID;
	child = NULL;
	suffix_link = NULL;
	sibling = NULL;
}

void Node::add_child(Node* child) {
    if (this->child == NULL) {
        this->child = child;
    }   
    else {
        Node* n = this->child;
        while (n->sibling != NULL)
            n = n->sibling;
        n->sibling = child;
    }
}

/*
void Node::split_edge(int char_index, int new_node_ID) {
    Node* new_node = new Node(this, char_index + 1, this->end_index, this->ID);
	new_node->adopt_children(this);
	
	this->add_child(new_node);
    this->end_index = char_index;
    this->ID = new_node_ID;
}
*/

void Node::split_edge(int char_index, int new_node_ID) {
	Node* new_node = new Node(this->parent, this->begin_index, char_index, new_node_ID);
	new_node->add_child(this); 
	new_node->sibling = this->sibling;
	Node* n = parent->child;
	if (parent->child == this)
		parent->child = new_node;
	else {
		while (n->sibling != this)
			n = n->sibling;
		n->sibling = new_node;
	}
	this->parent = new_node;
	this->sibling = NULL;
	this->begin_index = char_index + 1;
}


void Node::adopt_children(Node* current_parent) {
	child = current_parent->child;
	Node* n = child;
	while (n != NULL) {
		n->parent = this;
		n = n->sibling;
	}
	current_parent->child = NULL;
}

Node* Node::get_child(const SuffixTree& tree, char ch) {
    Node* to_return = child;
    while (to_return != NULL && tree.tree_string[to_return->begin_index] != ch)
        to_return = to_return->sibling;
    return to_return;
}



