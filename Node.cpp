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

void Node::add_child(Node* child_to_add) {
	children.push_back(child_to_add);
}

void Node::remove_child(Node* child_to_remove) {
	std::vector<Node*>::iterator it;
	it = std::find(children.begin(), children.end(), child_to_remove);
	children.erase(it);
}

void Node::split_edge(int char_index, int new_node_ID) {
	Node* new_node = new Node(this->parent, this->begin_index, 
								new int(char_index), new_node_ID);
	parent->remove_child(this);
	parent->add_child(new_node);
	new_node->add_child(this);

	this->parent = new_node;
	this->begin_index = char_index + 1;
}

Node* Node::get_child(const SuffixTree& tree, int char_index) 
{
	char to_get = tree.tree_string[char_index];
	bool terminal(to_get == '$');
 
	for (int i = 0; i < children.size(); i++) {
		int child_index = children[i]->begin_index;
		char child_char = tree.tree_string[child_index];
		bool match(child_char == to_get);

		if ((match && !terminal)
			|| (match && terminal && child_index == char_index))
				return children[i];
	}
    return NULL;
}

void Node::get_children(std::vector<Node*>& ret_children) const {
	ret_children.insert(ret_children.end(), children.begin(), children.end());
}

//only use for testing non-GENERAL suffix trees!!
Node* Node::get_char_child(const SuffixTree& tree, char ch) {
	for (int i = 0; i < children.size(); i++)
		if (tree.tree_string[children[i]->begin_index] == ch)
			return children[i];
	return NULL;
}






