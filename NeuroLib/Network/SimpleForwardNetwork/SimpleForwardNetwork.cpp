
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

	double mse = pow((value - rootIon->getOutputValue()), 2);
	std::cout << "Mean Squared Error: " << mse << std::endl;
	
	//создаем сигналы со значением ошибки
	rootIon->spawnErrorSignals(mse * eps);
	//убираем корневой нейрон, чтобы не обходить его дважды
	graph.erase(graph.begin());

	for (Neuron* neuron : graph)
	{
		neuron->backward(index);
	}
}

std::vector<std::vector<double>> SimpleForwardNetwork::predict(std::vector<std::vector<std::pair<double, bool>>> dataset)
{
	std::vector<std::vector<double>> predictedDataset;
	for (std::vector<std::pair<double, bool>> set : dataset)
	{
		std::vector<std::pair<double, bool>> stepSet = stepPredict(set);
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

void SimpleForwardNetwork::learn(std::vector<std::vector<double>> predictedDataset)
{
	for (std::vector<double> set : predictedDataset)
	{
		stepLearn(set);
	}
}

void SimpleForwardNetwork::stepLearn(std::vector<double> in)
{
	std::cout << "Starting stepLearn..." << std::endl;
	std::vector<bool> inOutBools;
	//создаем вектор булов для индексов нейронов на вход и выход
	while (inOutBools.size() < in.size())
	{
		bool randomBool = random(0, 1);
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
		int index = random(0, n - 1);
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
			  << "stepBackward Complete!" << std::endl
			  << "Learn complete!" << std::endl << std::endl;;
	clearSignals();
}

//std::vector<std::vector<std::pair<double, bool>>> SimpleForwardNetwork::readDataBool(std::string filename)
//{
//	std::vector<std::vector<std::pair<double, bool>>> dataVector;
//	std::ifstream file(filename);
//	std::string line;
//
//	if (!file.is_open()) 
//	{
//		std::cerr << "Error: unable to open file: " << filename << std::endl;
//		return dataVector;
//	}
//	//пропускаем первую строку с заголовками
//	std::getline(file, line);
//	while (std::getline(file, line)) 
//	{
//		std::stringstream lineStream(line);
//		std::string cell;
//		std::vector<std::pair<double, bool>> lineVector;
//
//		while (std::getline(lineStream, cell, ';')) 
//		{
//			//обрабатываем пропуски в строках
//			if (cell.empty()) 
//			{
//				lineVector.push_back(std::pair(0.0, false));
//			}
//			else
//			{
//				double value = std::stod(cell); //переводим в double
//				lineVector.push_back(std::pair(value, true));
//			}
//		}
//		dataVector.push_back(lineVector);
//	}
//	file.close();
//	return dataVector;
//}


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

//std::vector<std::pair<double, IONeuron*>> SimpleForwardNetwork::readDataPtr(std::string filename)
//{
//	std::vector<std::pair<double, IONeuron*>> dataVector;
//	std::ifstream file(filename);
//	std::string line;
//
//	if (!file.is_open())
//	{
//		std::cerr << "Error: unable to open file: " << filename << std::endl;
//		return dataVector;
//	}
//	//пропускаем первую строку с заголовками
//	std::getline(file, line);
//	while (std::getline(file, line)) 
//	{
//		std::stringstream lineStream(line);
//		std::string cell;
//		int i = 0;
//
//		while (std::getline(lineStream, cell, ';'))
//		{
//			//обрабатываем пропуски в строках
//			if (cell.empty())
//			{
//				dataVector.push_back(std::pair(0.0, nullptr));
//			}
//			else
//			{
//				double value = std::stod(cell); //переводим в double
//				dataVector.push_back(std::pair(value, ions[i]));
//			}
//			i++;
//		}
//	}
//	file.close();
//
//	return dataVector;
//}

std::vector<std::pair<double, bool>> SimpleForwardNetwork::stepPredict(std::vector <std::pair<double, bool>> set)
{
	std::cout << "Starting stepPredict..." << std::endl;
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
			  << "stepPredict Complete!" << std::endl << std::endl;

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

	return outputValue;

}

std::map<int, std::vector<Neuron*>> SimpleForwardNetwork::getGraphs()
{
	return graphs;
}
