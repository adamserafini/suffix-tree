#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h" 
#include <iostream>

SuffixTree::SuffixTree(std::string s) {
    length = s.length();
    tree_string = ' ' + s;
    internal_node_ID = 0;
    root = new Node(NULL,std::string(), internal_node_ID);
}

void SuffixTree::construct() {
    root->add_child(new Node(root, std::string(1, tree_string[1]), 1));
    print_tree();
    
    for (int i = 1; i < length; i++) {
        SPA(i);
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
                  << " " << child->edge_label 
                  << " " << child->ID << std::endl;
        print_node(child);
        child = child->sibling;
    } 
}

//SPA: Single Phase Algorithm (Gusfield, 1997)
void SuffixTree::SPA(int i) { 
    for (int j = 1; j <= (i + 1); j++) {
        SEA(j, i);
		print_tree();
    }
}

//SEA: Single Extension Algorithm (Gusfield, 1997)
void SuffixTree::SEA(int j, int i) { 
    Suffix suffix = get_suffix(root, get_substr(j, i));
    if (suffix.ends_at_leaf()) 
        RULE1(suffix, tree_string[i + 1]);
    else if (!suffix.continues_with_char(tree_string[i + 1]))
        RULE2(suffix, tree_string[i + 1], j);
    //else RULE3 - do nothing!
}

Suffix SuffixTree::get_suffix(Node* origin, std::string string) {
	int char_index = static_cast<int>(origin->edge_label.length()) - 1;
    while (!string.empty()) {
        if (char_index == static_cast<int>(origin->edge_label.length()) - 1) {
			origin = origin->get_child(string[0]);
			char_index = 0;
		}
        else char_index++;
        string.erase(0, 1);    
    }
    return Suffix(origin, char_index);
}

std::string SuffixTree::get_substr(int start_pos, int end_pos) {
    if (start_pos > end_pos) return std::string();
    return tree_string.substr(start_pos, end_pos - start_pos + 1);
}

void SuffixTree::RULE1(Suffix suffix, char ch) {
    suffix.node->edge_label.append(1, ch);
}

void SuffixTree::RULE2(Suffix suffix, char ch, int new_leaf_ID) {
    Node* new_leaf = new Node(suffix.node, std::string(1, ch), new_leaf_ID);  
    if (!suffix.ends_at_node()) //eg. case 2 (path ends inside an edge)
        suffix.node->split_edge(suffix.char_index, --internal_node_ID);
    suffix.node->add_child(new_leaf);
}