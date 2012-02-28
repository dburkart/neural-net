#ifndef __DATA_MANIP_H__
#define __DATA_MANIP_H__

#include <fstream>
#include <vector>

#include "network.h"

/**
 * Read in CSV-style data and extract the relevant fields.
 *
 * @param filename name of the file containing the data
 */
inline std::vector<std::vector<double> *> *readData(char *filename) {
	std::ifstream in;
	in.open(filename);
	
	std::vector<std::vector<double> *> *examples = new std::vector<std::vector<double> *>;
	
	while (in.good() && !in.eof()) {
		std::vector<double> *data = new std::vector<double>;
		
		for (int i = 0; i < 83; i++) {
			double ex;
			char comma;
			
			in >> ex;
			if (i % 82 != 0 || i == 0) in >> comma;
			
			switch (i) {
				case 36: //-- Education % (B.A or higher)
					data->insert(data->end(), (ex / 100.0));
					break;
				case 49: //-- People in poverty (%)
					data->insert(data->end(), (ex / 100.0));
					break;
				case 51: //-- Personal earnings per capita
					data->insert(data->end(), (ex / 132728.0));
					break;
				case 82: //-- Population per square mile
					data->insert(data->end(), (ex / 66834.6));
					break;
			}
		}
		
		examples->insert(examples->end(), data);
	}
	
	in.close();
	
	examples->erase(examples->end() - 1);
	
	return examples;
}

#endif

