#pragma once
#include <vector>

#include "GeneralSuffixTree.h"
#include "Overlap.h"
class Assembler
{
public:
	Assembler(int min, int max) : min_overlap(min), max_overlap(max), head(NULL) {}
	void compute_overlaps(GeneralSuffixTree&);
	void label_nodes(GeneralSuffixTree&);
	void label_node(GeneralSuffixTree&, Node*);
	Overlap* head;
	void add_overlap(int, int, short int);
	std::vector<Overlap*> overlaps;
	void counting_sort();
	std::vector<std::pair<Overlap*, Overlap*>> assembled_overlaps;
	void print_overlaps(const GeneralSuffixTree&);
	int min_overlap;
	int max_overlap;
};

