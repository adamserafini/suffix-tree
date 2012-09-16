#include "GeneralSuffixTree.h"
#include "Node.h"

GeneralSuffixTree::GeneralSuffixTree(std::set<std::string> strings)
{
	std::string concat;
	std::set<std::string>::iterator it;
	for (it = strings.begin(); it != strings.end(); it++)
		concat += (*it + "$");
	SuffixTree::construct(concat);
}

Overlap GeneralSuffixTree::lookup(Overlap to_lookup, Mapping strings) const
{
	int depth = to_lookup.overlap;
	int string_right = to_lookup.string_right;
	int overlap = to_lookup.overlap;
	Node* node = to_lookup.node;
	while(true) {
		for (int i = 0; i < node->labels.size(); i++) {
			int string_left = node->labels[i];
			if (string_left != string_right
				&& string_left != (strings[string_right]).right_end
				&& !strings[string_left].deleted)
					return Overlap(node, string_left, string_right, depth);
		}
		depth -= node->edge_length();
		node = node->parent;
	}
}

std::string GeneralSuffixTree::extract_string(int string_ID) const {
	std::string to_return;
	for (int i = string_ID - 1; tree_string[i] != '$'; i--)
		to_return = tree_string[i] + to_return;
	return to_return;
}
