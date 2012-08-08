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
	int i_position = gst.string_index[string_i].first;
	int i_length = gst.string_index[string_i].second;
	int j_position = gst.string_index[string_j].first;
	int j_length = gst.string_index[string_j].second;
	j_position += overlap;
	j_length -= overlap;

	return gst.tree_string.substr(i_position, i_length)
			+ gst.tree_string.substr(j_position, j_length);
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
	if (string_number = string_j && right != NULL)
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


