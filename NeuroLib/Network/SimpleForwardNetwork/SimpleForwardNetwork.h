#ifndef SIMPLEFORWARD_H
#define SIMPLEFORWARD_H

#include "Network\Network.h"

#include <math.h>
#include <fstream>
#include <sstream>


class SimpleForwardNetwork : public Network	
{
private:
	std::map<int, std::vector<Neuron*>> graphs;
	bool isInitialized;
public:
	SimpleForwardNetwork(Network* network);
	SimpleForwardNetwork();

	static SimpleForwardNetwork* createSmallWorldNetwork(int nIons, int Nneurons, int degree, float redirect);
	static SimpleForwardNetwork* createRandomNetwork(int nIons, int nNeurons, float connect);

	std::vector<Neuron*> graphTraverse(int index);
	void initGraphs();
	void stepForward(int index, double value);
	void stepBackward(int index, double value, double eps = 0.1);
	std::vector<std::vector<double>> predict (std::vector<std::vector<std::pair<double, bool>>> dataset);
	void learn(std::vector<std::vector<double>> predictedDataset);

	static std::vector<std::vector<std::pair<double, bool>>> readDataBool(std::string filename);
	//static std::vector<std::pair<double, IONeuron*>> readDataPtr(std::string filename);
	std::vector<std::pair<double, bool>> stepPredict(std::vector < std::pair<double, bool>> in);
	double collectOutputs(int index);
	void stepLearn(std::vector<double> in);

	std::map<int, std::vector<Neuron*>> getGraphs();
};

#endif //SIMPLEFORWARD_H