#pragma once

#include <string>
#include <fstream>
#include <set>

class FASTQ_FileReader
{
public:
	FASTQ_FileReader(std::string);
	std::set<std::string> parse();
	std::ifstream infile;
};

