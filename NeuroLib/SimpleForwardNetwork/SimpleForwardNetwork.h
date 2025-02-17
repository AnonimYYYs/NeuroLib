#ifndef SIMPLEFORWARD_H
#define SIMPLEFORWARD_H

#include "World\World.h"

class SimpleForwardNetwork : World	
{
public:
	SimpleForwardNetwork(World* world);

	/*
	@brief forward pass for all neurons by their order in vector
	*/
	void forwardPass();
};

#endif //SIMPLEFORWARD_H