#include "Synapse\Synapse.h"
#include "Neuron\Neuron.h"

Synapse::Synapse(Neuron* in, Neuron* out, double w, double v) : input(in), output(out), weight(w), value(v) { }

void Synapse::addNeuron(Neuron* neuron) { linkedNeurons.push_back(neuron); }

double Synapse::getValue(double n)
{
    return linkedNeurons[n]->getValue();
}
//Neuron* Synapse::getOutput() { return output; }

double Synapse::applyWeight()
{
    double weightedInput = input->getValue() * weight;
    output->setValue(weightedInput);
    return weightedInput;
}



