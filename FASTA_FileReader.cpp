#include "FASTA_FileReader.h"
#include <cassert>

FASTA_FileReader::FASTA_FileReader(std::string filename) {
    infile.open(filename.c_str());
	assert(!infile.fail());
}

std::vector<std::string> FASTA_FileReader::parse() {
    std::vector<std::string> to_return;
	std::string current_string;
    std::string current_line;
    while (std::getline(infile, current_line)) {
		if (!current_line.empty() && current_line[0] != '>')
			current_string += current_line;
		else if (!current_string.empty()) {
			to_return.push_back(current_string);
			current_string.clear();
		}
    }
	if (!current_string.empty())
		to_return.push_back(current_string);
    return to_return;
}
