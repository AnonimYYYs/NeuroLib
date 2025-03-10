#include "Network\Network.h"

Network::Network() {}
Network::~Network()
{
	for (auto [index, neuron] : neurons)
	{
		delete(neuron);
	}
	for (Synapse* synapse : synapses)
	{
		delete(synapse);
	}
	neurons.clear();
	ions.clear();
	synapses.clear();
}
;

void Network::addNeuron(Neuron* neuron)
{
	neurons[neuron->getIndex()] = neuron;
}	

void Network::addIONeuron(IONeuron* ion)
{
	neurons[ion->getIndex()] = ion;
	ions[ion->getIndex()] = ion;
}

void Network::addSynapse(Synapse* synapse)
{
	if (checkConnection(synapse->getNeuron1()->getIndex(), synapse->getNeuron2()->getIndex()) == true)
	{ 
		synapses.push_back(synapse);
		synapse->getNeuron1()->addSynapse(synapse);
		synapse->getNeuron2()->addSynapse(synapse);
		std::cout << "Successfully connected neurons " << synapse->getNeuron1()->getIndex() << " and " << synapse->getNeuron2()->getIndex() << std::endl;
	}
}

//без определения инта не работает, но дабл не обязателен?
template<typename T> T Network::random(T min, T max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	//скорее всего из-за этого ифа
	if (std::is_same<T, int>::value)
	{
		std::uniform_int_distribution<int> distribution(min, max);
		return distribution(gen);
	}
	else
	{
		std::uniform_real_distribution<double> distribution(min, max);
		return distribution(gen);
	}
};

std::map<int, Neuron*> Network::getNeurons()
{
	return neurons;
}

std::map<int, IONeuron*> Network::getIons()
{
	return ions;
}

std::vector<Synapse*> Network::getSynapses()
{
	return synapses;
}

/*
@brief fucntion to check if it is possible to create a new synapse between 2 neurons
@param index1,2 indices of neurons
@return true if connection can be made, false if invalid connection
*/
bool Network::checkConnection(int index1, int index2)
{
	if (index1 == index2)
	{
		std::cout << "Attempt to create looping synapse!"
			<< " Neuron " << index1 << " cannot be connected to itself" << std::endl;
		return false;
	}
	for (Synapse* synapse : neurons[index1]->getSynapses())
	{
		if ((synapse->getNeuron1()->getIndex() == index1
			&& synapse->getNeuron2()->getIndex() == index2)
			|| (synapse->getNeuron1()->getIndex() == index2
				&& synapse->getNeuron2()->getIndex() == index1))
		{
			std::cout << "Attempt to create duplicate synapses! "
				<< index1 << "-" << index2 << " connection already exists" << std::endl;
			return false;
		}
	}
	return true;
}

void Network::printIons()
{
	for (auto [index, ion] : ions)
	{
		std::cout << static_cast<std::string>(*(ion)) << std::endl;
	}
}

void Network::clearSignals()
{
	for (Synapse* synapse : synapses)
	{
		synapse->deleteSignals();
	}
}
/*
	@brief creates Network class object using random input values for in/out neurons and
	synapses for random pairs of neurons
	@param nIons is the number of in/out neurons created
	@param nNeurons is the number of regular neurons created
	@param connect is the chance to create connection for any pair of neurons
	@return pointer to created Network class object
	*/
Network* Network::createRandomNetwork(int nIons, int nNeurons, float connect)
{
	std::cout << "Creating New Random Network: " << std::endl
		<< "Number of Neurons: " << nNeurons + nIons << ", " << nIons << " of them are IONeurons" << std::endl
		<< "Chance to connect two random neurons: " << connect*100 << "%" <<std::endl
		<< "Creating IONeurons..." << std::endl;
	Network* network = new Network;
	//создаем нейроны
	for (int i = 0; i < nIons; i++)
	{
		IONeuron* ion = new IONeuron(random(0.0, 1.0), i);
		network->addIONeuron(ion);
	}
	network->printIons();
	std::cout << "Creating Neurons..." << std::endl;
	for (int i = 0; i != nNeurons; i++)
	{
		Neuron* neuron = new Neuron(network->getNeurons().size());
		network->addNeuron(neuron);
	}
	std::cout << "Creating random Synapses..." << std::endl;
	//рандомно связываем нейроны синапсами

	for (int i = 0; i < network->neurons.size(); i++)
	{
		if (connect >= random(0.0, 1.0))
		{
			int max = network->neurons.size();
			int connectTo = network->random(0, max);
			if (network->checkConnection(i, connectTo) == true)
			{
				Synapse* synapse = new Synapse(network->neurons[i], network->neurons[random(0, connectTo)]);
				network->addSynapse(synapse);
			}
			
		}
	}
	//создаем случайные веса для синапсов
	//вектор синапсов достается только методом, но мапа нейронов доступна сама по себе?
	for (Synapse* synapse : network->getSynapses())
	{
		synapse->setWeight(random(-1.0, 1.0));
	}
	std::cout << "Random Network Sucessfully Created!" << std::endl;
	return network;
}


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
Network* Network::createSmallWorldNetwork(int nIons, int nNeurons, int degree, float rewire)
{
	std::cout << "Creating New Small Network Network: " << std::endl
		<< "Number of Neurons: " << nNeurons + nIons << ", " << nIons << " of them are IONeurons" << std::endl
		<< "Chance to redirect neuron connection: " << rewire * 100 << "%" << std::endl
		<< "Creating IONeurons..." << std::endl;

	Network* network = new Network;
	//создаем нейроны
	for (int i = 0; i < nIons; i++)
	{
		IONeuron* ion = new IONeuron( random(0.0, 1.0), i);
		network->addIONeuron(ion);
	}
	network->printIons();
	std::cout << "Creating Neurons..." << std::endl;
	for (int i = 0; i != nNeurons; i++)
	{
		Neuron* neuron = new Neuron(network->getNeurons().size());
		network->addNeuron(neuron);
	}

	//создаем синапсы по алгоритму Ватца-Строгаца
	std::cout << "Creating Synapses..." << std::endl;
	for (int i = 0; i < network->neurons.size(); i++)
	{
		for (int j = 1; j <= degree; j++)
		{
			if (i + j < network->neurons.size())
			{
				network->addSynapse(new Synapse(network->neurons[i], network->neurons[i + j]));
			}
			else
			{
				int diff = (i + j) - network->neurons.size();
				network->addSynapse(new Synapse(network->neurons[i], network->neurons[0+diff]));
			}
		}
	}
	//перенаправляем синапсы по алгоритму Ватца-Строгаца
	std::cout << "Rewiring Synapses..." << std::endl;
	for (Synapse* synapse : network->synapses)
	{
		if (rewire >=  random(0.0, 1.0))
		{
			int rnd = random<int>(0, network->neurons.size() - 1);
			if (network->checkConnection(synapse->getNeuron1()->getIndex(), rnd) == true)
			{
				synapse->rewire(network->neurons[rnd]);
				std::cout << "Synapse Successfully Rewired! New connection: " << synapse->getNeuron1()->getIndex()
				<< "-"<< rnd << std::endl;
			}
		}
	}
	//создаем случайные веса для синапсов
	for (Synapse* synapse : network->getSynapses())
	{
		synapse->setWeight(random(-1.0, 1.0));
	}
	std::cout << "Small World Network Sucessfully Created!" << std::endl << std::endl;
	return network;
}
