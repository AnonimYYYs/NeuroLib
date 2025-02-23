
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

SimpleForwardNetwork::SimpleForwardNetwork(Network* network) : Network()
{
	this->ions = network->getIons();
	this->neurons = network->getNeurons();
	this->synapses = network->getSynapses();
}
SimpleForwardNetwork::SimpleForwardNetwork() : Network() {}

void SimpleForwardNetwork::forwardPass()
{
	std::cout << "Starting Forward Pass..." << std::endl;
	//создаем сигнал из IO нейронов
	for (IONeuron* ion : ions)
	{
		ion->spawnSignals();
	}


	//сигнал делает обход по всем нейронам
	for (auto [index, neuron] : neurons)
	{
		neuron->forward();
	}
	//сигнал делает обратный обход по нейронам
	/*for (auto neuron{ neurons.rbegin() }; neuron != neurons.rend(); neuron++)
	{
		(*neuron)->forward(ions);
	}*/
	std::cout << "All signals have successfully passed!" << std::endl;
	//удаляем сигналы
	for (Synapse* synapse : synapses)
	{
		synapse->deleteSignals();
	}
	std::cout << "Forward Pass Complete!" << std::endl;
}

SimpleForwardNetwork* SimpleForwardNetwork::createSmallWorldNetwork(int nIons, int nNeurons, int degree, float redirect)
{
	Network* network = Network::createSmallWorldNetwork(nIons, nNeurons, degree, redirect);
	SimpleForwardNetwork* sfn = new SimpleForwardNetwork(network);
	return sfn;
}

SimpleForwardNetwork* SimpleForwardNetwork::createRandomNetwork(int nIons, int nNeurons, float connect)
{
	Network* network = Network::createRandomNetwork(nIons, nNeurons, connect);
	SimpleForwardNetwork* sfn = new SimpleForwardNetwork(network);
	return sfn;
}
