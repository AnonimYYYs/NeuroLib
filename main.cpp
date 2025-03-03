#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>


int main() 
{
    SimpleForwardNetwork* network = SimpleForwardNetwork::createSmallWorldNetwork(3, 2, 1, 0.3);
    network->initGraphs();
    for (auto [index, graph] : network->getGraphs())
    {
        for (Neuron* neuron : graph)
        {
            std::cout << neuron->getIndex();
        }
        std::cout << std::endl;
    }
    std::vector<std::vector<double>> in = { { 0.3465, 0.8456, 0.3475 },
                                            { 0.6373, 0.2325, 0.7956 },
                                            { 0.2415, 0.6765, 0.3278 } };
    network->learn(in, 3);
    network->printIons();
  
    //network->predictDataBool();

    return 0;
}