#pragma once

#include <string>
#include <vector>
class Suffix;
class Node;

class SuffixTree
{
public:
    SuffixTree();
    std::string tree_string;
    Node* root;
    void construct(const std::string&);
	void generalize();
    int internal_node_ID;
    int length;
	int* current_end;
	Node* last_leaf_extension;
    void log_tree();
    void log_node(Node*);
	std::string get_substr(int, int) const;
	enum Rule {RULE_2, RULE_3};			//Suffix Extension rules (Gusfield, 1997)
	void SPA(int);						//SPA: Single Phase Algorithm (Gusfield, 1997)
    Rule SEA(Suffix&, int, int);		//SEA: Single Extension Algorithm (Gusfield, 1997)
    Suffix get_suffix(Node*, int, int); //The 'skip/count' trick for traversal (Gusfield, 1997)
    void RULE2(Suffix&, int, int);		//apply Suffix Extension Rule 2 (Gusfield, 1997)
	std::vector<Node*> retrieve_leaves(const Suffix&) const;
	void retrieve_paths(Node*, std::string, std::vector<std::string>&) const;
	Suffix match_string(std::string) const;
	std::vector<int> get_exact_matches(std::string) const;
};

