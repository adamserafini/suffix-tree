#pragma once

#include <vector>
#include "SuffixTree.h"
#include <utility>

class GeneralSuffixTree : public SuffixTree
{
public:
	GeneralSuffixTree();
	void construct(const std::vector<std::string>&);
	std::vector<std::pair<int, int>> string_index;
	void tidy_leaves();
	void label_nodes();
};



