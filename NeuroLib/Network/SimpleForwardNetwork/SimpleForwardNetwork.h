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
	void step(std::vector<double> in);
	void learn(std::vector<std::vector<double>> input, int epoch);

	//static?
	std::vector<std::pair<double, bool>> readDataBool(std::string filename);
	std::vector<std::pair<double, IONeuron*>> readDataPtr(std::string filename);
	void predictDataBool();

	std::map<int, std::vector<Neuron*>> getGraphs();
};

#endif //SIMPLEFORWARD_H