#pragma once

#include "GeneralSuffixTree.h"
class Assembler
{
public:
	Assembler() {}
	void compute_overlaps(GeneralSuffixTree&);
	std::vector<std::vector<short int>> overlap_lengths;
	void label_nodes(GeneralSuffixTree&);
	void label_node(GeneralSuffixTree&, Node*);
	void print_overlaps(const GeneralSuffixTree&);
};

