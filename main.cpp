#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"



int main() 
{
    SimpleForwardNetwork* sNetwork(SimpleForwardNetwork::createSmallWorldNetwork(2, 3, 1, 0.3));
    sNetwork->forwardPass();

    sNetwork->printIons();

    return 0;
}