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

double Neuron::getInputValue()
{
    return inputValue;
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

void Neuron::forwardIn()
{
    double sum = 0;
    for (Synapse* synapse : linkedSynapses)
    {
        //доработать для нескольких сигналов в синапсе
        sum += synapse->getSignals()[0]->getValue();
    }
    inputValue = sum;
    activation();
}

void Neuron::forwardOut()
{
    for (Synapse* synapse : linkedSynapses)
    {
        //доработать для нескольких сигналов в синапсе
        if (synapse->getSignals().empty() == false)
        {
            synapse->getSignals().clear();
        }
        synapse->addSignal(new Signal(outputValue, index));
    }
}


//std::ostream& operator<<(std::ostream& os, const Neuron& neuron)
//{
//    os << neuron.getValue(); 
//    return os;
//}

IONeuron::IONeuron(double inputValue, int index) : Neuron(inputValue, index) {}
