#pragma once

#include <string>
#include <vector>

class SuffixTree;
class Node
{
public:
	Node(Node*, int, int*, int);
    Node* parent;
    Node* child;
    Node* sibling;
    Node* suffix_link;
	int begin_index;
	int* end_index;
	std::vector<int> node_labels;
	int edge_length() {return *end_index - begin_index + 1;}
    void add_child(Node*);
    int ID;
    bool is_leaf() {return child == NULL;}
    void split_edge(int, int);
	Node* get_child(const SuffixTree&, char);
	void get_children(std::vector<Node*>&) const;
	void get_child_depths(int, std::vector<int>&) const;
	void get_alpha_children(const SuffixTree&, std::vector<Node*>&) const;
};

