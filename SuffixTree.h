#pragma once

#include <string>
#include <vector>

class Suffix;
class Node;
class SuffixTree
{
public:
    SuffixTree();
	void construct(std::string);
	void log_tree();
    void log_node(Node*);
	std::vector<int> get_exact_matches(std::string) const;
	std::vector<int> retrieve_leaves(const Suffix&) const;
	std::string get_substr(int, int);
	Suffix match_string(std::string) const;
	enum Rule {RULE_2, RULE_3};			//Suffix Extension rules (Gusfield, 1997)
	void SPA(int);						//SPA: Single Phase Algorithm (Gusfield, 1997)
    Rule SEA(Suffix&, int, int);		//SEA: Single Extension Algorithm (Gusfield, 1997)
    Suffix get_suffix(Node*, int, int); //The 'skip/count' trick for traversal (Gusfield, 1997)
    void RULE2(Suffix&, int, int);		//apply Suffix Extension Rule 2 (Gusfield, 1997)

    std::string tree_string;
    Node* root;
    int internal_node_ID;
    int length;
	int* current_end;
	Node* last_leaf_extension;
};

