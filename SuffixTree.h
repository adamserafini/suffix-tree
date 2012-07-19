#pragma once

#include <string>
class Suffix;
class Node;

class SuffixTree
{
public:
    SuffixTree(std::string);
    std::string tree_string;
    Node* root;
    void construct();
    int internal_node_ID;
    int length;
	int* current_end;
	Node* current_full_string;
    void print_tree();
    void print_node(Node*);
    void SPA(int); //SPA: Single Phase Algorithm (Gusfield, 1997)
    void SEA(Suffix&, int, int); //SEA: Single Extension Algorithm (Gusfield, 1997)
    Suffix get_suffix(Node*, int, int); //The 'skip/count' trick for suffix tree traversal (Gusfield, 1997)
    std::string get_substr(int, int);
	enum RULE2_CASE {NEW_CHILD_NODE, NEW_INTERNAL_NODE};
    RULE2_CASE RULE2(Suffix&, int, int); //apply extension rule 2 (Gusfield, 1997)
};

