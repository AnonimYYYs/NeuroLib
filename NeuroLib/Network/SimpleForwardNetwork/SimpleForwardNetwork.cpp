
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
	//auto iter = graphVector.begin();
	int i = 0;
	while(i < neurons.size())
	{
		Neuron* traverseNeuron = graphVector[i];
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
	rootIon->spawnSignals(value);

	// todo fix дважды активируется первый нейрон
	rootIon->forward(index, value);
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
	for (auto [index, neuron] : neurons)
	{
		errorSum += pow((value - neuron->getOutputValue()), 2);
	}
	double mse = errorSum / neurons.size();
	std::cout << "Mean Squared Error: " << mse << std::endl;
	IONeuron* rootIon = ions[index];
	std::vector<Neuron*> graph = graphs[index];
	//создаем сигналы со значением ошибки
	//? умножаем ли тут на эпсилон?
	rootIon->spawnSignals(mse * eps);
	for (Neuron* neuron : graph)
	{
		neuron->backward(index);
	}

	for (Synapse* synapse : synapses)
	{
		synapse->deleteSignals();
	}
}

void SimpleForwardNetwork::step(std::vector<double> in)
{
	for (auto [index, ion] : ions)
	{
		//будет работать только когда первые индексы у ионов
		if (index < ions.size() - 1)
		{
			stepForward(index, in[index]);
		}
		else
		{
			stepBackward(index, in[index]);
		}
	}
}

void SimpleForwardNetwork::learn(std::vector<std::vector<double>> input, int epoch)
{
	for (int i = 0; i < epoch; i++)
	{
		std::cout << "Epoch " << i << std::endl;
		for (auto set : input)
		{
			if (set.size() != ions.size())
			{
				std::cout << "Input error: learn set of invalid size!" << std::endl;
				return;
			}
			step(set);
			//printIons();
		}
	}
}

std::vector<std::pair<double, bool>> SimpleForwardNetwork::readDataBool(std::string filename)
{
	std::vector<std::pair<double, bool>> dataVector;
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open()) 
	{
		std::cerr << "Error: unable to open file: " << filename << std::endl;
		return dataVector;
	}
	//пропускаем первую строку с заголовками
	std::getline(file, line);
	while (std::getline(file, line)) {
		std::stringstream lineStream(line);
		std::string cell;

		while (std::getline(lineStream, cell, ';')) 
		{
			//обрабатываем пропуски в строках
			if (cell.empty()) 
			{
				dataVector.push_back(std::pair(0.0, false)); 
			}
			else
			{
				double value = std::stod(cell); //переводим в double
				dataVector.push_back(std::pair(value, true));
			}
		}
	}
	file.close();
	return dataVector;
}

std::vector<std::pair<double, IONeuron*>> SimpleForwardNetwork::readDataPtr(std::string filename)
{
	std::vector<std::pair<double, IONeuron*>> dataVector;
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
	{
		std::cerr << "Error: unable to open file: " << filename << std::endl;
		return dataVector;
	}
	//пропускаем первую строку с заголовками
	std::getline(file, line);
	while (std::getline(file, line)) 
	{
		std::stringstream lineStream(line);
		std::string cell;
		int i = 0;

		while (std::getline(lineStream, cell, ';'))
		{
			//обрабатываем пропуски в строках
			if (cell.empty())
			{
				dataVector.push_back(std::pair(0.0, nullptr));
			}
			else
			{
				double value = std::stod(cell); //переводим в double
				dataVector.push_back(std::pair(value, ions[i]));
			}
			i++;
		}
	}
	file.close();

	return dataVector;
}

void SimpleForwardNetwork::predictDataBool()
{
	//TODO использовать относительный путь
	std::string filename = "C:\\Users\\user\\Desktop\\Neuro\\NeuroLib\\empty_data.csv";

	std::vector<std::pair<double, bool>> dataset = readDataBool(filename);
	//проверяем полученный датасет
	/*for (auto pair : dataset)
	{
		std::cout << "Value: " << pair.first << ", Present: " << pair.second << std::endl;
	}*/


	//будет работать только пока первые индексы у ионов
	int i = 0;
	//?сохраняем индексы для out нейронов в отдельный вектор, чтобы не обходить нейроны дважды
	std::vector<std::pair<double, int>> outIndices;
	//проходим датасет
	for (auto pair : dataset)
	{
		if (pair.second == true)
		{
			//для входных нейронов делаем степ форвард
			stepForward(i, pair.first);
		}
		else
		{
			outIndices.push_back(std::pair(pair.first, i));
		}
		if (i < 2)
		{
			i++;
		}
		else
		{
			i = 0;
		}
	}
	//делаем степ бэквард для выходных нейронов
	for (auto pair : outIndices)
	{
		//? для пустых значений задавали value 0 или рандомное
		stepBackward(pair.second, pair.first);
		std::cout << "Out Neuron " << pair.second << " predicted value is " << ions[pair.second]->getInputValue() << std::endl;
	}
}

std::map<int, std::vector<Neuron*>> SimpleForwardNetwork::getGraphs()
{
	return graphs;
}
