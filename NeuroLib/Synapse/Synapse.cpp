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

double Synapse::applyWeight(Neuron *targetNeuron)
{
    double weightedInput = 0;
    for (Neuron* neuron : linkedNeurons)
    {
        if (neuron != targetNeuron)
            weightedInput = neuron->getValue() * weight;
    }
    return weightedInput;
}



