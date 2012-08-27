#pragma once

#include "SuffixTree.h"
#include <string>
#include <set>
#include <vector>

class GeneralSuffixTree : public SuffixTree
{
public:
	GeneralSuffixTree(std::set<std::string>);
	int string_count;
};

