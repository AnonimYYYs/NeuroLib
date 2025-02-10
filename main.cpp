#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "World\World.h"


int main() 
{
    //World* rWorld (World::createRandomWorld(5, 10, 0.1));
    //rWorld->forwardPass();
    //rWorld->printIons();

    World* sWorld (World::createSmallWorld(3, 5, 2, 0.2));
    sWorld->forwardPass();
    sWorld->printIons();

    return 0;
}