#include "FASTA_FileReader.h"
#include <cassert>
#include <sstream>

FASTA_FileReader::FASTA_FileReader(std::string filename) {
    infile.open(filename.c_str());
	assert(!infile.fail());
}

void FASTA_FileReader::parse(std::vector<std::string>& strings) {
	std::string current_string;
    std::string current_line;
    while (std::getline(infile, current_line)) {
		if (!current_line.empty() && current_line[0] != '>')
			current_string += current_line;
		else if (!current_string.empty()) {
			strings.push_back(current_string);
			current_string.clear();
		}
    }
	strings.push_back(current_string);
}
