#ifndef SYNAPSE_H
#define SYNAPSE_H

#include "Neuron\Neuron.h"
#include "Signal\Signal.h"
class Neuron;
class Signal;

class Synapse
{
private:
    double weight;
    std::vector<Neuron*> linkedNeurons;
    std::vector<Signal*> storedSignals;
public:
    Synapse(Neuron* neuron1, Neuron* neuron2);

    double getWeight();
    void setWeight(double setWeight);

    void applyWeight(Signal* targetSignal);
    void addSignal(Signal* signal);
    void removeSignal(Signal* signal);
    void rewire(Neuron* neuron);

    std::vector<Neuron*> getNeurons();
    std::vector<Signal*> getSignals();
};

#endif //SYNAPSE_H