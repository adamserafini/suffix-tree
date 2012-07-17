#pragma once

#include <string>
#include <vector>

class Node
{
public:
    Node(Node*, std::string, int);
    Node* parent;
    Node* child;
    Node* sibling;
    Node* suffix_link;
    std::string edge_label;
    void add_child(Node*);
    int ID;
    Node* get_child(char);
    bool is_leaf() {return child == NULL;}
    void split_edge(int, int);
	void adopt_children(Node*);
};

