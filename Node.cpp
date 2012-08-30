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

void Node::add_child(Node* child_to_add) {
	child_to_add->sibling = child;
	child = child_to_add;
}

void Node::remove_child(Node* child_to_remove) {
	if (this->child == child_to_remove) {
		this->child = child_to_remove->sibling;
	}
	else {
		Node* n = this->child;
		while (n->sibling != child_to_remove)
			n = n->sibling;
		n->sibling = n->sibling->sibling;
	}
}

void Node::split_edge(int char_index, int new_node_ID) {
	Node* new_node = new Node(this->parent, this->begin_index, 
								new int(char_index), new_node_ID);
	parent->remove_child(this);
	parent->add_child(new_node);
	new_node->add_child(this);

	this->parent = new_node;
	this->sibling = NULL;
	this->begin_index = char_index + 1;
}

Node* Node::get_child(const SuffixTree& tree, int char_index) 
{
	char to_get = tree.tree_string[char_index];
	bool terminal(to_get == '$');
    Node* to_return = child;
    while (to_return != NULL) {
		int child_index(to_return->begin_index);
		char child_char(tree.tree_string[child_index]);
		bool match(child_char == to_get);
		
		if ((match && !terminal)
			|| (match && terminal && child_index == char_index))
				return to_return;
		to_return = to_return->sibling;
	} 
    return NULL;
}

void Node::get_children(std::vector<Node*>& children) const {
	Node* node = this->child;
	while (node != NULL) {
		children.push_back(node);
		node = node->sibling;
	}
}

//only use for testing non-GENERAL suffix trees!!
Node* Node::get_char_child(const SuffixTree& tree, char ch) {
    Node* to_return = child;
    while (to_return != NULL && tree.tree_string[to_return->begin_index] != ch)
        to_return = to_return->sibling;
    return to_return;
}






