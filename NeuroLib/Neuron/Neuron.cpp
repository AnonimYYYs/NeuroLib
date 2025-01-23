#include "Synapse\Synapse.h"
#include "Neuron\Neuron.h"

void Neuron::activation()
{
    // сигмоид
    outputValue = 1.0 / (1.0 + std::exp(-inputValue));
}

Neuron::Neuron(double setValue) : outputValue(setValue) {}

void Neuron::setValue(double setValue) 
{ 
    outputValue = setValue; 
}
double Neuron::getValue() 
{ 
    return outputValue; 
}

void Neuron::addSynapse(Synapse* synapse)
{
    linkedSynapses.push_back(synapse);
}

void Neuron::forward()
{
    double sum = 0;
    for (Synapse* synapse : linkedSynapses)
    {
        sum += synapse->applyWeight(this);
    }
    inputValue = sum;
    activation();

    std::cout << "Input Value: " << inputValue << std::endl;
    std::cout << "Output Value: " << outputValue << std::endl;
}

IONeuron::IONeuron(double inputValue) : Neuron() 
{
    setValue(inputValue);
}
