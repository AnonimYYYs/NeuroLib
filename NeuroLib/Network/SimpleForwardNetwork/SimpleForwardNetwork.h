#ifndef SIMPLEFORWARD_H
#define SIMPLEFORWARD_H

#include "Network\Network.h"

class SimpleForwardNetwork : Network	
{
public:
	SimpleForwardNetwork(Network* network);

	/*
	@brief forward pass for all neurons by their order in vector
	*/
	void forwardPass();
};

#endif //SIMPLEFORWARD_H