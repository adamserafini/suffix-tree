#include "SuffixTree.h"
#include "Node.h"
#include "Suffix.h" 
#include <iostream>
#include <sstream>


SuffixTree::SuffixTree() {
    internal_node_ID = 0;
	current_end = new int(0);
    root = new Node(NULL, 1, new int (0), internal_node_ID);
	root->suffix_link = root;
}

void SuffixTree::construct(const std::string& s) {
	length = s.length();
    tree_string = ' ' + s;

	(*current_end)++;
	last_leaf_extension = new Node(root, 1, current_end, 1);
    root->add_child(last_leaf_extension);

    for (int i = 1; i < length; i++) {
        SPA(i);
		//log_tree();
		if (i % 10000 == 0) std::cerr << "Phase: " << i << std::endl;
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

//Match a string from the root of the tree
Suffix SuffixTree::match_string(std::string string) const {
	int char_index;
	Node* current_node = root;
	while (!string.empty()) {
		current_node = current_node->get_child(*this, string[0]);
		if (current_node == NULL)
			return Suffix(NULL, 0);
		else {
			char_index = current_node->begin_index;
			int i = 1;
			for ( ; i < string.length() && i < current_node->edge_length(); i++)
				if (string[i] != tree_string[char_index + i]) 
					return Suffix(NULL, 0);
			string.erase(0, i);
		}
	}
	return Suffix(current_node, char_index);
}

std::vector<int> SuffixTree::get_exact_matches(std::string string) const {
	Suffix suffix = match_string(string);
	if (suffix.node == NULL)
		return std::vector<int>();
	else {
		std::vector<Node*> leaves = retrieve_leaves(suffix);
		std::vector<int> to_return;
		for (int i = 0; i < leaves.size(); i++)
			to_return.push_back(leaves[i]->ID);
		return to_return;
	}
}

//depth first tree traversal to gather leaf IDs below a given suffix
std::vector<Node*> SuffixTree::retrieve_leaves(const Suffix& suffix) const {
	std::vector<Node*> leaves;
	std::vector<Node*> nodes_to_visit (1, suffix.node);

	while (!nodes_to_visit.empty()) {
		Node* current_node = nodes_to_visit.back();
		nodes_to_visit.pop_back();
		if (current_node->is_leaf()) 
			leaves.push_back(current_node);
		else
			current_node->get_children(nodes_to_visit);
	}
	return leaves;
}


std::string SuffixTree::get_substr(int start_pos, int end_pos) const {
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

//recursive algorithm to retrieve all path labels below a certain node;
void SuffixTree::retrieve_paths(Node* node, std::string string, std::vector<std::string>& to_return) const {
	std::string this_string = get_substr(node->begin_index, *node->end_index);
	string += this_string;
	if (node->is_leaf())
		to_return.push_back(string);
	else {
		std::vector<Node*> children;
		node->get_children(children);
		for (int i = 0; i < children.size(); i++)
			retrieve_paths(children[i], string, to_return);
	}
}

void SuffixTree::log_tree() {
    log_node(root);
	std::cout << "END OF TREE" << std::endl;
	freopen( "CON", "w", stdout );
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
		std::cout << "\"" << parent->ID << ": {";
		for (int i = 0; i < parent->node_labels.size(); i++)
			std::cout << parent->node_labels[i] << ",";
		std::cout << "}\" -> ";
		std::cout << "\"" << child->ID << ": {";
		for (int i = 0; i < child->node_labels.size(); i++)
			std::cout << child->node_labels[i] << ",";
		std::cout << "}\"";
		std::cout << " [label = \"" 
				  << get_substr(child->begin_index, *child->end_index) 
				  << "\"];" << std::endl;
		line_count++;
        log_node(child);
        child = child->sibling;
    } 
}