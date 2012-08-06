#pragma once

#include "GeneralSuffixTree.h"
#include "Overlap.h"
class Assembler
{
public:
	Assembler(int o) : min_overlap(o), head(NULL) {}
	void compute_overlaps(GeneralSuffixTree&);
	void label_nodes(GeneralSuffixTree&);
	void label_node(GeneralSuffixTree&, Node*);
	Overlap* head;
	void add_overlap(int, int, short int);
	std::vector<std::pair<Overlap*, Overlap*>> assembled_overlaps;
	void print_overlaps(const GeneralSuffixTree&);
	int min_overlap;
};

