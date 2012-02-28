#include <iostream>

#include "layer.h"

using namespace std;

/** 
 * Constructor. Takes the size of the layer, and the size of the previous layer,
 * and creates the specified number of perceptrons.
 *
 * @param size size of this layer
 * @param prevSz size of the previous layer
 */
Layer::Layer(int size, int prevSz) {
	for (int i = 0; i < size; i++) {
		Perceptron p(prevSz);
		_nodes.insert(_nodes.end(), p);
	}
}

/**
 * Convenience operator for selecting nodes in this layer.
 *
 * @param index the node needed
 */
Perceptron& Layer::operator[](int index) {
	return (Perceptron &)_nodes.at(index);
}

/**
 * Returns the size of this layer
 */
int Layer::size() {
	return _nodes.size();
}

/**
 * Sets the ith input of each node within this layer. Used to propagate values
 * forward.
 *
 * @param input the index of the input to set
 * @param value the value to store
 */
void Layer::set(int input, double value) {
	for (int i = 0; i < _nodes.size(); i++) {
		_nodes.at(i)[input].input = value;
	}
}

/**
 * Sets the activation functions for this layer. We don't ever use any function 
 * other than a sigmoid, but we'll future proof this anyway.
 *
 * @param sigmoid g(x) - activation function
 * @param dx g'(x) - first derivative of the activation function
 */ 
void Layer::setActivation(double(*sigmoid)(double), double(*dx)(double)) {
	for (int i = 0; i < _nodes.size(); i++) {
		_nodes.at(i).setActivation(sigmoid, dx);
	}
}

/**
 * Used for debugging.
 */
void Layer::display() {
	cout << "=============" << endl;
	for (int i = 0; i < _nodes.size(); i++) {
		_nodes.at(i).display();
		cout << endl;
	}
}
