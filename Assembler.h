#pragma once
#include <string>
#include <vector>
#include <map>

class StringMap;
class Overlap;
class GeneralSuffixTree;
class Assembler
{
public:
	Assembler();
	void label_nodes(GeneralSuffixTree&);
	void push_overlap(GeneralSuffixTree& gst, std::string, int);
	void initialise_greedy_SCS(GeneralSuffixTree&);
	void greedy_SCS(GeneralSuffixTree&);
	int merge_strings(Overlap);
	std::string get_SCS(GeneralSuffixTree&);

	std::vector<Overlap> overlaps;
	std::map<int, StringMap> mapping; 
	int left_handle;
};

