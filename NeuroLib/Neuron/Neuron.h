#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <math.h> 
#include <iostream>

#include "Synapse\Synapse.h"

class Synapse;

class Neuron
{
private:
    double value;
    std::vector<Synapse*> linkedSynapses;

    double activation();

public:
    Neuron(double setValue = 0);

    void setValue(double setValue);
    double getValue();
    void addSynapse(Synapse* synapse);

    double forward();
};

#endif //NEURON_H