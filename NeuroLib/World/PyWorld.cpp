#ifndef PYWORLD_CPP
#define PYWORLD_CPP

#include "World\World.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif


//for DLLEXPORT
World *World_new()
{
	return new World();
}

void World_delete(World *world)
{
	delete world;
}

World *World_createRandomWorld(int nIons, int nNeurons, float connect)
{
	return World::createRandomWorld(nIons, nNeurons, connect);
}

World *World_createSmallWorld(int nIons, int nNeurons, int degree, float rewire)
{
	return World::createSmallWorld(nIons, nNeurons, degree, rewire);
}

void World_printIons(World *world)
{
	world->printIons();
}

int World_getSynapsesSize(World *world)
{
	return world->getSynapses().size();
}

Synapse *World_getSynapses(World *world, int pos)
{
	return world->getSynapses()[pos];
}

double World_getSynapseWeight(World *world, int pos)
{
	return world->getSynapses()[pos]->getWeight();
}

int World_getSynapseConnectedNeuron1(World *world, int pos)
{
	return world->getSynapses()[pos]->getNeurons()[0]->getIndex();
}

int World_getSynapseConnectedNeuron2(World *world, int pos)
{
	return world->getSynapses()[pos]->getNeurons()[1]->getIndex();
}

int World_getIonsSize(World *world)
{
	return world->getIons().size();
}

bool World_checkIfIon(World *world, int index)
{
	for (IONeuron *ion : world->getIons())
	{
		if (ion->getIndex() == index)
			return true;
	}
	return false;
}


#endif //PYWORLD_CPP