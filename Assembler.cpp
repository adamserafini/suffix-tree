#include "Assembler.h"

#include "GeneralSuffixTree.h"
#include "Node.h"

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



std::string Assembler::greedy_SCS(GeneralSuffixTree& gst) {
	return "not yet";
}
