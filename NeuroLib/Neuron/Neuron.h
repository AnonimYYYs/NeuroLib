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
    double inputValue;
    double outputValue;
    std::vector<Synapse*> linkedSynapses;

    void activation();

public:
    Neuron(double setValue = 0);

    void setValue(double setValue);
    double getValue();
    void addSynapse(Synapse* synapse);

    void forward();
};

class IONeuron : public Neuron
{
public:
    IONeuron(double inputValue = 0);
};

#endif //NEURON_H