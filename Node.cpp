#include "Node.h"
#include "SuffixTree.h"

Node::Node(Node* parent, int begin_index, int* end_index, int ID) {
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


void Node::split_edge(int char_index, int new_node_ID) {
	Node* new_node = new Node(this->parent, this->begin_index, 
								new int(char_index), new_node_ID);
	new_node->add_child(this); 
	new_node->sibling = this->sibling;
	if (parent->child == this)
		parent->child = new_node;
	else {
		Node* n = parent->child;
		while (n->sibling != this)
			n = n->sibling;
		n->sibling = new_node;
	}
	this->parent = new_node;
	this->sibling = NULL;
	this->begin_index = char_index + 1;
}

Node* Node::get_child(const SuffixTree& tree, char ch) {
    Node* to_return = child;
    while (to_return != NULL && tree.tree_string[to_return->begin_index] != ch)
        to_return = to_return->sibling;
    return to_return;
}

void Node::get_children(std::vector<Node*>& children) const {
	Node* node = this->child;
	while (node != NULL) {
		children.push_back(node);
		node = node->sibling;
	}
}

void Node::get_alpha_children(const SuffixTree& st, std::vector<Node*>& children) const {
	Node* node = this->child;
	while (node != NULL) {
		if (isalpha(st.tree_string[node->begin_index]))
			children.push_back(node);
		node = node->sibling;
	}
}




