#include "GeneralSuffixTree.h"


GeneralSuffixTree::GeneralSuffixTree(std::set<std::string> strings)
{
	int position = -1;
	std::string concat;
	std::set<std::string>::iterator it;
	for (it = strings.begin(); it != strings.end(); it++) {
		position += (*it).length() + 1;
		concat += (*it + "$");
		string_IDs.push_back(position);
	}	
	SuffixTree::construct(concat);
}
