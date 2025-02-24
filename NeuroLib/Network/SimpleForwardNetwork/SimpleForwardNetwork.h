#ifndef SIMPLEFORWARD_H
#define SIMPLEFORWARD_H

#include "Network\Network.h"

#include <math.h>

class SimpleForwardNetwork : public Network	
{
private:
	std::map<int, std::vector<Neuron*>> graphs;
	bool isInitialized;
	double error;
public:
	SimpleForwardNetwork(Network* network);
	SimpleForwardNetwork();

	static SimpleForwardNetwork* createSmallWorldNetwork(int nIons, int Nneurons, int degree, float redirect);
	static SimpleForwardNetwork* createRandomNetwork(int nIons, int nNeurons, float connect);

	std::vector<Neuron*> graphTraverse(int index);
	void initGraphs();
	void stepForward(int index, double value);
	void stepBackward(int index, double value, double eps = 0.1);
	void stepComplete(std::vector<double> in);

	std::map<int, std::vector<Neuron*>> getGraphs();
	double getError();
	void setError(double value);
	/*
	@brief forward pass for all neurons by their order in vector
	*/
	void forwardPass();

	
};

#endif //SIMPLEFORWARD_H