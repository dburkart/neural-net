#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "perceptron.h"

using namespace std;

/**
 * Default constructor, used if we are learning a new network. Sets up the
 * inputs and generates random weights.
 *
 * @param n the number of inputs to this perceptron.
 */
Perceptron::Perceptron(int n) {
	
	// Generate random weights
	_inputs.insert(_inputs.end(), (Dendrite){1.0, (double)rand() / (RAND_MAX)});
	for (int i = 0; i < n; i++) {
		_inputs.insert(_inputs.end(), (Dendrite){0.0, (double)rand() / (RAND_MAX)});
	}
}

/**
 * Overloaded constructor, used when we are loading a saved network.
 *
 * @param inputs the dendrites from the saved network.
 */
Perceptron::Perceptron(vector<Dendrite> inputs) {
	_inputs = inputs;
}

/**
 * Convenience operator so we can index the inputs of this perceptron like an
 * array.
 *
 * @param index the index of the input to get.
 */
Dendrite& Perceptron::operator[] (const int index) {
	return (Dendrite &)_inputs.at(index);
}

/**
 * Get the output of this perceptron after it 'fires'.
 */
double Perceptron::output() {
	return _sigmoid(sum());
}

/**
 * Get the derivative of this perceptron.
 */
double Perceptron::derivative() {
	return _sigmoidPrime(sum());
}

/**
 * Convenience function which returns the number of weights in this Perceptron.
 */
int Perceptron::size() {
	return _inputs.size();
}

/**
 * Set the activation function for this perceptron. This is so that we can
 * easily swap out activation functions in our network, if need be.
 *
 * @param sigmoid pointer to the activation function we are going to use.
 * @param dx derivative of the sigmoid function
 */
void Perceptron::setActivation(double(*sigmoid)(double), double(*dx)(double)) {
	_sigmoid = sigmoid;
	_sigmoidPrime = dx;
}

/**
 * Used for debugging.
 */
void Perceptron::display() {
	cout << "{ ";
	for (int i = 0; i < _inputs.size(); i++) {
		cout << _inputs.at(i).input << " ";
	}
	cout << "} => ";
	cout << "{ ";
	for (int i = 0; i < _inputs.size(); i++) {
		cout << _inputs.at(i).weight << " ";
	}
	
	cout << "} = " << output();
}

//---Private Functions--------------------------------------------------------//

/**
 * Compute the weighted sum of the inputs to this perceptron, and return it as a
 * double.
 */
double Perceptron::sum() {
	double s = 0.0;
	
	for (int i = 0; i < _inputs.size(); i++) {
		s += (_inputs.at(i).input * _inputs.at(i).weight);
	}
	
	return s;
}
