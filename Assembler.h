#pragma once
#include <string>

class GeneralSuffixTree;
class Assembler
{
public:
	Assembler();
	void label_nodes(GeneralSuffixTree&);
	std::string greedy_SCS(GeneralSuffixTree&);
};

