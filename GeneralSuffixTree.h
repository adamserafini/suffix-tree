#pragma once

#include <vector>
#include "SuffixTree.h"


class GeneralSuffixTree : public SuffixTree
{
public:
	GeneralSuffixTree(std::string);
	void tidy_leaves();
};


