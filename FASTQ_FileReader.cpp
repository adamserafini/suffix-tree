#include "FASTQ_FileReader.h"
#include <cassert>

FASTQ_FileReader::FASTQ_FileReader(std::string filename)
{
	infile.open(filename.c_str());
	assert(!infile.fail());
}

std::set<std::string> FASTQ_FileReader::parse() {
	std::set<std::string> to_return;
	std::string current_string;
    std::string current_line;
    while (std::getline(infile, current_line)) {
		if (current_line[0] == '@') {
			std::getline(infile, current_line);
			to_return.insert(current_line);
		}
    }
    return to_return;
}


