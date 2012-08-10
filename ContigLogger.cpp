#include "ContigLogger.h"
#include <iostream>

void ContigLogger::log_contigs(GeneralSuffixTree& gst) {
	std::cout << "Contig logging..." << std::endl;
	freopen("contig_log", "w", stdout);
	
	for (int i = 0; i < gst.strings.size(); i++) {
		if (!gst.strings[i].empty()) 
			std::cout << "> Contig " << i << std::endl
			<< gst.strings[i] << std::endl;
	}
	std::cout << std::endl << "END OF CONTIGS" << std::endl;

	freopen( "CON", "w", stdout );
}
