#ifndef WORLD_H
#define WORLD_H

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
	World(World* world);
	void addNeuron();
	void addIONeuron(double value);
	void addSynapse(Synapse* synapse);
	static double random();

	void printIons();
	void forwardPass();

	static World* createRandomWorld(int nIons, int nNeurons, float connect);
};

#endif //WORLD_H