#include <sstream>
#include <algorithm>
#include <iostream>

#include "Assembler.h"
#include "Node.h"
#include "Suffix.h"

void Assembler::compute_overlaps(GeneralSuffixTree& gst) {
	int number_of_strings = gst.string_index.size();
	overlap_lengths.resize(number_of_strings);
	for (int i = 0; i < number_of_strings; i++)
		overlap_lengths[i].resize(number_of_strings);

	label_nodes(gst);

	for (int j = 0; j < number_of_strings; j++) {
		Node* x = gst.root;
		int depth = 0;
		while (!x->is_leaf()) {
			for (int i = 0; i < x->node_labels.size(); i++) {
				int min_length = std::min(	gst.string_index[x->node_labels[i]].second,
											gst.string_index[j].second);
				overlap_lengths[x->node_labels[i]][j] = std::min(min_length, depth);
			}
			x = x->get_child(gst, gst.tree_string[gst.string_index[j].first + depth]);
			depth += x->edge_length();
		}
		overlap_lengths[j][j] = gst.string_index[j].second;
	}
}

void Assembler::label_nodes(GeneralSuffixTree& gst) {
	std::vector<Node*> nodes_to_visit (1, gst.root);
	//depth first traversal to visit all alpha nodes
	while (!nodes_to_visit.empty()) {
		std::cout << "I entered the label nodes loop!" << std::endl;
		Node* current_node = nodes_to_visit.back();
		nodes_to_visit.pop_back();
		label_node(gst, current_node);
		if (!current_node->is_leaf()) 
			current_node->get_children(nodes_to_visit);
	}
}

void Assembler::label_node(GeneralSuffixTree& gst, Node* node) {
	std::vector<Node*> children;
	node->get_children(children);
	for (int i = 0; i < children.size(); i++) {
		if (isdigit(gst.tree_string[children[i]->begin_index])) {
		std::vector<Node*> leaves = gst.retrieve_leaves(Suffix(children[i], *children[i]->end_index));
		for (int j = 0; j < leaves.size(); j++)
			node->node_labels.push_back(gst.character_index[leaves[j]->ID]);
		}
	}
}

void Assembler::print_overlaps(const GeneralSuffixTree& gst) {
	for (int i = 0; i < overlap_lengths.size(); i++) {
		for (int j = 0; j < overlap_lengths[i].size(); j++)
			std::cout << "Strings: " << gst.tree_string.substr(gst.string_index[i].first, gst.string_index[i].second) << "/" 
			<< gst.tree_string.substr(gst.string_index[j].first, gst.string_index[j].second) <<
			" overlap by: " << overlap_lengths[i][j] << std::endl;
	}
}



