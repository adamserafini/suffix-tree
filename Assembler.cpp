#include <sstream>
#include <algorithm>
#include <iostream>
#include <utility>

#include "Assembler.h"
#include "Node.h"
#include "Suffix.h"
#include "ContigLogger.h"

void Assembler::compute_overlaps(GeneralSuffixTree& gst) {
	label_nodes(gst);
	for (int j = 0; j < gst.string_index.size(); j++) {
		std::vector<int> overlap_vector (gst.string_index.size(), 0);
		if (j % 1000 == 0) std::cout << "Computing overlaps for string: " << j << std::endl;
		Node* x = gst.root;
		int depth = 0;
		while (!x->is_leaf()) {
			for (int i = 0; i < x->node_labels.size(); i++) {
					int min_length = std::min(	gst.string_index[x->node_labels[i]].second,
												gst.string_index[j].second);
					if (x->node_labels[i] != j)
						overlap_vector[x->node_labels[i]] = std::min(depth, min_length);
			}
			x = x->get_child(gst, gst.tree_string[gst.string_index[j].first + depth]);
			depth += x->edge_length();
		}
		for (int i = 0; i < overlap_vector.size(); i++) {
				if (overlap_vector[i] > 0)
					add_overlap(i, j, overlap_vector[i]);
		}
	}
	counting_sort();
}

void Assembler::counting_sort() {
	std::vector<int> count(max_overlap - min_overlap + 1, 0);
	for (int i = 0; i < overlaps.size(); i++)
		count[overlaps[i]->overlap - min_overlap]++;
	int total = 0;
	for (int i = 0; i < count.size(); i++) {
		int c = count[i];
		count[i] = total;
		total = total + c;
	}
	std::vector<Overlap*> sorted_overlaps(overlaps.size());
	for (int i = 0; i < overlaps.size(); i++) {
		sorted_overlaps[count[overlaps[i]->overlap - min_overlap]] = overlaps[i];
		count[overlaps[i]->overlap - min_overlap]++;
	}
	overlaps = sorted_overlaps;
}

void Assembler::label_nodes(GeneralSuffixTree& gst) {
	std::vector<Node*> nodes_to_visit (1, gst.root);
	std::vector<int> depth_stack (1, 0);
	while (!nodes_to_visit.empty()) {
		Node* current_node = nodes_to_visit.back();
		int current_depth = depth_stack.back();
		nodes_to_visit.pop_back();
		depth_stack.pop_back();
		if (current_depth >= min_overlap)
			label_node(gst, current_node);
		if (!current_node->is_leaf()) {
			current_node->get_children(nodes_to_visit);
			current_node->get_child_depths(current_depth, depth_stack);
		}
	}
}

void Assembler::label_node(GeneralSuffixTree& gst, Node* node) {
	static int node_number = 0;
	node_number++;
	if (node_number % 1000 == 0) std::cout << "Labelling node: " << node_number << std::endl;
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

void Assembler::add_overlap(int string_i, int string_j, short int overlap) {
	if (overlap > max_overlap)
		max_overlap = overlap;
	Overlap* to_add = new Overlap(string_i, string_j, overlap);
	overlaps.push_back(to_add);
}

void Assembler::print_overlaps(const GeneralSuffixTree& gst) {
	std::cout << "entered print overlaps" << std::endl;
	freopen("overlap_log", "w", stdout);
	for (int i = 0; i < overlaps.size(); i++) {
		int string_i = overlaps[i]->string_i;
		int string_j = overlaps[i]->string_j;
		std::cout << "Strings: " 
		<< gst.tree_string.substr(	gst.string_index[string_i].first, 
									gst.string_index[string_i].second) 
		<< "/" 
		<< gst.tree_string.substr(	gst.string_index[string_j].first, 
									gst.string_index[string_j].second) 
		<< " overlap by: " << overlaps[i]->overlap << std::endl;
	}
	freopen( "CON", "w", stdout );
}

std::set<Overlap*> Assembler::merge_overlaps(const GeneralSuffixTree& gst) {
	std::cout << "Entered merge overlaps.. " << std::endl;
	int string_count = gst.string_index.size();
	std::vector<Overlap*> merged (string_count, NULL);
	std::set<Overlap*> contigs;
	int top = overlaps.size() - 1;
	while (top >= 0) {
		int string_i = overlaps[top]->string_i;
		int string_j = overlaps[top]->string_j;
		std::string string_left = gst.get_string(string_i);
		std::string string_right = gst.get_string(string_j);

		if (top % 10000 == 0) std::cerr << "Top = " << top << std::endl;

		if (merged[string_i] != NULL)
		std::cerr << std::boolalpha << (merged[string_i] != NULL) <<
					merged[string_i]->left_edge_merged(string_i) <<
					!merged[string_i]->right_edge_merged(string_i) <<
					(merged[string_j] == NULL) << std::endl;

		if (merged[string_i] == NULL && merged[string_j] == NULL) {
			merged[string_i] = merged[string_j] = overlaps[top];
			contigs.insert(overlaps[top]);
		} 
		else if (merged[string_i] != NULL 
					&& merged[string_i]->left_edge_merged(string_i)
					&& !merged[string_i]->right_edge_merged(string_i) 
					&& merged[string_j] == NULL) {
						merged[string_i]->merge_right(overlaps[top]);
						merged[string_j] = merged[string_i];
		}
		else if (merged[string_j] != NULL
					&& merged[string_j]->right_edge_merged(string_j)
					&& !merged[string_j]->left_edge_merged(string_j)
					&& merged[string_i] == NULL) {
						merged[string_j]->merge_left(overlaps[top]);
						merged[string_i] = merged[string_j];
		}
		else if (merged[string_i] != NULL && merged[string_j] != NULL
					&& !merged[string_i]->match_contig(merged[string_j])
					&& merged[string_i]->left_edge_merged(string_i)
					&& !merged[string_i]->right_edge_merged(string_i)
					&& merged[string_j]->right_edge_merged(string_j)
					&& !merged[string_j]->left_edge_merged(string_j)) {
						merged[string_i]->merge_right(overlaps[top]);
						merged[string_j]->merge_left(overlaps[top]);
						contigs.erase(contigs.find(merged[string_j]));
		}
		ContigLogger logger;
		logger.log_contigs(contigs, gst);
		top--;
	}
	return contigs;
}