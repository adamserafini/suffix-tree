#pragma once

#include <string>
#include <vector>
#include <map>

class SuffixTree;
class Node
{
public:
	Node(Node*, int, int*, int);
	int edge_length() {return *end_index - begin_index + 1;}
	void add_child(const SuffixTree&, Node*);
	void remove_child(const SuffixTree&, Node*);
	bool is_leaf() {return children.empty();}
    void split_edge(const SuffixTree&, int, int);
	Node* get_child(const SuffixTree&, int char_index);
	Node* get_char_child(const SuffixTree&, char ch);
	void get_children(std::vector<Node*>&) const;
	int get_key(const SuffixTree&, Node*, int) const;

    Node* parent;
    std::map<int, Node*> children;
	std::vector<int> labels;
    Node* suffix_link;
	int begin_index;
	int* end_index;
    int ID;
};

