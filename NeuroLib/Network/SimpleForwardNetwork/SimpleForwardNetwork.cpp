
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

SimpleForwardNetwork::SimpleForwardNetwork(Network* network) : Network()
{
	this->ions = network->getIons();
	this->neurons = network->getNeurons();
	this->synapses = network->getSynapses();
	isInitialized = false;
}
SimpleForwardNetwork::SimpleForwardNetwork() : Network() {}

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

std::vector<Neuron*> SimpleForwardNetwork::graphTraverse(int index)
{
	std::map<int, Neuron*> graphMap;
	std::vector<Neuron*> graphVector;
	graphMap[index] = neurons[index];
	graphVector.push_back(neurons[index]);

	//делаем обход для каждого нейрона в нетворке
	auto iter = graphVector.begin();
	int i = 0;
	while(iter != graphVector.end())
	{
		Neuron* traverseNeuron = *iter;
		int traverseIndex = traverseNeuron->getIndex();
		//получаем нейроны, связанные с текущим
		for (Synapse* synapse : traverseNeuron->getSynapses())
		{
			//определяем, какой нейрон из синапса нужно получить
			Neuron* nextNeuron;
			if (synapse->getNeuron1()->getIndex() == traverseIndex)
			{
				nextNeuron = synapse->getNeuron2();
			}
			else
			{
				nextNeuron = synapse->getNeuron1();
			}
			int nextIndex = nextNeuron->getIndex();
			//проверяем, находится ли следующий нейрон в графе
			if (graphMap.contains(nextIndex) == false)
			{
				graphMap[nextIndex] = nextNeuron;
				graphVector.push_back(nextNeuron);
			}
		}
		i++;
		iter = graphVector.begin() + i;
	}
	graphMap.clear();

	return graphVector;
}

void SimpleForwardNetwork::initGraphs()
{
	if (isInitialized == false)
	{
		isInitialized = true;

		for (auto [index, ion] : ions)
		{
			int index = ion->getIndex();
			graphs[index] = graphTraverse(index);
		}
	}
}

void SimpleForwardNetwork::stepForward(int index, double value)
{
	IONeuron* rootIon = ions[index];
	std::vector<Neuron*> graph = graphs[index];
	rootIon->setValue(value);
	rootIon->spawnSignals(rootIon->getOutputValue());

	for (Neuron* neuron : graph)
	{
		neuron->forward(index);
	}

	for (Synapse* synapse : synapses)
	{
		synapse->deleteSignals();
	}
}

void SimpleForwardNetwork::stepBackward(int index, double value, double eps)
{
	double errorSum = 0;
	//TODO обработка для нейронов без связей?
	for (auto [index, neuron] : neurons)
	{
		errorSum += pow((value - neuron->getOutputValue()), 2);
	}
	setError(errorSum / neurons.size());
	IONeuron* rootIon = ions[index];
	std::vector<Neuron*> graph = graphs[index];
	//создаем сигналы со значением ошибки
	rootIon->spawnSignals(getError()*eps);
	for (Neuron* neuron : graph)
	{
		neuron->backward(index);
	}
}

void SimpleForwardNetwork::stepComplete(std::vector<double> in)
{
	for (auto [index, ion] : ions)
	{
		int index = ion->getIndex();
		if (index < ions.size() - 1)
		{
			stepForward(index, 0.5);
		}
		else
		{
			stepBackward(index, 0.4);
		}
	}
}

std::map<int, std::vector<Neuron*>> SimpleForwardNetwork::getGraphs()
{
	return graphs;
}

double SimpleForwardNetwork::getError()
{
	return error;
}

void SimpleForwardNetwork::setError(double value)
{
	error = value;
}
