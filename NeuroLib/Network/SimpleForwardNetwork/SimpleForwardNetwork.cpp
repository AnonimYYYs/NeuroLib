
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

SimpleForwardNetwork::SimpleForwardNetwork(Network* network) : Network()
{
	this->ions = network->getIons();
	this->neurons = network->getNeurons();
	this->synapses = network->getSynapses();
}


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
		neuron->forward(ions);
	}
	//сигнал делает обратный обход по нейронам
	/*for (auto neuron{ neurons.rbegin() }; neuron != neurons.rend(); neuron++)
	{
		(*neuron)->forward(ions);
	}*/
	std::cout << "All signals have successfully passed!" << std::endl;
	////удаляем сигналы
	//for (Synapse* synapse : synapses)
	//{
	//	for (Signal* signal : synapse->getSignals())
	//	{
	//		delete signal;
	//	}
	//	synapse->getSignals().clear();
	//}
	std::cout << "Forward Pass Complete!" << std::endl;
}
