#include "World\World.h"

World::World() {} ;

void World::addNeuron()
{
	neurons.push_back(new Neuron(neurons.size()));
}	

void World::addIONeuron(double value)
{
	IONeuron* ion = new IONeuron(value, neurons.size());
	ions.push_back(ion);
	neurons.push_back(ion);
}

void World::addSynapse(Synapse* synapse)
{
	if (checkDuplicateSynapses(synapse) == false)
	{ 
		synapses.push_back(synapse);
		synapse->getNeurons()[0]->addSynapse(synapse);
		synapse->getNeurons()[1]->addSynapse(synapse);
		std::cout << "Successfully connected neurons " << synapse->getNeurons()[0]->getIndex() << " and " << synapse->getNeurons()[1]->getIndex() << std::endl;
	}
}


double World::random(int RND_MAX, int div)
{
	static std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, RND_MAX);
	int roll = distribution(generator);
	double ret = (double)roll / div;
	return ret;
}

std::vector<Neuron*> World::getNeurons()
{
	return neurons;
}

std::vector<IONeuron*> World::getIons()
{
	return ions;
}

std::vector<Synapse*> World::getSynapses()
{
	return synapses;
}

bool World::checkDuplicateSynapses(Synapse* synapse)
{
	for (Synapse* synapse2 : synapses)
	{
		if ((synapse2->getNeurons()[0] == synapse->getNeurons()[0]
			&& synapse2->getNeurons()[1] == synapse->getNeurons()[1])
			|| (synapse2->getNeurons()[0] == synapse->getNeurons()[1]
			&& synapse2->getNeurons()[1] == synapse->getNeurons()[0]))
		{
			std::cout << "Attempt to create duplicate synapses! "
				<< synapse->getNeurons()[0]->getIndex() << "-"
				<< synapse->getNeurons()[1]->getIndex() << " connection already exists" << std::endl;
			return true;
		}
		else if (synapse->getNeurons()[0] == synapse->getNeurons()[1])
		{
			std::cout << "Attempt to create looping synapse!"
				<< " Neuron " << synapse->getNeurons()[0]->getIndex() << " cannot be connected to itself" << std::endl;
			return true;
		}
	}
	return false;
}

void World::printIons()
{
	for (IONeuron* ion : ions)
	{
		std::cout << static_cast<std::string>(*(ion)) << std::endl;
	}
}



World* World::createRandomWorld(int nIons, int nNeurons, float connect)
{
	std::cout << "Creating New Random World: " << std::endl
		<< "Number of Neurons: " << nNeurons + nIons << ", " << nIons << " of them are IONeurons" << std::endl
		<< "Chance to connect two random neurons: " << connect*100 << "%" <<std::endl
		<< "Creating IONeurons..." << std::endl;
	World* world = new World;
	//создаем нейроны
	for (int i = 0; i != nIons; i++)
	{
		world->addIONeuron(random(10000, 10000));
	}
	world->printIons();
	std::cout << "Creating Neurons..." << std::endl;
	for (int i = 0; i != nNeurons; i++)
	{
		world->addNeuron();
	}
	std::cout << "Creating random Synapses..." << std::endl;
	//рандомно связываем нейроны синапсами
	//TODO переписать по индексам
	for (Neuron* neuron : world->neurons)
	{
		for (Neuron* neuron2 : world->neurons)
		{
			if (neuron != neuron2)
			{
				if (connect >= random(10000, 10000))
				{
					Synapse* synapse = new Synapse(neuron, neuron2);
					world->addSynapse(synapse);
				}
			}
		}
	}
	//создаем случайные веса для синапсов
	for (Neuron* neuron : world->neurons)
	{
		int n = neuron->getSynapses().size();
		for (Synapse* synapse : neuron->getSynapses())
		{
			//сумма весов не превышает 1
			double setWeight = random(10000, 10000) / n;
			if (synapse->getWeight() == 0 || synapse->getWeight() > setWeight)
			{
				synapse->setWeight(setWeight);
			}
		}
	}
	std::cout << "Random World Sucessfully Created!" << std::endl;
	return world;
}

World* World::createSmallWorld(int nIons, int nNeurons, int degree, float rewire)
{
	std::cout << "Creating New Small World: " << std::endl
		<< "Number of Neurons: " << nNeurons + nIons << ", " << nIons << " of them are IONeurons" << std::endl
		<< "Chance to redirect neuron connection: " << rewire * 100 << "%" << std::endl
		<< "Creating IONeurons..." << std::endl;

	World* world = new World;
	//создаем нейроны
	for (int i = 0; i != nIons; i++)
	{
		world->addIONeuron(random(10000, 10000));
	}
	world->printIons();
	std::cout << "Creating Neurons..." << std::endl;
	for (int i = 0; i != nNeurons; i++)
	{
		world->addNeuron();
	}

	//создаем синапсы по алгоритму Ватца-Строгаца
	std::cout << "Creating Synapses..." << std::endl;
	for (int i = 0; i < world->neurons.size(); i++)
	{
		for (int j = 1; j <= degree; j++)
		{
			if (i + j < world->neurons.size())
			{
				world->addSynapse(new Synapse(world->neurons[i], world->neurons[i + j]));
			}
			else
			{
				int diff = (i + j) - world->neurons.size();
				world->addSynapse(new Synapse(world->neurons[i], world->neurons[0+diff]));
			}
		}
	}
	//перенаправляем синапсы по алгоритму Ватца-Строгаца
	std::cout << "Rewiring Synapses..." << std::endl;
	for (Synapse* synapse : world->synapses)
	{
		if (rewire >= random(10000, 10000))
		{
			int rnd = random(world->neurons.size() - 1, 1);
			for (Neuron* neuron : world->neurons)
			{
				if (neuron->getIndex() == rnd)
				{
					Synapse* rewSynapse = new Synapse(synapse->getNeurons()[0], world->getNeurons()[rnd]);
					if (world->checkDuplicateSynapses(rewSynapse) == false)
					{
						synapse->rewire(neuron);
						std::cout << "Synapse Successfully Rewired! New connection: " << synapse->getNeurons()[0]->getIndex()
							<< "-"<< synapse->getNeurons()[1]->getIndex() << std::endl;
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
	for (Neuron* neuron : world->neurons)
	{
		int n = neuron->getSynapses().size();
		for (Synapse* synapse : neuron->getSynapses())
		{
			//сумма весов не превышает 1
			double setWeight = random(10000, 10000) / n;
			if (synapse->getWeight() == 0 || synapse->getWeight() > setWeight)
			{
				synapse->setWeight(setWeight);
			}
		}
	}
	std::cout << "Small World Sucessfully Created!" << std::endl;
	return world;
}
