#ifndef PYSIMPLEFORWARD_CPP
#define PYSIMPLEFORWARD_CPP


#include "SimpleForwardNetwork\SimpleForwardNetwork.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C"
{
	DLLEXPORT SimpleForwardNetwork* SimpleForwardNetwork_new(World* world)
	{
		return new SimpleForwardNetwork(world);
	}
	DLLEXPORT void SimpleForwardNetwork_delete(SimpleForwardNetwork* network)
	{
		delete network;
	}
	DLLEXPORT void SimpleForwardNetwork_ForwardPass(SimpleForwardNetwork* network)
	{
		network->forwardPass();
	}
}

#endif //PYSIMPLEFORWARD_CPP