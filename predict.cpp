#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include "network.h"
#include "datamanip.h"

using namespace std;

int main(int argc, char **argv) {
	Network n(argv[1]);

	vector<vector<double> *> *data = readData(argv[2]);
	
	for (int i = 0; i < data->size(); i++) {
		vector<double> *d = data->at(i);
		
		n.setInputs(d);
		n.feedForward();
		
		vector<double> output = n.output();
		cout << "Obama: " << round(output[0]*100) << "%\tMcCain: ";
		cout << round(output[1]*100) << "%" << endl;
	}

	return 0;
}
