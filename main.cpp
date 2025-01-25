#include "Neuron\Neuron.h"
#include "Synapse\Synapse.h"

//int main() {
//    std::cout << "hello world: ";
//    std::cout << neurolib::neuro_sum(2, 4) << std::endl;
//}
//
//    return 0;

int main() 
{
    std::vector<Neuron*> neurons;

    neurons.push_back(new IONeuron(0.1, 1));
    neurons.push_back(new IONeuron(0.2, 2));
    neurons.push_back(new IONeuron(0.3, 3));
    neurons.push_back(new Neuron(0, 4));
    neurons.push_back(new Neuron(0, 5));
    neurons.push_back(new Neuron(0, 6));

    std::vector<Synapse*> synapses;
    
    synapses.push_back(new Synapse(neurons[0], neurons[3], 0.3));
    synapses.push_back(new Synapse(neurons[1], neurons[3], 0.4));
    synapses.push_back(new Synapse(neurons[1], neurons[4], 0.5));
    synapses.push_back(new Synapse(neurons[2], neurons[4], 0.6));
    synapses.push_back(new Synapse(neurons[2], neurons[5], 0.7));
    synapses.push_back(new Synapse(neurons[0], neurons[5], 0.8));

    neurons[3]->forward(); 


    return 0;
}