#include "Network\Network.h"

Network::Network() {} ;

void Network::addNeuron(Neuron* neuron)
{
	neurons.push_back(neuron);
}	

void Network::addIONeuron(double value)
{
	IONeuron* ion = new IONeuron(value, neurons.size());
	ions.push_back(ion);
	neurons.push_back(ion);
}

void Network::addSynapse(Synapse* synapse)
{
	if (checkDuplicateSynapses(synapse) == false)
	{ 
		synapses.push_back(synapse);
		synapse->getNeuron1()->addSynapse(synapse);
		synapse->getNeuron2()->addSynapse(synapse);
		std::cout << "Successfully connected neurons " << synapse->getNeuron1()->getIndex() << " and " << synapse->getNeuron2()->getIndex() << std::endl;
	}
}

//без определения инта не работает, но дабл не обязателен?
template int Network::random<int>(int min, int max);
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

std::vector<Neuron*> Network::getNeurons()
{
	return neurons;
}

std::vector<IONeuron*> Network::getIons()
{
	return ions;
}

std::vector<Synapse*> Network::getSynapses()
{
	return synapses;
}

bool Network::checkDuplicateSynapses(Synapse* synapse)
{
	for (Synapse* synapse2 : synapses)
	{
		if ((synapse2->getNeuron1() == synapse->getNeuron1()
			&& synapse2->getNeuron2() == synapse->getNeuron2())
			|| (synapse2->getNeuron1() == synapse->getNeuron2()
			&& synapse2->getNeuron2() == synapse->getNeuron1()))
		{
			std::cout << "Attempt to create duplicate synapses! "
				<< synapse->getNeuron1()->getIndex() << "-"
				<< synapse->getNeuron2()->getIndex() << " connection already exists" << std::endl;
			return true;
		}
		else if (synapse->getNeuron1() == synapse->getNeuron2())
		{
			std::cout << "Attempt to create looping synapse!"
				<< " Neuron " << synapse->getNeuron1()->getIndex() << " cannot be connected to itself" << std::endl;
			return true;
		}
	}
	return false;
}

void Network::printIons()
{
	for (IONeuron* ion : ions)
	{
		std::cout << static_cast<std::string>(*(ion)) << std::endl;
	}
}



Network* Network::createRandomNetwork(int nIons, int nNeurons, float connect)
{
	std::cout << "Creating New Random Network: " << std::endl
		<< "Number of Neurons: " << nNeurons + nIons << ", " << nIons << " of them are IONeurons" << std::endl
		<< "Chance to connect two random neurons: " << connect*100 << "%" <<std::endl
		<< "Creating IONeurons..." << std::endl;
	Network* network = new Network;
	//создаем нейроны
	for (int i = 0; i != nIons; i++)
	{
		network->addIONeuron(random(0.0, 1.0));
	}
	network->printIons();
	std::cout << "Creating Neurons..." << std::endl;
	for (int i = 0; i != nNeurons; i++)
	{
		network->addNeuron(new Neuron(network->getNeurons().size()));
	}
	std::cout << "Creating random Synapses..." << std::endl;
	//рандомно связываем нейроны синапсами
	//TODO переписать по индексам
	for (auto [index, neuron] : network->neurons)
	{
		for (Neuron* neuron2 : network->neurons)
		{
			if (neuron != neuron2)
			{
				if (connect >=  random(0.0, 1.0))
				{
					Synapse* synapse = new Synapse(neuron, neuron2);
					network->addSynapse(synapse);
				}
			}
		}
	}
	//создаем случайные веса для синапсов
	for (Neuron* neuron : network->neurons)
	{
		int n = neuron->getSynapses().size();
		for (Synapse* synapse : neuron->getSynapses())
		{
			//сумма весов не превышает 1
			double setWeight = random(-1.0, 1.0);
			if (synapse->getWeight() == 0 || synapse->getWeight() > setWeight)
			{
				synapse->setWeight(setWeight);
			}
		}
	}
	std::cout << "Random Network Sucessfully Created!" << std::endl;
	return network;
}

Network* Network::createSmallWorldNetwork(int nIons, int nNeurons, int degree, float rewire)
{
	std::cout << "Creating New Small Network Network: " << std::endl
		<< "Number of Neurons: " << nNeurons + nIons << ", " << nIons << " of them are IONeurons" << std::endl
		<< "Chance to redirect neuron connection: " << rewire * 100 << "%" << std::endl
		<< "Creating IONeurons..." << std::endl;

	Network* network = new Network;
	//создаем нейроны
	for (int i = 0; i != nIons; i++)
	{
		network->addIONeuron(random(0.0, 1.0));
	}
	network->printIons();
	std::cout << "Creating Neurons..." << std::endl;
	for (int i = 0; i != nNeurons; i++)
	{
		network->addNeuron(new Neuron(network->getNeurons().size()));
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
			for (Neuron* neuron : network->neurons)
			{
				if (neuron->getIndex() == rnd)
				{
					Synapse* rewSynapse = new Synapse(synapse->getNeuron1(), network->getNeurons()[rnd]);
					if (network->checkDuplicateSynapses(rewSynapse) == false)
					{
						synapse->rewire(neuron);
						std::cout << "Synapse Successfully Rewired! New connection: " << synapse->getNeuron1()->getIndex()
							<< "-"<< synapse->getNeuron2()->getIndex() << std::endl;
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	//создаем случайные веса для синапсов
	for (Neuron* neuron : network->neurons)
	{
		int n = neuron->getSynapses().size();
		for (Synapse* synapse : neuron->getSynapses())
		{
			//сумма весов не превышает 1
			double setWeight = random(-1.0, 1.0);
			if (synapse->getWeight() == 0 || synapse->getWeight() > setWeight)
			{
				synapse->setWeight(setWeight);
			}
		}
	}
	std::cout << "Small World Network Sucessfully Created!" << std::endl;
	return network;
}
