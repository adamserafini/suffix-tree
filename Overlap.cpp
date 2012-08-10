#include "Overlap.h"
#include <cstring>

Overlap::Overlap(int string_i, int string_j, short int overlap) {
	this->string_i = string_i;
	this->string_j = string_j;
	this->overlap = overlap;
	left = NULL;
	right = NULL;
}

std::string Overlap::get_string(const GeneralSuffixTree& gst) const {
	return gst.strings[string_i] + gst.strings[string_j].substr(overlap);
}

bool Overlap::left_edge_merged(int string_number) {
	if (string_number == string_i && left != NULL)
		return true;
	else if (string_number == string_j)
		return true;
	else
		return false;
}

bool Overlap::right_edge_merged(int string_number) {
	if (string_number == string_j && right != NULL)
		return true;
	else if (string_number == string_i)
		return true;
	else
		return false;
}

void Overlap::merge_right(Overlap* overlap) {
	right = overlap;
	overlap->left = this;
}

void Overlap::merge_left(Overlap* overlap) {
	left = overlap;
	overlap->right = this;
}

bool Overlap::match_contig(Overlap* overlap) {
	Overlap* this_contig = this;
	Overlap* that_contig = overlap;
	while(this_contig->left != NULL)
		this_contig = this_contig->left;
	while(that_contig->left != NULL)
		that_contig = that_contig->left;
	return (this_contig == that_contig);
}


