#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"

#include <math.h>

int main() 
{
    SimpleForwardNetwork* network(SimpleForwardNetwork::createSmallWorldNetwork(3, 7, 1, 0.3));
    network->initGraphs();
    for (auto [index, graph] : network->getGraphs())
    {
        for (Neuron* neuron : graph)
        {
            std::cout << neuron->getIndex();
        }
        std::cout << std::endl;
    }
    std::vector<double> in = { 0.25, 0.35, 0.45 };
    network->stepComplete(in);
    network->printIons();

    return 0;
}