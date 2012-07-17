#include "FASTA_FileReader.h"


FASTA_FileReader::FASTA_FileReader(std::string filename) {
    infile.open(filename.c_str());
}

std::string FASTA_FileReader::parse() {
    std::string to_return;
    std::string s;
    std::getline(infile, s); //ignore first line
    while (std::getline(infile, s)) {
        to_return += s;
    }
    return to_return;
}
