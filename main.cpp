#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "World\World.h"


int main() 
{
    World* rWorld (World::createRandomWorld(5, 10, 0.1));
    rWorld->forwardPass();
    rWorld->printIons();

    return 0;
}