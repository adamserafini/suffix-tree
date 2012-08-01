#pragma once

#include <vector>
#include "SuffixTree.h"

class GeneralSuffixTree : public SuffixTree
{
public:
	GeneralSuffixTree(std::string);
	void get_leaves(std::vector<Node*>&);
	void tidy_leaves();
};


