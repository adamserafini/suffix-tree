#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FASTA_FileReader {
public:
    FASTA_FileReader(std::string);
    void parse(std::vector<std::string>&);
    std::ifstream infile;
};