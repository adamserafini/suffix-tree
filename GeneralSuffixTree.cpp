#include "GeneralSuffixTree.h"


GeneralSuffixTree::GeneralSuffixTree(std::set<std::string> strings)
{
	std::string concat;
	std::set<std::string>::iterator it;
	for (it = strings.begin(); it != strings.end(); it++)
		concat += (*it + "$");
	SuffixTree::construct(concat);
}
