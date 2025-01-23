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

    neurons.push_back(new IONeuron(0.1));
    neurons.push_back(new IONeuron(0.2));
    neurons.push_back(new IONeuron(0.3));
    neurons.push_back(new Neuron());
    neurons.push_back(new Neuron());
    neurons.push_back(new Neuron());

    std::vector<Synapse*> synapses;
    
    synapses.push_back(new Synapse(neurons[0], neurons[3], 0.5));
    synapses.push_back(new Synapse(neurons[1], neurons[3], 0.6));


    neurons[3]->forward(); 


    return 0;
}