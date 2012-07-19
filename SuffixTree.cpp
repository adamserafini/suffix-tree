#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h" 
#include <iostream>

SuffixTree::SuffixTree(std::string s) {
    length = s.length();
    tree_string = ' ' + s;
    internal_node_ID = 0;
	current_end = new int(0);
    root = new Node(NULL, 1, new int (0), internal_node_ID);
}

void SuffixTree::construct() {
	(*current_end)++;
    root->add_child(new Node(root, 1, current_end, 1));
    //print_tree();

    for (int i = 1; i < length; i++) {
        SPA(i);
		print_tree();
		if (i % 100 == 0) std::cerr << "Phase: " << i << std::endl;
    }
}

void SuffixTree::print_tree() {
    print_node(root);
	std::cout << "END OF TREE" << std::endl;
}

void SuffixTree::print_node(Node* parent) {
    int parent_ID = parent->ID;
    Node* child = parent->child;
    while (child != NULL) {
        std::cout << parent_ID 
                  << " " << get_substr(child->begin_index, *child->end_index) 
                  << " " << child->ID << std::endl;
        print_node(child);
        child = child->sibling;
    } 
}

//SPA: Single Phase Algorithm (Gusfield, 1997)
void SuffixTree::SPA(int i) { 
	(*current_end)++;
    for (int j = 1; j <= (i + 1); j++) {
        SEA(j, i);
		//print_tree();
    }
}

//SEA: Single Extension Algorithm (Gusfield, 1997)
void SuffixTree::SEA(int j, int i) { 
    Suffix suffix = get_suffix(root, j, i);
    //RULE1 (path ends at a leaf) - do nothing! extension is explicity handled by 'current_end'
	//RULE2 (path doesn't end at a leaf and no path continues with char [i + 1]):
    if (!suffix.ends_at_leaf() && !suffix.continues_with_char(*this, tree_string[i + 1]))
        RULE2(suffix, i + 1, j);
    //else RULE3 (some ongoing path starts with char [i + 1]) - do nothing!
}

//The 'skip/count' trick for suffix tree traversal (Gusfield, 1997)
Suffix SuffixTree::get_suffix(Node* origin, int begin_index, int end_index) {
	int char_index = *origin->end_index;
	while (begin_index <= end_index) {
		origin = origin->get_child(*this, tree_string[begin_index]);
		if (origin->edge_length() < end_index - begin_index + 1)
			char_index = *origin->end_index;
		else char_index = origin->begin_index + (end_index - begin_index);
		begin_index+=origin->edge_length();
	}
	return Suffix(origin, char_index);
}

std::string SuffixTree::get_substr(int start_pos, int end_pos) {
    if (start_pos > end_pos) return std::string();
    return tree_string.substr(start_pos, end_pos - start_pos + 1);
}

void SuffixTree::RULE2(Suffix& suffix, int char_index, int new_leaf_ID) {
    if (!suffix.ends_at_node()) {  //eg. case 2 (path ends inside an edge)
		suffix.node->split_edge(suffix.char_index, --internal_node_ID);
		suffix.node = suffix.node->parent;
	}
	Node* new_leaf = new Node(suffix.node, char_index, current_end, new_leaf_ID);  
    suffix.node->add_child(new_leaf);
}

