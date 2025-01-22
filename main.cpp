#include "NeuroLib.h"
#include "NeuroLib.cpp" //unresolved external errors ?

#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"
#include "Neuron\Neuron.cpp"
#include "Synapse\Synapse.cpp"

//int main() {
//    std::cout << "hello world: ";
//    std::cout << neurolib::neuro_sum(2, 4) << std::endl;
//}
//
//    return 0;

int main() 
{
    std::vector<Neuron*> neurons;

    neurons.push_back(new Neuron(0.1));
    neurons.push_back(new Neuron(0.2));
    neurons.push_back(new Neuron(0.3));
    neurons.push_back(new Neuron());
    neurons.push_back(new Neuron());
    neurons.push_back(new Neuron());

    Synapse test(neurons[0], neurons[3], 0.5);
    neurons[0]->addSynapse(&test); 
    neurons[3]->addSynapse(&test);

    double outputValue = neurons[3]->forward(); 

    std::cout << "Output value: " << outputValue << std::endl;
    std::cout << "Neuron 4 value: " << neurons[3]->getValue() << std::endl;


    return 0;
}