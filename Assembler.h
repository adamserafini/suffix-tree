#pragma once
#include <string>
#include <vector>
#include "Overlap.h"
#include "Suffix.h"

class GeneralSuffixTree;
class Assembler
{
public:
	Assembler();
	std::vector<Overlap> overlaps;

	void label_nodes(GeneralSuffixTree&);
	void get_overlaps(GeneralSuffixTree&);
	void push_overlap(GeneralSuffixTree& gst, std::string, int);
	std::string greedy_SCS(GeneralSuffixTree&);
	
};

