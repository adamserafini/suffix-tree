#include "ContigLogger.h"
#include <iostream>

void ContigLogger::log_contigs(	std::set<Overlap*> contigs, const GeneralSuffixTree& gst) {
	std::cout << "Contig logging..." << std::endl;
	freopen("contig_log", "w", stdout);
	std::set<Overlap*>::iterator it; 
	int contig_number = 1;
	for (it = contigs.begin(); it != contigs.end(); ++it) {
		std::cout << "> CONTIG " << contig_number << std::endl;
		Overlap* reader = *it;
		while (reader->left != NULL)
			reader = reader->left;
		while (reader != NULL) {
			std::cout << reader->get_string(gst);
			reader = reader->right;
		}
		std::cout << std::endl;
		contig_number++;
	}
	freopen( "CON", "w", stdout );
}
