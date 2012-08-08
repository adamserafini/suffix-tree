#include "ContigLogger.h"
#include <iostream>

void ContigLogger::log_contigs(	std::set<Overlap*> contigs, const GeneralSuffixTree& gst) {
	std::cout << "Contig logging..." << std::endl;
	//freopen("contig_log", "w", stdout);
	std::set<Overlap*>::iterator it; 
	int contig_number = 1;
	for (it = contigs.begin(); it != contigs.end(); ++it) {
		std::cout << "> CONTIG " << contig_number << std::endl;
		Overlap* reader = *it;
		while (reader->left != NULL)
			reader = reader->left;
		std::cout << reader->get_string(gst);
		while (reader->right != NULL) {
			reader = reader->right;
			std::cout << reader->get_string(gst)
							.substr(gst.string_index[reader->string_i].second);
		}
		std::cout << std::endl;
		contig_number++;
	}
	std::cout << std::endl;
	//freopen( "CON", "w", stdout );
}
