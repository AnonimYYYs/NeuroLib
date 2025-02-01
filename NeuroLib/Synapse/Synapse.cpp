#include "Synapse\Synapse.h"

Synapse::Synapse(Neuron* neuron1, Neuron* neuron2, double w, double v) :  weight(w), value(v) 
{ 
    linkedNeurons.push_back(neuron1);
    linkedNeurons.push_back(neuron2);

    neuron1->addSynapse(this);
    neuron2->addSynapse(this);
}

double Synapse::getValue()
{
    return value;
}
void Synapse::setValue(int n)
{
    value = linkedNeurons[n]->getValue();
}
void Synapse::moveValue(int n)
{
    linkedNeurons[n]->setValue(value);
}

void Synapse::applyWeight(Signal* signal)
{
    signal->setValue(signal->getValue() * weight);
} 

void Synapse::addSignal(Signal* signal)
{
    storedSignals.push_back(signal);
}

std::vector<Neuron*> Synapse::getNeurons()
{
    return linkedNeurons;
}

std::vector<Signal*> Synapse::getSignals()
{
    return storedSignals;
}
