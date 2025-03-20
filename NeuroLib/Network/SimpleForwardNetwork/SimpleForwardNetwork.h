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

	static SimpleForwardNetwork* createSmallWorldNetwork(int nIons, int Nneurons, int degree, float redirect, int* seed = nullptr);
	static SimpleForwardNetwork* createRandomNetwork(int nIons, int nNeurons, float connect, int* seed = nullptr);

	std::vector<Neuron*> graphTraverse(int index);
	void initGraphs();
	void stepForward(int index, double value);
	void stepBackward(int index, double value, double eps = 0.1);
	std::vector<std::vector<double>> predictBool (std::vector<std::vector<std::pair<double, bool>>> dataset);
	std::vector<std::vector<double>> predictPtr(std::vector<std::vector<double*>> dataset);
	void learn(std::vector<std::vector<double>> predictedDataset, int epoch, int* seed = nullptr);

	static std::vector<std::vector<std::pair<double, bool>>> readDataBool(std::string filename);
	static std::vector<std::vector<double*>> readDataPtr(std::string filename);
	static std::vector<std::vector<double>> readDataLearn(std::string filename);
	std::vector<std::pair<double, bool>> stepPredictBool(std::vector  <std::pair<double, bool>> in);
	std::vector<double*> stepPredictPtr(std::vector <double*> in);
	double collectOutputs(int index);
	void stepLearn(std::vector<double> in, int* seed = nullptr);

	std::map<int, std::vector<Neuron*>> getGraphs();
};

#endif //SIMPLEFORWARD_H