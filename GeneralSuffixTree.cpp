#include "GeneralSuffixTree.h"

#include "Node.h"

#include "Suffix.h"
#include <cmath>
#include <sstream>
#include <algorithm>

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
		character_index.resize(position, i);
	}
	SuffixTree::construct(to_build + "$");
}

std::string GeneralSuffixTree::get_string(int s) const {
	return tree_string.substr(string_index[s].first, string_index[s].second);
}