#ifndef PYWORLD_CPP
#define PYWORLD_CPP

#include "World\World.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

extern "C"
{
	DLLEXPORT World* World_new();

	DLLEXPORT void World_delete(World* world);
	DLLEXPORT World* World_createRandomWorld(int nIons, int nNeurons, float connect);
	DLLEXPORT World* World_createSmallWorld(int nIons, int nNeurons, int degree, float rewire);

	DLLEXPORT void World_printIons(World* world);
	DLLEXPORT int World_getIonsSize(World* world);
	DLLEXPORT bool World_checkIfIon(World* world, int index);

	DLLEXPORT int World_getSynapsesSize(World* world);
	DLLEXPORT Synapse* World_getSynapses(World* world, int pos);
	DLLEXPORT double World_getSynapseWeight(World* world, int pos);
	DLLEXPORT int World_getSynapseConnectedNeuron1(World* world, int pos);
	DLLEXPORT int World_getSynapseConnectedNeuron2(World* world, int pos);
}


#endif //PYWORLD_CPP