#include "Neuron\Neuron.h"

void Neuron::activation()
{
    // сигмоид
    outputValue = 1.0 / (1.0 + std::exp(-inputValue));
}

Neuron::Neuron(double setValue, int index) : inputValue(setValue), index(index) 
{ 
    activation(); 
}

void Neuron::setValue(double setValue) 
{ 
   inputValue = setValue; 
}
double Neuron::getValue() 
{ 
    return outputValue; 
}

int const Neuron::getIndex()
{
    return index;
}

void Neuron::addSynapse(Synapse* synapse)
{
    linkedSynapses.push_back(synapse);
}

std::vector<Synapse*> Neuron::getSynapses()
{
    return linkedSynapses;
}

IONeuron::IONeuron(double inputValue, int index) : Neuron(inputValue, index) {}
