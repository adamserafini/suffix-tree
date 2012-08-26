#pragma once

#include "SuffixTree.h"
#include <string>
#include <set>

class GeneralSuffixTree : public SuffixTree
{
public:
	GeneralSuffixTree(std::set<std::string>);
};

