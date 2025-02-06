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
	static double random();

	std::vector<Neuron*> getNeurons();
	std::vector<IONeuron*> getIons();
	std::vector<Synapse*> getSynapses();

	void printIons();
	void forwardPass();

	static World* createRandomWorld(int nIons, int nNeurons, float connect);
};

class cSynapse;
extern "C" 
{
	DLLEXPORT World* World_new();
	DLLEXPORT void World_delete(World* world);
	DLLEXPORT World* World_createRandomWorld(int nIons, int nNeurons, float connect);	
	DLLEXPORT void World_printIons(World* world);

	DLLEXPORT int World_getSynapsesSize(World* world);
	DLLEXPORT cSynapse* World_getSynapsesData(World* world);
	DLLEXPORT int World_getIonsSize(World* world);
}


#endif //WORLD_H