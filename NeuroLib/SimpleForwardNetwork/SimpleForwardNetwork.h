#ifndef SIMPLEFORWARD_H
#define SIMPLEFORWARD_H

#include "World\World.h"


#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

class SimpleForwardNetwork : World	
{
public:
	SimpleForwardNetwork(World* world);
	void forwardPass();
};

#endif //SIMPLEFORWARD_H