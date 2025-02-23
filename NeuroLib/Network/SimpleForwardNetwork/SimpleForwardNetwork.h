#ifndef SIMPLEFORWARD_H
#define SIMPLEFORWARD_H

#include "Network\Network.h"

class SimpleForwardNetwork : public Network	
{
public:
	SimpleForwardNetwork(Network* network);
	SimpleForwardNetwork();

	/*
	@brief forward pass for all neurons by their order in vector
	*/
	void forwardPass();

	static SimpleForwardNetwork* createSmallWorldNetwork(int nIons, int Nneurons, int degree, float redirect);
	static SimpleForwardNetwork* createRandomNetwork(int nIons, int nNeurons, float connect);
};

#endif //SIMPLEFORWARD_H