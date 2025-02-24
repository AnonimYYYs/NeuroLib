#include "Synapse\Synapse.h"

Synapse::Synapse(Neuron* neuron1, Neuron* neuron2)
{ 
    weight = 0;
    this->neuron1 = neuron1;
    this->neuron2 = neuron2;
}

Synapse::~Synapse()
{
    deleteSignals();
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
    storedSignals[signal->getIndex()] = signal;
}
void Synapse::removeSignal(int index)
{
    storedSignals.erase(index);
}

Signal* Synapse::popSignal(int index)
{
    Signal* signal = storedSignals[index];
    storedSignals.erase(index);
    return signal;
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

std::map<int, Signal*> Synapse::getSignals()
{
    return storedSignals;
}
void Synapse::deleteSignals()
{
    for (auto [index, signal] :storedSignals)
    {
        delete signal;
    }
    storedSignals.clear();
}
