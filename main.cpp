#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>


int main() 
{
    //TODO createrandom полностью связный при коннект=1
    int seed = 111;
    int* seedPtr = &seed;

    SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(6, 10, 1, 0.3, seedPtr);
    //SimpleForwardNetwork* network = SimpleForwardNetwork::createRandomNetwork(6, 10, 1, seedPtr);
    network->initGraphs();

    //TODO использовать относительный путь
    std::string filename = "C:\\Users\\user\\Desktop\\Neuro\\NeuroLib\\dataset100.csv";

    std::vector<std::vector<double>> dataset = SimpleForwardNetwork::readDataLearn(filename);
    //for (auto vector : dataset)
    //{
    //    for (auto value : vector)
    //    {
    //         std::cout << value << "\t";
    //    }
    //    std::cout << std::endl;
    //}

    network->learn(dataset, 1, seedPtr);

    return 0;
}