
#include "World\World.h"
#include "SimpleForwardNetwork\SimpleForwardNetwork.h"

SimpleForwardNetwork::SimpleForwardNetwork(World* world) : World()
{
	this->ions = world->getIons();
	this->neurons = world->getNeurons();
	this->synapses = world->getSynapses();
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
	for (auto neuron{ neurons.begin() }; neuron != neurons.end(); neuron++)
	{
		(*neuron)->forward(ions);
	}
	//сигнал делает обратный обход по нейронам
	for (auto neuron{ neurons.rbegin() }; neuron != neurons.rend(); neuron++)
	{
		(*neuron)->forward(ions);
	}
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
