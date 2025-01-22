#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <vector>
#include <math.h> 
#include <iostream>

#include "Neuron\Neuron.h"

class Neuron;

class Synapse
{
private:
    Neuron* input;
    Neuron* output;

    double weight;
    double value;
    std::vector<Neuron*> linkedNeurons;

public:
    Synapse(Neuron* in, Neuron* out, double w = 0, double v = 0);

    void addNeuron(Neuron* neuron);


    double getValue(double n);

    //Neuron* getOutput();

    double applyWeight();
};

#endif //SYNAPSE_H