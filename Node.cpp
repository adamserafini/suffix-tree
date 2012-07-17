#include "Node.h"
#include <iostream>

Node::Node(Node* parent, std::string label, int ID) {
    edge_label = label;
    this->parent = parent;
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

Node* Node::get_child(char ch) {
    Node* to_return = child;
    while (to_return != NULL && to_return->edge_label[0] != ch)
        to_return = to_return->sibling;
    return to_return;
}

void Node::split_edge(int char_index, int new_node_ID) {
    Node* new_node = new Node(this, edge_label.substr(char_index + 1), this->ID);
	new_node->adopt_children(this);
	
	this->add_child(new_node);
    this->edge_label = edge_label.substr(0, char_index + 1);
    this->ID = new_node_ID;
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



