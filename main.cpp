#include <iostream>

#include "NeuroLib/NeuroLib.h"


//int main() {
//    std::cout << "hello world: ";
//    std::cout << neurolib::neuro_sum(2, 4) << std::endl;
//}
//
//    return 0;
using namespace std;

int main() 
{
    vector<Neuron*> neurons;

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

    cout << "Output value: " << outputValue << endl;
    cout << "Neuron 4 value: " << neurons[3]->getValue() << endl;


    return 0;
}