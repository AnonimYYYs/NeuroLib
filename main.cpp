#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Network\Network.h"
#include "Network\SimpleForwardNetwork\SimpleForwardNetwork.h"




int main() 
{
    Network* sNetwork(Network::createSmallWorldNetwork(3, 5, 2, 0.2));
    SimpleForwardNetwork network (sNetwork);

    network.forwardPass();

    sNetwork->printIons();

    return 0;
}