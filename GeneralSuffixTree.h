#pragma once

#include "SuffixTree.h"
#include "Overlap.h"
#include "StringMap.h"
#include <string>
#include <set>
#include <map>
#include <vector>
#include <utility>

class GeneralSuffixTree : public SuffixTree
{
public:
	GeneralSuffixTree(std::set<std::string>);
	typedef std::map<int, StringMap>& Mapping; 

	Overlap lookup(Overlap, Mapping) const;
	std::string extract_string(int);
};

