#include "GeneralSuffixTree.h"

#include "Node.h"

#include "Suffix.h"

GeneralSuffixTree::GeneralSuffixTree(std::string s) : SuffixTree(s) {
}

void GeneralSuffixTree::tidy_leaves() {
	std::vector<Node*> leaves = retrieve_leaves(Suffix(root, 0));

	for (int i = 0; i < leaves.size(); i++) {
		int index = leaves[i]->begin_index;
		while (!isdigit(tree_string[index]))
			index++;
		while (index < *leaves[i]->end_index
			&& isdigit(tree_string[index + 1]))
			index++;
		leaves[i]->end_index = new int(index);
	}
}