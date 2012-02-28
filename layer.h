#ifndef __LAYER_H__
#define __LAYER_H__

#include <vector>

#include "perceptron.h"

/**
 * The layer class is essentially a vector of Perceptrons, with some helper
 * functions.
 */
class Layer {
	public:
		Layer(int, int);
		~Layer() {}
	
		Perceptron& operator[] (int index);
		
		int size();
		
		void set(int, double);
		void setActivation(double(*sigmoid)(double), double(*dx)(double));
		void display();
	
	private:
		std::vector<Perceptron> _nodes;
};

#endif
