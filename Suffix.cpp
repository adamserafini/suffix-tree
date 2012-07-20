#include "Suffix.h"
#include "Node.h"
#include "SuffixTree.h"

#include <iostream>

Suffix::Suffix(Node* n, int c) : node(n), char_index(c) {
	new_internal_node = false;
}

bool Suffix::ends_at_node() const { 
    return char_index == *node->end_index;
}

bool Suffix::ends_at_leaf() const {
    return node->is_leaf() && ends_at_node();
}

bool Suffix::continues_with_char(const SuffixTree& tree, char ch) const {
    return (ends_at_node() && node->get_child(tree, ch) != NULL)
            || (!ends_at_node() && tree.tree_string[char_index + 1] == ch);
}

Node* Suffix::walk_up() const {
	return ends_at_node() && node->suffix_link != NULL ?
		node : node->parent;
}


/*
Node* Suffix::traverse_link(Node* root) const {
	if (ends_at_node() && node->suffix_link != NULL) {
		if (node->suffix_link == root) std::cerr << "UH OH1!" << std::endl;
		return node->suffix_link;
	}
		//std::cout << "ends at node and node has suffix link" << std::endl;
	else if (ends_at_node() && node->parent->suffix_link != NULL) {
		if (node->parent->suffix_link == root) std::cerr << "UH OH2!" << std::endl;
		return node->parent->suffix_link;
	}
		//std::cout << "ends at node and node's parent has suffix link" << std::endl;
	else if (!ends_at_node() && node->parent->suffix_link != NULL) {
		if (node->parent->suffix_link == root) std::cerr << "UH OH3!" << std::endl;
		return node->parent->suffix_link;
	}
		//std::cout << "doesn't end at node and node's parent has suffix link" << std::endl;
	else if (!ends_at_node() && node->parent == root)
		return node->parent;
		//std::cout << "doesn't end at node and node's parent is root" << std::endl;
	else if (ends_at_node() && node->parent == root)
		return node->parent;
		//std::cout << "ends at node and node's parent is root" << std::endl;
	else
		std::cerr << "an unexpected situation happened" << std::endl;
	return NULL;
}
*/