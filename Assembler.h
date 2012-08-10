#pragma once
#include <vector>

#include "GeneralSuffixTree.h"
#include "Overlap.h"
#include <set>

class Assembler
{
public:
	Assembler(int min) : min_overlap(min), max_overlap(0) {}
	void compute_overlaps(GeneralSuffixTree&);
	void label_nodes(GeneralSuffixTree&);
	void label_node(GeneralSuffixTree&, Node*);
	void add_overlap(int, int, short int);
	std::vector<Overlap*> overlaps;
	std::vector<std::vector<Overlap*>> matrix;
	void counting_sort();
	void merge_overlaps(GeneralSuffixTree&);
	void print_overlaps(const GeneralSuffixTree&);
	int min_overlap;
	int max_overlap;
};

