#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FASTA_FileReader {
public:
    FASTA_FileReader(std::string);
    std::vector<std::string> parse();
    std::ifstream infile;
};