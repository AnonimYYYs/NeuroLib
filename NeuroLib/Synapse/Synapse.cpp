#include "Synapse\Synapse.h"

Synapse::Synapse(Neuron* neuron1, Neuron* neuron2)
{ 
    weight = 0;
    this->neuron1 = neuron1;
    this->neuron2 = neuron2;
}

double Synapse::getWeight()
{
    return weight;
}

void Synapse::setWeight(double setWeight)
{
    weight = setWeight;
}

/*
@brief multiplies signal's stored value by synapse's weight
*/
void Synapse::applyWeight(Signal* signal)
{
    signal->setValue(signal->getValue() * weight);
} 

void Synapse::addSignal(Signal* signal)
{
    applyWeight(signal);
    storedSignals.push_back(signal);
}
void Synapse::removeSignal(Signal* targetSignal)
{
    for (auto iter{ storedSignals.begin() }; iter != storedSignals.end(); iter++ )
    {
        if (*iter == targetSignal)
        {
            storedSignals.erase(iter);
            return;
        }
    }
}

void Synapse::rewire(Neuron* neuron)
{
    neuron2 = neuron;
}

Neuron* Synapse::getNeuron1()
{
    return neuron1;
}

Neuron* Synapse::getNeuron2()
{
    return neuron2;
}

std::vector<Signal*> Synapse::getSignals()
{
    return storedSignals;
}
