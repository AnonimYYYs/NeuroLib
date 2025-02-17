#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <random>

#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"

class World
{
protected:
	std::vector<Neuron*> neurons;
	std::vector<IONeuron*> ions;
	std::vector<Synapse*> synapses;
public:
	World();
	void addNeuron();
	void addIONeuron(double value);
	void addSynapse(Synapse* synapse);

	std::vector<Neuron*> getNeurons();
	std::vector<IONeuron*> getIons();
	std::vector<Synapse*> getSynapses();

	bool checkDuplicateSynapses(Synapse* synapse);
	void printIons();

	/*
	@brief function to set random values
	@param RND_MAX is highest value for random range
	@param div is value by which random roll is divided
	@return result of random value being divided by div
	*/
	static double random(int RND_MAX, int div);
	/*
	@brief creates World class object using random input values for in/out neurons and
	synapses for random pairs of neurons
	@param nIons is the number of in/out neurons created
	@param nNeurons is the number of regular neurons created
	@param connect is the chance to create connection for any pair of neurons
	@return pointer to created World class object
	*/
	static World* createRandomWorld(int nIons, int nNeurons, float connect);

	/*
	@brief creates World class object using the Small World algorithm.
	Input values are random for in/out neurons.  Synapses are created for neighbor neurons
	to form a circle, then synapses are randomly rewired to connect new pairs of neurons
	@param nIons is the number of in/out neurons created
	@param nNeurons is the number of regular neurons created
	@param degree is the number of neighbor neurons in a circle (for each side) to create synapses with
	@param rewire is the chance to redirect synapse to a different neuron after finishing the initial circle
	@return pointer to created World class object
	*/
	static World* createSmallWorld(int nIons, int Nneurons, int degree, float redirect);
};



#endif //WORLD_H