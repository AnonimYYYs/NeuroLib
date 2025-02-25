#ifndef PYSIMPLEFORWARD_CPP
#define PYSIMPLEFORWARD_CPP


#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C"
{
	DLLEXPORT SimpleForwardNetwork* SimpleForwardNetwork_new(Network* network)
	{
		return new SimpleForwardNetwork(network);
	}
	DLLEXPORT void SimpleForwardNetwork_delete(SimpleForwardNetwork* network)
	{
		delete network;
	}
}

#endif //PYSIMPLEFORWARD_CPP