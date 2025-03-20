
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

SimpleForwardNetwork* SimpleForwardNetwork::createSmallWorldNetwork(int nIons, int nNeurons, int degree, float redirect, int* seed)
{
	Network* network = Network::createSmallWorldNetwork(nIons, nNeurons, degree, redirect, seed);
	SimpleForwardNetwork* sfn = new SimpleForwardNetwork(network);
	return sfn;
}

SimpleForwardNetwork* SimpleForwardNetwork::createRandomNetwork(int nIons, int nNeurons, float connect, int* seed)
{
	Network* network = Network::createRandomNetwork(nIons, nNeurons, connect, seed);
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

	rootIon->setInputValue(value);
	rootIon->spawnValueSignals(value);
	//убираем корневой нейрон, чтобы не обходить его дважды
	graph.erase(graph.begin());
	for (Neuron* neuron : graph)
	{
		neuron->forward(index);
	}
}

void SimpleForwardNetwork::stepBackward(int index, double value, double eps)
{
	IONeuron* rootIon = ions[index];
	std::vector<Neuron*> graph = graphs[index];

	//создаем сигналы со значением ошибки
	double error = (value - rootIon->getOutputValue());
	rootIon->spawnErrorSignals(error * eps);

	//убираем корневой нейрон, чтобы не обходить его дважды
	graph.erase(graph.begin());

	for (Neuron* neuron : graph)
	{
		neuron->backward(index, eps);
	}
}

