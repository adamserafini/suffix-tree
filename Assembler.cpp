#include "Assembler.h"
#include "GeneralSuffixTree.h"
#include "Node.h"
#include <cassert>

Assembler::Assembler()
{
}

void Assembler::label_nodes(GeneralSuffixTree& gst) {
	std::vector<Node*> to_visit (1, gst.root);
	while (!to_visit.empty()) {
		Node* current_node = to_visit.back();
		to_visit.pop_back();

		std::vector<Node*> children;
		current_node->get_children(children);
		for (int i = 0; i < children.size(); i++) {
			if (gst.tree_string[children[i]->begin_index] == '$')
				current_node->labels.push_back(children[i]->begin_index);
		}
		to_visit.insert(to_visit.end(), children.begin(), children.end());
	}
}

void Assembler::get_overlaps(GeneralSuffixTree& gst) {
	std::string to_match;
	for (int i = 1; i < gst.tree_string.length(); i++) {
		if (gst.tree_string[i] != '$')
			to_match += gst.tree_string[i];
		else {
			push_overlap(gst, to_match, i);
			to_match.clear();
		}
	}
}

void Assembler::push_overlap(GeneralSuffixTree& gst, std::string string, int string_right) 
{
	int depth = 0;
	int deepest_overlap;
	Node* node = gst.root;
	Node* deepest_node;
	while (!string.empty()) {
		if (!node->labels.empty()) {
			deepest_overlap = depth;
			deepest_node = node;
		}
		node = node->get_char_child(gst, string[0]);
		depth += node->edge_length();
		string.erase(0, node->edge_length());
	}
	overlaps.push_back(Overlap(	deepest_node, 
								deepest_node->labels.front(),
								string_right, 
								deepest_overlap));
}

std::string Assembler::greedy_SCS(GeneralSuffixTree& gst) {
	return "not yet";
}
