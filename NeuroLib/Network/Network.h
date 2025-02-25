#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
//#include <map>
#include <random>
#include <type_traits>

#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"

class Network
{
protected:
	std::map<int, Neuron*> neurons;
	std::map<int, IONeuron*> ions;
	std::vector<Synapse*> synapses;
public:
	Network();
	~Network();
	void addNeuron(Neuron* neuron);
	void addIONeuron(IONeuron* ion);
	void addSynapse(Synapse* synapse);

	std::map<int, Neuron*> getNeurons();
	std::map<int, IONeuron*> getIons();
	std::vector<Synapse*> getSynapses();

	bool checkConnection(int index1, int index2);
	void printIons();

	template <typename T>
	static T random(T min, T max);
	/*
	@brief creates Network class object using random input values for in/out neurons and
	synapses for random pairs of neurons
	@param nIons is the number of in/out neurons created
	@param nNeurons is the number of regular neurons created
	@param connect is the chance to create connection for any pair of neurons
	@return pointer to created Network class object
	*/
	static Network* createRandomNetwork(int nIons, int nNeurons, float connect);

	/*
	@brief creates Network class object using the Small Network algorithm.
	Input values are random for in/out neurons.  Synapses are created for neighbor neurons
	to form a circle, then synapses are randomly rewired to connect new pairs of neurons
	@param nIons is the number of in/out neurons created
	@param nNeurons is the number of regular neurons created
	@param degree is the number of neighbor neurons in a circle (for each side) to create synapses with
	@param rewire is the chance to redirect synapse to a different neuron after finishing the initial circle
	@return pointer to created Network class object
	*/
	static Network* createSmallWorldNetwork(int nIons, int nNeurons, int degree, float redirect);
};



#endif //NETWORK_H