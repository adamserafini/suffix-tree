#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h" 
#include <iostream>
#include <sstream>


SuffixTree::SuffixTree(std::string s) {
    length = s.length();
    tree_string = ' ' + s;
    internal_node_ID = 0;
	current_end = new int(0);
    root = new Node(NULL, 1, new int (0), internal_node_ID);
	root->suffix_link = root;
}

void SuffixTree::construct() {
	(*current_end)++;
	last_leaf_extension = new Node(root, 1, current_end, 1);
    root->add_child(last_leaf_extension);

    for (int i = 1; i < length; i++) {
        SPA(i);
		//log_tree();
		if (i % 100 == 0) std::cerr << "Phase: " << i << std::endl;
    }
}

//SPA: Single Phase Algorithm (Gusfield, 1997)
void SuffixTree::SPA(int i) { 
	Suffix previous_suffix(last_leaf_extension, *current_end);
	(*current_end)++;
	
	int j;
    for (j = (last_leaf_extension->ID + 1); j <= (i + 1); j++) {
		Rule rule_applied = SEA(previous_suffix, j, i);
		if (rule_applied == RULE_3) 
			break;
		//log_tree();
    }
}

//SEA: Single Extension Algorithm (Gusfield, 1997)
SuffixTree::Rule SuffixTree::SEA(Suffix& previous_suffix, int j, int i) {
	int begin_index, end_index;
	Node* origin = previous_suffix.walk_up(begin_index, end_index);
	Suffix suffix = (origin == root ? get_suffix(root, j, i)
		: get_suffix(origin->suffix_link, begin_index, end_index));

	Rule rule_applied;
    if (suffix.RULE2_conditions(*this, tree_string[i + 1])) {
		RULE2(suffix, i + 1, j);
		rule_applied = RULE_2;
	}
	else rule_applied = RULE_3;
	
	if (previous_suffix.new_internal_node)
		previous_suffix.node->suffix_link = suffix.node;
	previous_suffix = suffix;
	return rule_applied;
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


//depth first tree traversal to gather leaf IDs below a given suffix
std::vector<int> SuffixTree::retrieve_leaves(const Suffix& suffix) const {
	std::vector<int> leaf_IDs;
	std::vector<Node*> nodes_to_visit (1, suffix.node);

	while (!nodes_to_visit.empty()) {
		Node* current_node = nodes_to_visit.back();
		nodes_to_visit.pop_back();
		if (current_node->is_leaf()) 
			leaf_IDs.push_back(current_node->ID);
		else
			current_node->get_children(nodes_to_visit);
	}
	return leaf_IDs;
}


std::string SuffixTree::get_substr(int start_pos, int end_pos) {
    if (start_pos > end_pos) return std::string();
    return tree_string.substr(start_pos, end_pos - start_pos + 1);
}

void SuffixTree::RULE2(Suffix& suffix, int char_index, int new_leaf_ID) {
    if (!suffix.ends_at_node()) {  //eg. case 2 (path ends inside an edge)
		suffix.node->split_edge(suffix.char_index, --internal_node_ID);
		suffix.node = suffix.node->parent;
		suffix.new_internal_node = true;
	}
	Node* new_leaf = new Node(suffix.node, char_index, current_end, new_leaf_ID);  
    suffix.node->add_child(new_leaf);
	last_leaf_extension = new_leaf;
}

void SuffixTree::log_tree() {
    log_node(root);
	std::cout << "END OF TREE" << std::endl;
}

void SuffixTree::log_node(Node* parent) {
	static unsigned int line_count;
	static const unsigned int LINES_PER_FILE = 20000;
	std::stringstream file_number;

    int parent_ID = parent->ID;
    Node* child = parent->child;
    while (child != NULL) {
		if (line_count % LINES_PER_FILE == 0) {
			file_number << ((line_count / LINES_PER_FILE) + 1);
			freopen(("log_file" + file_number.str()).c_str(), "w", stdout);
		}
        std::cout << parent_ID 
                  << " " << get_substr(child->begin_index, *child->end_index) 
                  << " " << child->ID << std::endl;
		line_count++;
        log_node(child);
        child = child->sibling;
    } 
}