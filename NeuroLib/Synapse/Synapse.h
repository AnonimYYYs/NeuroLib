#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "Neuron\Neuron.h"

class Neuron;
class Signal;

class Synapse
{
private:
    double weight;
    double value;
    std::vector<Neuron*> linkedNeurons;
    std::vector<Signal*> storedSignals;
public:
    Synapse(Neuron* neuron1, Neuron* neuron2, double w = 0, double v = 0);


    double getValue();
    void setValue(int n);
    void moveValue(int n);

    double applyWeight(Neuron *targetNeuron);
};

#endif //SYNAPSE_H