#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <vector>

#include "layer.h"

/**
 * The Network class holds some number of layers, and contains the high-level
 * important bits of code.
 */
class Network {
	public:
		Network(int, int *);
		Network(char *);
		~Network() {}
	
		Layer& operator[] (int index);
		
		std::vector<double> output();
		
		bool save(char *);
		bool load(char *);
		
		void setInputs(std::vector<double> *);
		void feedForward();
		double backprop(std::vector<double> *, double);
		void setActivation(double(*sigmoid)(double), double(*dx)(double));
		void display();

	private:
		std::vector<Layer> _layers;
};

#endif

