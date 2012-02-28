#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include "network.h"
#include "datamanip.h"

using namespace std;

vector<vector<double> *> *readTrainingData(char *);

//-- Array containing the size of each layer in the network. We must be careful
//-- that the number of inputs matches how much data we are scraping in the
//-- readData function in datamanip.h
int networkSizes[] = {4, 3, 2};

int main(int argc, char ** argv) {
	vector<vector<double> *> *exampleSet = readData(argv[2]);
	vector<vector<double> *> *trainingSet = readTrainingData(argv[3]);
	
	Network n(3, (int *)&networkSizes);
	
	double alpha = .9;
	while (true) {
		double error = 0.0;
		for (int i = 0; i < exampleSet->size(); i++) {
			n.setInputs(exampleSet->at(i));
			n.feedForward();
			error += n.backprop(trainingSet->at(i), alpha);
		}
		n.save(argv[1]);
		cout << error << endl;
		if (alpha <= .00001 || error <= .001) break;
		alpha -= .00001;
	}
	
	return 0;
}

/**
 * This helper function reads in answer data from a file and returns it in a
 * two-dimensional vector.
 *
 * @param filename the name of the file containing the data
 */
vector<vector<double> *> *readTrainingData(char *filename) {
	ifstream in;
	in.open(filename);
	
	vector<vector<double> *> *trainingSet = new vector<vector<double> *>;
	
	do {
		vector<double> *row = new vector<double>;
		double obama, mccain;
		
		in >> obama;
		in >> mccain;
		
		row->insert(row->end(), obama);
		row->insert(row->end(), mccain);
		
		trainingSet->insert(trainingSet->end(), row);
	} while (in.peek() != ifstream::traits_type::eof());
	
	in.close();
	
	trainingSet->erase(trainingSet->end() - 1);
	
	return trainingSet;
}
