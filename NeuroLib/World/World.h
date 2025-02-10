#ifndef WORLD_H
#define WORLD_H

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT

#endif
#include <vector>
#include <random>

#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"

class World
{
private:
	std::vector<Neuron*> neurons;
	std::vector<IONeuron*> ions;
	std::vector<Synapse*> synapses;
public:
	World();
	void addNeuron();
	void addIONeuron(double value);
	void addSynapse(Synapse* synapse);
	static double random(int RND_MAX, int div);

	std::vector<Neuron*> getNeurons();
	std::vector<IONeuron*> getIons();
	std::vector<Synapse*> getSynapses();

	bool checkDuplicateSynapses(Synapse* synapse);
	void printIons();
	void forwardPass();

	static World* createRandomWorld(int nIons, int nNeurons, float connect);
	static World* createSmallWorld(int nIons, int Nneurons, int degree, float redirect);
};

class cSynapse;
extern "C" 
{
	DLLEXPORT World* World_new();
	DLLEXPORT void World_delete(World* world);
	DLLEXPORT World* World_createRandomWorld(int nIons, int nNeurons, float connect);
	DLLEXPORT World* World_createSmallWorld(int nIons, int nNeurons, int degree, float rewire);

	DLLEXPORT void World_printIons(World* world);
	DLLEXPORT void World_forwardPass(World* world);

	DLLEXPORT int World_getSynapsesSize(World* world);
	DLLEXPORT Synapse* World_getSynapses(World* world, int pos);
	DLLEXPORT double World_getSynapseWeight(World* world, int pos);
	DLLEXPORT int World_getSynapseConnectedNeuron1(World* world, int pos);
	DLLEXPORT int World_getSynapseConnectedNeuron2(World* world, int pos);

	DLLEXPORT int World_getIonsSize(World* world);
	DLLEXPORT bool World_checkIfIon(World* world, int index);
}


#endif //WORLD_H