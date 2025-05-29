#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <random>
#include <type_traits>

#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"

class Synapse;
class Neuron;
class IONeuron; 

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

	void clearSignals();

	template <typename T>
	static T random(T min, T max, int* seed = nullptr);
	
	static Network* createRandomNetwork(int nIons, int nNeurons, float connect, int* seed = nullptr);
	static Network* createSmallWorldNetwork(int nIons, int nNeurons, int degree, float redirect, int* seed = nullptr);
	static Network* createSpiralNetwork(int n, int* seedPtr);
};



#endif //NETWORK_H


