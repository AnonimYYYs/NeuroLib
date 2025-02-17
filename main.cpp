#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "World\World.h"
#include "SimpleForwardNetwork\SimpleForwardNetwork.h"


int main() 
{
    World* sWorld (World::createSmallWorld(3, 5, 2, 0.2));
    SimpleForwardNetwork network (sWorld);

    network.forwardPass();

    sWorld->printIons();

    return 0;
}