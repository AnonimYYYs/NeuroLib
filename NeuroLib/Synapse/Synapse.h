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
    //Neuron* input;
    //Neuron* output;

    double weight;
    double value;
    std::vector<Neuron*> linkedNeurons;

public:
    Synapse(Neuron* neuron1, Neuron* neuron2, double w = 0, double v = 0);

    //void addNeuron(Neuron* neuron);


    double getValue();
    void setValue(int n);
    void moveValue(int n);

    double applyWeight(Neuron *targetNeuron);
};

#endif //SYNAPSE_H