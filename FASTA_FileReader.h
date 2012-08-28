#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

class FASTA_FileReader {
public:
    FASTA_FileReader(std::string);
    std::set<std::string> parse();
    std::ifstream infile;
};