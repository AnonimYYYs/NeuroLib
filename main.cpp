#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>


int main() 
{
    SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(4, 2, 1, 0.3);
    network->initGraphs();

    //TODO использовать относительный путь
    std::string filename = "C:\\Users\\user\\Desktop\\Neuro\\NeuroLib\\empty_data.csv";

    std::vector<std::vector<std::pair<double, bool>>> dataset = SimpleForwardNetwork::readDataBool(filename);
    //проверяем полученный датасет
    /*int i = 0, j = 0;
    for (auto set : dataset)
    {
        std::cout << "Set " << i << ": ";
        for (auto pair : set)
        {
            std::cout << pair.first << "-" << pair.second << "  ";
        }
        std::cout << std::endl;
        i++;
    }*/
    std::vector<std::vector<double>> predictedDataset = network->predict(dataset);
    network->learn(predictedDataset);

    return 0;
}