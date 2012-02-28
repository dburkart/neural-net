#include <iostream>
#include <fstream>
#include <vector>

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "datamanip.h"
#include "network.h"

using namespace std;

double sigmoid(double);
double sigmoidPrime(double);

/**
 * Constructor used for learning a new network. Takes in the number of layers
 * (including the input and output layers) and creates a network of size n - 1.
 * The output layer is incorporated in the last layer, and the input layer is
 * the inputs to the first hidden layer.
 * 
 * @param numLayers the number of layers in the network, including input laye
 * @param layersizes array containing the size of each layer
 */
Network::Network(int numLayers, int *layersizes) {
	srand(time(NULL));
	
	for (int i = 1; i < numLayers; i++) {
		Layer layer(layersizes[i], layersizes[i-1]);
		_layers.insert(_layers.end(), layer);
	}
	
	setActivation(&sigmoid, &sigmoidPrime);
}

/**
 * Overloaded constructor for loading in a neural network.
 *
 * @param filename file name of the neural network
 */
Network::Network(char *filename) {
	srand(time(NULL));
	load(filename);
	setActivation(&sigmoid, &sigmoidPrime);
}

/**
 * Convenience operator for selecting layers in the network.
 *
 * @param index the index of the layer to select
 */
Layer& Network::operator[](int index) {
	return (Layer &)_layers.at(index);
}

/**
 * Convenience function, returns the vector of outputs for this network.
 */
vector<double> Network::output() {
	vector<double> o;
	
	for (int i = 0; i < _layers[_layers.size() - 1].size(); i++) {
		o.insert(o.end(), _layers[_layers.size() - 1][i].output());
	}
	
	return o;
}

/**
 * Save this network to a file.
 *
 * @param filename name of the file to save the network to
 */
bool Network::save(char *filename) {
	ofstream file;
	file.open(filename);
	
	file << _layers.size() + 1 << " " << _layers[0][0].size() - 1 << " ";
	
	for (int i = 0; i < _layers.size(); i++) {
		file << _layers[i].size() << " ";
	}
	file << "\n";
	
	for (int i = 0; i < _layers.size(); i++) {
		for (int j = 0; j < _layers[i].size(); j++) {
			for (int k = 0; k < _layers[i][j].size(); k++) {
				file << _layers[i][j][k].weight << " ";
			}
			file << "\n";
		}
	}
	
	file.close();
	return true;
}

/**
 * Load a network from a file.
 *
 * @param filename the name of the file containing some network
 */
bool Network::load(char *filename) {
	ifstream file;
	vector<int> layersizes;
	
	file.open(filename);
	
	int n, sz;
	double m;
	file >> n;
	
	for (int i = 0; i < n; i++) {
		file >> sz;
		layersizes.insert(layersizes.end(), sz);
	}
	
	for (int i = 1; i < layersizes.size(); i++) {
		Layer layer(layersizes[i], layersizes[i-1]);
		for (int j = 0; j < layersizes[i]; j++) {
			for (int k = 0; k < layer[j].size(); k++) {
				file >> m;
				layer[j][k].weight = m;
			}
		}
		_layers.insert(_layers.end(), layer);
	}
	
	file.close();
	return true;
}

/**
 * This clunky little function sets the inputs to the network given 
 */
void Network::setInputs(vector<double> *ex) {
	int sz = ex->size();
	for (int i = 0; i < sz; i++) {
		_layers[0].set(i + 1, ex->at(i));
	}
}

/**
 * Propagate the inputs in the first hidden layer through the network.
 */
void Network::feedForward() {
	for (int i = 0; i < _layers.size(); i++) {
		if (i < _layers.size() - 1) {
			for (int j = 0; j < _layers[i].size(); j++) {
				double output = _layers[i][j].output();
				_layers[i + 1].set(j + 1, output);
			}
		}
	}
}

/**
 * Back-propagation function. 
 *
 * @param T vector of correct outputs
 * @param alpha value used to converge the network
 */
double Network::backprop(vector<double> *T, double alpha) {
	vector<double> E;
	double totalError = 0.0;
	
	//-- Calculate the initial deltas (E[]), and update the output vector 
	//-- weights while we're at it.
	int o = _layers.size() - 1;
	for (int i = 0; i < _layers[o].size(); i++) {
		E.insert(E.end(), (*T)[i] - _layers[o][i].output());
		double dx = _layers[o][i].derivative();
		
		for (int j = 0; j < _layers[o][i].size(); j++) {
			_layers[o][i][j].weight = _layers[o][i][j].weight + 
				(alpha * E[i] * dx * _layers[o][i][j].input);
		}
		
		totalError += fabs(E[i]);
	}
	
	//-- Propagate the values back through the network.
	for (int i = o - 1; i >= 0; i--) {
		vector<double> temp;
		for (int j = 0; j < _layers[i].size(); j++) {
			double delta = 0.0;
			
			for (int k = 0; k < _layers[i + 1].size(); k++) {
				delta = delta + (_layers[i + 1][k][j].weight * E[k]);
			}
			
			double dx = _layers[i][j].derivative();
			
			for (int k = 0; k < _layers[i][j].size(); k++) {
				_layers[i][j][k].weight = _layers[i][j][k].weight +
					(alpha * delta * dx * _layers[i][j][k].input);
			}
			
			temp.insert(temp.end(), delta);
		}
		E = temp;
	}
	
	return totalError;
}

/**
 * Sets the activation functions for this neural network. We don't ever use any
 * function other than a sigmoid, but we'll future proof this anyway.
 *
 * @param sigmoid g(x) - activation function
 * @param dx g'(x) - first derivative of the activation function
 */
void Network::setActivation(double(*sigmoid)(double), double(*dx)(double)) {
	for (int i = 0; i < _layers.size(); i++) {
		_layers.at(i).setActivation(sigmoid, dx);
	}
}

/**
 * Used for debugging purposes.
 */
void Network::display() {
	for (int i = 0; i < _layers.size(); i++) {
		_layers.at(i).display();
		cout << endl;
	}
}

double sigmoid(double sum) {
	return (double)(1 / (1 + exp(-sum)));
}

double sigmoidPrime(double x) {
	double g = sigmoid(x);
	return (double)(g * (1 - g));
}
