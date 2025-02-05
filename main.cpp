#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "World\World.h"


//int main() {
//    std::cout << "hello world: ";
//    std::cout << neurolib::neuro_sum(2, 4) << std::endl;
//}
//
//    return 0;

int main() 
{
    //World myWorld;

    //myWorld.addIONeuron(0.1);
    //myWorld.addIONeuron(0.2);
    //myWorld.addNeuron();
    //myWorld.addNeuron();

    //myWorld.addSynapse(myWorld.neurons[0], myWorld.neurons[2], 0.5);
    //myWorld.addSynapse(myWorld.neurons[2], myWorld.neurons[3], 0.6);
    //myWorld.addSynapse(myWorld.neurons[3], myWorld.neurons[1], 0.7);

    //myWorld.forwardPass();

    //myWorld.printIons();

    World rWorld (World::createRandomWorld(10, 100, 0.1));
    rWorld.forwardPass();
    rWorld.printIons();

    return 0;
}