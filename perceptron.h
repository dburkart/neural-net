#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include <vector>

/**
 * The Dendrite structure is a convenience data type, simply an input / weight
 * pair.
 */
typedef struct {
	double input;
	double weight;
} Dendrite;

/**
 * The perceptron class contains all of the machinery for an artificial neuron. 
 */
class Perceptron {
	public:
		Perceptron(int);
		Perceptron(std::vector<Dendrite>);
		~Perceptron(){}
	
		Dendrite& operator[](const int);
		
		double output();
		double derivative();
		
		int size();
		
		void setActivation(double(*sigmoid)(double), double(*dx)(double));
		void display();
		
	private:
		//-- Inputs to this perceptron
		std::vector<Dendrite> _inputs;
		
		//-- g(x)
		double (*_sigmoid)(double);
		
		//-- g'(x)
		double (*_sigmoidPrime)(double);
		
		double sum();
		
};

#endif

