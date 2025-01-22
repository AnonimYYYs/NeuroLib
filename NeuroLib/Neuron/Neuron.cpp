#include "Synapse\Synapse.h"
#include "Neuron\Neuron.h"
#include <vector>
#include <math.h> 


double Neuron::activation()
{
    // сигмоид
    return 1.0 / (1.0 + std::exp(-value));
}

Neuron::Neuron(double setValue) : value(setValue) {}

void Neuron::setValue(double setValue) { value = setValue; }
double Neuron::getValue() { return value; }

void Neuron::addSynapse(Synapse* synapse)
{
    linkedSynapses.push_back(synapse);
    synapse->addNeuron(this);
}

double Neuron::forward()
{
    double sum = 0;
    for (Synapse* synapse : linkedSynapses)
    {
        sum += synapse->applyWeight();
    }
    value = sum;
    return activation();
}

