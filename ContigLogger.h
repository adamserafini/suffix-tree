#pragma once
#include <set>
#include "Overlap.h"

class ContigLogger
{
public:
	ContigLogger() {}
	void log_contigs(std::set<Overlap*>, const GeneralSuffixTree&);
};