std::vector<std::vector<double>> SimpleForwardNetwork::predictBool(std::vector<std::vector<std::pair<double, bool>>> dataset)
{
	std::vector<std::vector<double>> predictedDataset;
	for (std::vector<std::pair<double, bool>> set : dataset)
	{
		std::vector<std::pair<double, bool>> stepSet = stepPredictBool(set);
		std::vector<double> predictedSet;
		for (auto pair : stepSet)
		{
			predictedSet.push_back(pair.first);
		}
		predictedDataset.push_back(predictedSet);
	}

	//вывод результатов предикта
	std::cout << "------------------------------" << std::endl
			  << "Predict Results " << std::endl
		      << "In: " << std::endl;;
	std::cout.precision(5);
	for (int i = 0; i < dataset.size(); i++)
	{
		std::cout << "(" << i << ")\t";
		for (auto [value, boolValue] : dataset[i])
		{
			std::cout << value << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "Out: " << std::endl;
	for (int i = 0; i < predictedDataset.size(); i++)
	{
		std::cout << "(" << i << ")\t";
		for (double value : predictedDataset[i])
		{
			std::cout << value << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------------" << std::endl;

	return predictedDataset;
}

std::vector<std::vector<double>> SimpleForwardNetwork::predictPtr(std::vector<std::vector<double*>> dataset)
{
	std::vector<std::vector<double>> predictedDataset;
	for (std::vector<double*> set : dataset)
	{
		std::vector<double*> stepSet = stepPredictPtr(set);
		std::vector<double> predictedSet;
		for (auto value : stepSet)
		{
			predictedSet.push_back(*value);
		}
		predictedDataset.push_back(predictedSet);
	}

	//вывод результатов предикта
	std::cout << "------------------------------" << std::endl
		<< "Predict Results " << std::endl
		<< "In: " << std::endl;;
	std::cout.precision(5);
	for (int i = 0; i < dataset.size(); i++)
	{
		std::cout << "(" << i << ")\t";
		for (auto value : dataset[i])
		{
			std::cout << value << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "Out: " << std::endl;
	for (int i = 0; i < predictedDataset.size(); i++)
	{
		std::cout << "(" << i << ")\t";
		for (double value : predictedDataset[i])
		{
			std::cout << value << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------------" << std::endl;

	return predictedDataset;
}

void SimpleForwardNetwork::learn(std::vector<std::vector<double>> dataset, int epoch, int* seed)
{
	for (int e = 0; e < epoch; e++)
	{
		std::cout << "Epoch " << e << std::endl;
		for (int i = 0; i < dataset.size(); i++)
		{
			std::vector<double> set = dataset[i];
			std::cout << "Set " << i << std::endl;
			stepLearn(set, seed);
		}
	}
}

void SimpleForwardNetwork::stepLearn(std::vector<double> in, int* seed)
{
	std::cout << "Starting stepLearn..." << std::endl;
	std::vector<bool> inOutBools;
	//создаем вектор булов для индексов нейронов на вход и выход
	while (inOutBools.size() < in.size())
	{
		bool randomBool = random(0, 1, seed);
		inOutBools.push_back(randomBool);
	}
	bool check = false;
	//проверяем, чтобы был хотя бы 1 нейрон как на вход, так и на выход
	for (bool currentBool : inOutBools)
	{
		//если иф не соблюдается ни разу, все нейроны в векторе одного типа
		if (currentBool != inOutBools[0])
		{
			check = true;
			break;
		}
	}
	//если все нейроны одного типа
	if (check == false)
	{
		int n = inOutBools.size();
		int index = random(0, n - 1, seed);
		//задаем противоположное значение случайному нейрону
		inOutBools[index] = !inOutBools[index];
	}

	//вывод индексов на вход и выход
	std::cout << "Bools: ";
	for(int index : inOutBools)
	{
		std::cout << index << " ";
	}
	std::cout << std::endl;

	//stepForward
	//будет работать только пока первые индексы у ионов
	//для входных нейронов делаем степ форвард
	for (int i = 0; i < in.size(); i++)
	{
		if (inOutBools[i] == true)
		{
			double inValue = in[i];
			std::cout << "Ion " << i << " -> stepForward..." << std::endl;
			stepForward(i, inValue);
		}
	}
	std::cout << "Forward Complete!" << std::endl;

	//делаем гет и бэквард для выходных нейронов
	for (int i = 0; i < in.size(); i++)
	{
		if (inOutBools[i] == false)
		{
			std::cout << "Ion " << i << " -> collectOutputs..." << std::endl;
			double outValue = collectOutputs(i);
			std::cout << "Output value is " << outValue << std::endl;

			std::cout << "Ion " << i << " -> stepBackward..." << std::endl;
			//берем значения из вектора in как perfect value
			stepBackward(i, in[i]);
		}
	}
	std::cout << "All Outputs Collected!" << std::endl
		<< "stepBackward Complete!" << std::endl;

	double errorSum = 0;
	int n = 0;
	for (int i = 0; i < in.size(); i++)
	{
		if (inOutBools[i] == false)
		{
			double error = pow((in[i] - ions[i]->getOutputValue()), 2);
			errorSum += error;
			n++;
		}
	}
	double mseScore = errorSum / n;

	std::cout << "Error Score: " << mseScore << std::endl
			  << "stepLearn complete!" << std::endl << std::endl;
	clearSignals();
}

std::vector<std::vector<std::pair<double, bool>>> SimpleForwardNetwork::readDataBool(std::string filename) 
{
	std::vector<std::vector<std::pair<double, bool>>> dataVector;
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open()) 
	{
		std::cerr << "Error: unable to open file: " << filename << std::endl;
		return dataVector;
	}

	//пропускаем заголовки
	std::getline(file, line);


	while (std::getline(file, line)) 
	{
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<std::pair<double, bool>> lineVector;

		//бесконечный цикл для обработки пустых значений в конце строк
		while (true) 
		{
			//конец строки
			if (!std::getline(lineStream, cell, ';')) 
			{
				//если в конце строки стоит разделитель, значит последнее значение пустое
				if (!line.empty() && line.back() == ';')
				{
					lineVector.push_back(std::pair(0.0, false));
				}
				//выходим из бесконечного цикла
				break;
			}

			if (cell.empty()) 
			{
				lineVector.push_back(std::pair(0.0, false));
			}
			else 
			{
					double value = std::stod(cell);
					lineVector.push_back(std::pair(value, true));
			}
		}
		dataVector.push_back(lineVector);
	}

	file.close();
	return dataVector;
}





std::vector<std::vector<double*>> SimpleForwardNetwork::readDataPtr(std::string filename)
{
	std::vector<std::vector<double*>> dataVector;
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
	{
		std::cerr << "Error: unable to open file: " << filename << std::endl;
		return dataVector;
	}
	//пропускаем заголовки
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<double*> lineVector;

		//бесконечный цикл для обработки пустых значений в конце строк
		while (true)
		{
			//конец строки
			if (!std::getline(lineStream, cell, ';'))
			{
				//если в конце строки стоит разделитель, значит последнее значение пустое
				if (!line.empty() && line.back() == ';')
				{
					lineVector.push_back(nullptr);
				}
				//выходим из бесконечного цикла
				break;
			}

			if (cell.empty())
			{
				lineVector.push_back(nullptr);
			}
			else
			{
				double* value = new double(std::stod(cell));
				lineVector.push_back(value);
			}
		}
		dataVector.push_back(lineVector);
	}

	file.close();
	return dataVector;
}

std::vector<std::vector<double>> SimpleForwardNetwork::readDataLearn(std::string filename)
{
	std::vector<std::vector<double>> dataVector;
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
		std::vector<double> lineVector;

		while (std::getline(lineStream, cell, ';'))
		{
			double value = std::stod(cell);
			lineVector.push_back(value);
		}
		dataVector.push_back(lineVector);
	}
	file.close();
	return dataVector;
}

std::vector<std::pair<double, bool>> SimpleForwardNetwork::stepPredictBool(std::vector <std::pair<double, bool>> set)
{
	std::cout << "Starting stepPredictBool..." << std::endl;
	std::vector<std::pair<double, bool>> predictedSet = set;
	//будет работать только пока первые индексы у ионов
	//проходим датасет
	for (int i = 0; i < predictedSet.size(); i++)
	{
		if (predictedSet[i].second == true)
		{
			std::cout << "Ion " << i << " -> stepForward..." << std::endl;
			//для входных нейронов делаем степ форвард
			stepForward(i, predictedSet[i].first);
		}
	}
	std::cout << "Forward Complete!" << std::endl;

	//делаем гет для выходных нейронов
	for (int i = 0; i < predictedSet.size(); i++)
	{
		if (predictedSet[i].second == false)
		{
			std::cout << "Ion " << i << " -> collectOutputs..." << std::endl;
			predictedSet[i].first = collectOutputs(i);
			std::cout << "Output value is " << predictedSet[i].first << std::endl;
		}
	}

	clearSignals();
	std::cout << "All Outputs Collected!" << std::endl
			  << "stepPredictBool Complete!" << std::endl << std::endl;

	return predictedSet;
}

std::vector<double*> SimpleForwardNetwork::stepPredictPtr(std::vector<double*> set)
{
	std::cout << "Starting stepPredictBool..." << std::endl;
	std::vector<double*> predictedSet = set;
	//будет работать только пока первые индексы у ионов
	//проходим датасет
	for (int i = 0; i < predictedSet.size(); i++)
	{
		if (predictedSet[i] != nullptr)
		{
			std::cout << "Ion " << i << " -> stepForward..." << std::endl;
			//для входных нейронов делаем степ форвард
			stepForward(i, *predictedSet[i]);
		}
	}
	std::cout << "Forward Complete!" << std::endl;

	//делаем гет для выходных нейронов
	for (int i = 0; i < predictedSet.size(); i++)
	{
		if (predictedSet[i] == nullptr)
		{
			std::cout << "Ion " << i << " -> collectOutputs..." << std::endl;
			*predictedSet[i] = collectOutputs(i);
			std::cout << "Output value is " << *predictedSet[i] << std::endl;
		}
	}

	clearSignals();
	std::cout << "All Outputs Collected!" << std::endl
		<< "stepPredictBool Complete!" << std::endl << std::endl;

	return predictedSet;
}

double SimpleForwardNetwork::collectOutputs(int index)
{
	double outputValue = 0;
	IONeuron* ion = ions[index];

	std::map<int, Signal*> collectedSignals;
	//определяем количество индексов сигналов
	for (auto [signalIndex, signal] : ion->getSynapses()[0]->getSignals())
	{
		collectedSignals[signalIndex] = new Signal(0, signalIndex);
	}
	//собираем все сигналы с соседних синапсов
	for (Synapse* synapse : ion->getSynapses())
	{
		for (auto [signalIndex, signal] : synapse->getSignals())
		{
			Signal* currentSignal = synapse->getSignals()[signalIndex];
			double setValue = collectedSignals[signalIndex]->getValue() + currentSignal->getValue();
			collectedSignals[signalIndex]->setValue(setValue);
		}
	}
	//складываем сигналы
	for (auto [signalIndex, signal] : collectedSignals)
	{
		outputValue += ion->activation(signal->getValue());
	}
	collectedSignals.clear();

	return outputValue;

}

std::map<int, std::vector<Neuron*>> SimpleForwardNetwork::getGraphs()
{
	return graphs;
}
