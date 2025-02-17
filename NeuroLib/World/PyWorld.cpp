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
	DLLEXPORT World* World_new()
	{
		return new World();
	}
	DLLEXPORT void World_delete(World* world)
	{
		delete world;
	}
	DLLEXPORT World* World_createRandomWorld(int nIons, int nNeurons, float connect)
	{
		return World::createRandomWorld(nIons, nNeurons, connect);
	}
	DLLEXPORT World* World_createSmallWorld(int nIons, int nNeurons, int degree, float rewire)
	{
		return World::createSmallWorld(nIons, nNeurons, degree, rewire);
	};
	DLLEXPORT void World_printIons(World* world)
	{
		world->printIons();
	}
	DLLEXPORT int World_getIonsSize(World* world)
	{
		return world->getIons().size();
	}
	DLLEXPORT bool World_checkIfIon(World* world, int index)
	{
		for (IONeuron* ion : world->getIons())
		{
			if (ion->getIndex() == index)
				return true;
		}
		return false;
	}
	DLLEXPORT int World_getSynapsesSize(World* world)
	{
		return world->getSynapses().size();
	}
	DLLEXPORT Synapse* World_getSynapses(World* world, int pos)
	{
		return world->getSynapses()[pos];
	}
	DLLEXPORT double World_getSynapseWeight(World* world, int pos)
	{
		return world->getSynapses()[pos]->getWeight();
	}
	DLLEXPORT int World_getSynapseConnectedNeuron1(World* world, int pos)
	{
		return world->getSynapses()[pos]->getNeurons()[0]->getIndex();
	}

	DLLEXPORT int World_getSynapseConnectedNeuron2(World* world, int pos)
	{
		return world->getSynapses()[pos]->getNeurons()[1]->getIndex();
	}
}
#endif //PYWORLD_CPP