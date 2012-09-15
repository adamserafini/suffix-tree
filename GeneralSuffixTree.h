#pragma once

#include <set>
#include <string>
#include <map>
#include "SuffixTree.h"
#include "Overlap.h"
#include "StringMap.h"

class GeneralSuffixTree : public SuffixTree
{
public:
	GeneralSuffixTree(std::set<std::string>);
	typedef std::map<int, StringMap>& Mapping; 
	Overlap lookup(Overlap, Mapping) const;
	std::string extract_string(int);
};

