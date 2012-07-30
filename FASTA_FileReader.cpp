#include "FASTA_FileReader.h"
#include <cassert>
#include <sstream>

FASTA_FileReader::FASTA_FileReader(std::string filename) {
    infile.open(filename.c_str());
	assert(!infile.fail());
}

std::string FASTA_FileReader::parse() {


     std::stringstream buffer;

        buffer << infile.rdbuf();

        infile.close();

	std::string to_return;
	char ch;
	int string_count = 0;
	buffer.ignore(INT_MAX, '\n'); //ignore first line
	while (buffer.get(ch)){
		if (ch == '>') {
			buffer.ignore(INT_MAX, '\n');
			std::stringstream convert;
			convert << string_count++;
			to_return += convert.str();
		}
		else if (ch != '\n')
			to_return += ch;
	}
	std::stringstream convert;
	convert << string_count++;
	to_return += convert.str();
	return to_return;
}
