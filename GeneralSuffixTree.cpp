#include "GeneralSuffixTree.h"

#include "Node.h"

#include "Suffix.h"
#include <cmath>
#include <sstream>

GeneralSuffixTree::GeneralSuffixTree() {
}

void GeneralSuffixTree::construct(const std::vector<std::string>& strings) {
	std::string to_build;
	int position = 1;
	for (int i = 0; i < strings.size(); i++) {
		string_index.push_back(std::make_pair(position, strings[i].length()));
		std::stringstream convert;
		convert << i;
		std::string to_add = strings[i] + convert.str();
		to_build += to_add;
		position += to_add.length();
	}
	SuffixTree::construct(to_build);
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

void GeneralSuffixTree::label_nodes() {


}