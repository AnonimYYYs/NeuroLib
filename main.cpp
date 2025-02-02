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

    neurons[0]->forwardOut();
    synapses[0]->applyWeight(synapses[0]->getSignals()[0]);
    neurons[1]->forwardOut();
    synapses[1]->applyWeight(synapses[1]->getSignals()[0]);
    neurons[3]->forwardIn();

    std::cout << neurons[3]->getValue() << std::endl;  

    std::cout << static_cast<std::string>(*((IONeuron*)neurons[0])) << std::endl;


    return 0;
}