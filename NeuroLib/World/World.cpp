#include "World\World.h"

World::World() {} ;

void World::addNeuron()
{
	neurons.push_back(new Neuron());
}	

void World::addIONeuron(double value)
{
	IONeuron* ion = new IONeuron(value);
	ions.push_back(ion);
	neurons.push_back(ion);
}

void World::addSynapse(Synapse* synapse)
{
	for (Synapse* synapse2 : synapses)
	{
		if ((synapse2->getNeurons()[0] == synapse->getNeurons()[0]
			&& synapse2->getNeurons()[1] == synapse->getNeurons()[1])
			|| (synapse2->getNeurons()[0] == synapse->getNeurons()[1]
			&& synapse2->getNeurons()[1] == synapse->getNeurons()[0]))
		{
			std::cout << "Attempt to create duplicate synapses!"
				<< " Neurons " << synapse->getNeurons()[0]->getIndex() << " and "
				<< synapse->getNeurons()[1]->getIndex() << " are already connected" << std::endl;
			return;
		}
	}
	synapses.push_back(synapse);
	synapse->getNeurons()[0]->addSynapse(synapse);
	synapse->getNeurons()[1]->addSynapse(synapse);
	std::cout << "Successfully connected neurons " << synapse->getNeurons()[0]->getIndex() << " and " << synapse->getNeurons()[1]->getIndex()  << std::endl;
}

double World::random() 
{
	static const int RND_MAX = 100000;
	static std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, RND_MAX + 1);
	int roll = distribution(generator);
	double ret = (double)roll / RND_MAX;
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

void World::printIons()
{
	for (IONeuron* ion : ions)
	{
		std::cout << static_cast<std::string>(*(ion)) << std::endl;
	}
}

void World::forwardPass()
{
	//создаем сигнал из IO нейронов
	for (IONeuron* ion : ions)
	{
		ion->spawnSignals();
	}
	//сигнал делает обход по всем нейронам
	for (auto neuron { neurons.begin()}; neuron != neurons.end(); neuron++)
	{
		(*neuron)->forward();
	}	
	//сигнал делает обратный обход по нейронам
	for (auto neuron{ neurons.rbegin() }; neuron != neurons.rend(); neuron++)
	{
		(*neuron)->forward();
	}
	std::cout << "Forward Pass Complete!" << std::endl;
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
		world->addIONeuron(random());
	}
	world->printIons();
	std::cout << "Creating Neurons..." << std::endl;
	for (int i = 0; i != nNeurons; i++)
	{
		world->addNeuron();
	}
	std::cout << "Creating random Synapses..." << std::endl;
	//рандомно связываем нейроны синапсами
	for (Neuron* neuron : world->neurons)
	{
		for (Neuron* neuron2 : world->neurons)
		{
			if (neuron != neuron2)
			{
				if (connect >= random())
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
			double setWeight = random() / n;
			if (synapse->getWeight() == 0 || synapse->getWeight() > setWeight)
			{
				synapse->setWeight(setWeight);
			}
		}
	}
	std::cout << "Random World Sucessfully Created!" << std::endl;
	return world;
}

World* World_new()
{
	return new World();
}

void World_delete(World* world)
{
	delete world;
}

World* World_createRandomWorld(int nIons, int nNeurons, float connect)
{
		return World::createRandomWorld(nIons, nNeurons, connect);
}

void World_printIons(World* world)
{
	return world->printIons();
}

int World_getSynapsesSize(World* world) 
{
	return world->getSynapses().size();
}

void World_forwardPass(World* world)
{
	return world->forwardPass();
}

class cSynapse
{
public:
	int neuron1_index;
	int neuron2_index;
	double weight;
};

cSynapse* World_getSynapsesData(World* world) {
	cSynapse* synapse_array = new cSynapse[world->getSynapses().size()];
	int i = 0;
	for ( auto synapse : world->getSynapses()) 
	{
		cSynapse s;
		s.weight = synapse->getWeight();
		s.neuron1_index = synapse->getNeurons()[0]->getIndex();
		s.neuron2_index = synapse->getNeurons()[1]->getIndex();
		synapse_array[i] = s;
		i++;
	}
	return synapse_array;
}

int World_getIonsSize(World* world)
{
	return world->getIons().size();
}